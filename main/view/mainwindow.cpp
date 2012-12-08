#include "mainwindow.h"
#include <iostream>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;

/** TODO
  *     - status updates
  *     - error checking for run
  *     - fail gracefully
  *     - break this hideously long file into several
  */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    modelThread(this, &model),
    progressThread(this, &model)
{
    ui->setupUi(this);

    // connect signals from progress thread
    connect(&progressThread, SIGNAL(progressPercentUpdate(int)), this, SLOT(progressPercentUpdate(int)));
    connect(&progressThread, SIGNAL(progressTimeUpdate(int, int)), this, SLOT(progressTimeUpdate(int, int)));
    connect(&progressThread, SIGNAL(finished()), this, SLOT(enableRun()));
    connect(&progressThread, SIGNAL(imageUpdate(QImage)), this, SLOT(imageUpdate(QImage)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* BEGIN public slots */

void MainWindow::selectHydroMapClicked()
{
    clearErrors();

    // if the currently selected hydro map was not added, remove it
    if (wholeHydroMapFiles.size() != daysToRun.size())
    {
        wholeHydroMapFiles.removeLast();
    }

    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Hydro Map File"),
                                                    defaultFileLocation(), tr("Text Files (*.txt)"));

    // make sure a hydro map file was selected
    if (!selected.isEmpty())
    {
        wholeHydroMapFiles.append(selected);
        QString filename = stripFile(selected);
        ui->labelHydroMap->setText(filename);
        ui->labelHydroMap->setToolTip(filename);
    }
}

void MainWindow::addHydroMapClicked()
{
    clearErrors();
    if (!isBoxFilled(ui->lineEditDaysToRun))
    {
        displayErrors("Need to insert # days to run");
        return;
    }
    if (!isFileSelected(ui->labelHydroMap))
    {
        displayErrors("No hydro map file selected");
        return;
    }

    // filename already added to list, but days to run not added
    QString days = ui->lineEditDaysToRun->text();
    daysToRun.append(days.toInt());

    addHydroMap(ui->labelHydroMap->text(), days, false);
}

void MainWindow::removeHydroMapClicked()
{
    clearErrors();

    QListWidget* list = ui->listWidgetHydroMap;
    QMutableListIterator<QString> itHydro(wholeHydroMapFiles);
    QMutableListIterator<uint16_t> itDays(daysToRun);
    bool anyRemoved = false;
    size_t size = list->count();

    // loop through all items, remove selected items
    for (size_t i = 0; i < size; i++)
    {
        itHydro.next(); itDays.next();
        if (list->item(i)->isSelected())
        {
            itHydro.remove();
            itDays.remove();
            anyRemoved = true;
        }
    }

    if (!anyRemoved)
    {
        displayErrors("No files selected for removal");
    }
    else
    {
        displayHydroFiles(); // this will clear and refresh the list
    }
}

void MainWindow::selectDischargeFileClicked()
{
    clearErrors();

    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Discharge File"),
                                                    defaultFileLocation(), tr("Text Files (*.txt)"));

    // make sure a discharge file was selected
    if (!selected.isEmpty())
    {
        dischargeToHydro(selected);
        compressHydroFiles();
    }
    else
    {
        displayErrors("No discharge file selected");
    }
}

void MainWindow::selectTemperatureFileClicked()
{
    clearErrors();

    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Temperature Data File"),
                                                    defaultFileLocation(), tr("Text Files (*.txt)"));

    // make sure a temperature file was selected
    if (!selected.isEmpty())
    {
        wholeTempFile = selected;
        QString filename = stripFile(wholeTempFile);
        ui->labelTempFile->setText(filename);
        ui->labelTempFile->setToolTip(filename);
    }
}

void MainWindow::selectPARFileClicked()
{
    clearErrors();

    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select PAR Data File"),
                                                    defaultFileLocation(), tr("Text Files (*.txt)"));

    // make sure a par file was selected
    if (!selected.isEmpty())
    {
        wholePARFile = selected;
        QString filename = stripFile(wholePARFile);
        ui->labelPARFile->setText(filename);
        ui->labelPARFile->setToolTip(filename);
    }
}

void MainWindow::runClicked()
{
    clearErrors();

    // check all input for errors
    // and set model values appropriately
    getAllInput();

    modelThread.start();
    progressThread.start();

    // open output tab
    setTab(OUTPUT);

    // disable run button for now
    disableRun();
}

void MainWindow::whichstockChanged(QString newStock)
{
    model.set_whichstock(newStock);
    imageUpdate(model.getImage(newStock));
}

void MainWindow::enableRun()
{
    ui->pushButtonRun->setEnabled(true);
}

void MainWindow::disableRun()
{
    ui->pushButtonRun->setEnabled(false);
}

void MainWindow::timestepUpdate(int newVal)
{
    clearErrors();
    ui->horizontalSliderTimestep->setValue(newVal);
    ui->horizontalSliderTimestep->setToolTip(QString::number(newVal));
    ui->labelTimestepVal->setText(QString::number(newVal));
    ui->labelTimestepVal->move(320 + (140*newVal)/60, ui->labelTimestepVal->y());
}

void MainWindow::progressPercentUpdate(int percent)
{
    ui->progressBar->setValue(percent);
}

void MainWindow::progressTimeUpdate(int elapsed, int remaining)
{
    ui->labelTimeElapsedValue->setText(QString::number(elapsed));
    ui->labelTimeRemainingValue->setText(QString::number(remaining));
}

void MainWindow::imageUpdate(QImage stockImage)
{
    // max size of the image
    int maxWidth = 400;
    int maxHeight = 300;

    // default upper left corner of display field
    int x = 15;
    int y = 60;

    // setup the size for the display field
    QSize scaledSize = stockImage.size();
    scaledSize.scale(maxWidth, maxHeight, Qt::KeepAspectRatio);

    int xOffset = (maxWidth - scaledSize.width()) / 2;
    int yOffset = (maxHeight - scaledSize.height()) / 2;

    // set image to label
    ui->labelImageOutput->setGeometry(QRect(QPoint(x + xOffset, y + yOffset), scaledSize));
    ui->labelImageOutput->setPixmap(QPixmap::fromImage(stockImage));
    ui->labelImageOutput->setScaledContents(true);

    // show image
    ui->labelImageOutput->show();
}

/* END public slots */

/* BEGIN private slots */

void MainWindow::saveConfiguration()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Save Configuration As"),
                                                defaultFileLocation(), tr("Config Files (*.conf)"));
    if (!name.isEmpty())
    {
        saveConfiguration(name);
    }
}

void MainWindow::saveConfiguration(QString file) const
{
    Configuration conf;

    // set all values for configuration
    conf.adjacent                   = getAdjacent();
    conf.outputFreq                 = getOutputFreq();
    conf.timestep                   = getTimestep();
    conf.numHydroMaps               = getNumHydroMaps();
    conf.tss                        = getTSS();
    conf.kMacro                     = getKMacro();
    conf.kPhyto                     = getKPhyto();

    // stock parameters
    conf.macro                      = getMacroBase();
    conf.phyto                      = getPhytoBase();
    conf.consumer                   = getConsumerBase();
    conf.decomp                     = getDecompBase();
    conf.sedconsumer                = getSedconsumerBase();
    conf.seddecomp                  = getSeddecompBase();
    conf.herbivore                  = getHerbivoreBase();
    conf.detritus                   = getDetritusBase();
    conf.poc                        = getPocBase();
    conf.doc                        = getDocBase();

    conf.phytoSenescence            = getPhytoSenescence();
    conf.phytoRespiration           = getPhytoRespiration();
    conf.phytoExcretion             = getPhytoExcretion();
    conf.phytoAj                    = getPhytoAj();
    conf.phytoGj                    = getPhytoGj();

    conf.herbivoreAiPhyto           = getHerbivoreAiPhyto();
    conf.herbivoreGiPhyto           = getHerbivoreGiPhyto();
    conf.herbivorePrefPhyto         = getHerbivorePrefPhyto();
    conf.herbivoreAiPeri            = getHerbivoreAiPeri();
    conf.herbivoreGiPeri            = getHerbivoreGiPeri();
    conf.herbivorePrefPeri          = getHerbivorePrefPeri();
    conf.herbivoreAiWaterdecomp     = getHerbivoreAiWaterdecomp();
    conf.herbivoreGiWaterdecomp     = getHerbivoreGiWaterdecomp();
    conf.herbivorePrefWaterdecomp   = getHerbivorePrefWaterdecomp();
    conf.herbivoreAj                = getHerbivoreAj();
    conf.herbivoreGj                = getHerbivoreGj();
    conf.herbivoreRespiration       = getHerbivoreRespiration();
    conf.herbivoreExcretion         = getHerbivoreExcretion();
    conf.herbivoreEgestion          = getHerbivoreEgestion();
    conf.herbivoreSenescence        = getHerbivoreSenescence();
    conf.herbivoreMax               = getHerbivoreMax();

    conf.waterdecompAiDoc           = getWaterdecompAiDoc();
    conf.waterdecompGiDoc           = getWaterdecompGiDoc();
    conf.waterdecompPrefDoc         = getWaterdecompPrefDoc();
    conf.waterdecompAiPoc           = getWaterdecompAiPoc();
    conf.waterdecompGiPoc           = getWaterdecompGiPoc();
    conf.waterdecompPrefPoc         = getWaterdecompPrefPoc();
    conf.waterdecompAj              = getWaterdecompAj();
    conf.waterdecompGj              = getWaterdecompGj();
    conf.waterdecompRespiration     = getWaterdecompRespiration();
    conf.waterdecompExcretion       = getWaterdecompExcretion();
    conf.waterdecompSenescence      = getWaterdecompSenescence();
    conf.waterdecompMax             = getWaterdecompMax();

    conf.seddecompAiDetritus        = getSeddecompAiDetritus();
    conf.seddecompGiDetritus        = getSeddecompGiDetritus();
    conf.seddecompPrefDetritus      = getSeddecompPrefDetritus();
    conf.seddecompAj                = getSeddecompAj();
    conf.seddecompGj                = getSeddecompGj();
    conf.seddecompRespiration       = getSeddecompRespiration();
    conf.seddecompExcretion         = getSeddecompExcretion();
    conf.seddecompSenescence        = getSeddecompSenescence();
    conf.seddecompMax               = getSeddecompMax();

    conf.consumerAiHerbivore        = getConsumerAiHerbivore();
    conf.consumerGiHerbivore        = getConsumerGiHerbivore();
    conf.consumerPrefHerbivore      = getConsumerPrefHerbivore();
    conf.consumerAiSedconsumer      = getConsumerAiSedconsumer();
    conf.consumerGiSedconsumer      = getConsumerGiSedconsumer();
    conf.consumerPrefSedconsumer    = getConsumerPrefSedconsumer();
    conf.consumerAj                 = getConsumerAj();
    conf.consumerGj                 = getConsumerGj();
    conf.consumerRespiration        = getConsumerRespiration();
    conf.consumerExcretion          = getConsumerExcretion();
    conf.consumerSenescence         = getConsumerSenescence();
    conf.consumerEgestion           = getConsumerEgestion();
    conf.consumerMax                = getConsumerMax();

    conf.macroSenescence            = getMacroSenescence();
    conf.macroRespiration           = getMacroRespiration();
    conf.macroExcretion             = getMacroExcretion();
    conf.macroTemp                  = getMacroTemp();
    conf.macroGross                 = getMacroGross();
    conf.macroMassMax               = getMacroMassMax();
    conf.macroVelocityMax           = getMacroVelocityMax();

    conf.sedconsumerAiDetritus      = getSedconsumerAiDetritus();
    conf.sedconsumerGiDetritus      = getSedconsumerGiDetritus();
    conf.sedconsumerPrefDetritus    = getSedconsumerPrefDetritus();
    conf.sedconsumerAiSeddecomp     = getSedconsumerAiSeddecomp();
    conf.sedconsumerGiSeddecomp     = getSedconsumerGiSeddecomp();
    conf.sedconsumerPrefSeddecomp   = getSedconsumerPrefSeddecomp();
    conf.sedconsumerAj              = getSedconsumerAj();
    conf.sedconsumerGj              = getSedconsumerGj();
    conf.sedconsumerRespiration     = getSedconsumerRespiration();
    conf.sedconsumerExcretion       = getSedconsumerExcretion();
    conf.sedconsumerSenescence      = getSedconsumerSenescence();
    conf.sedconsumerMax             = getSedconsumerMax();

    // file names need special attention
    QList<QString> hydromaps = getHydroMaps();
    conf.hydroMaps = new char*[conf.numHydroMaps];
    QList<uint16_t> days = getDaysToRun();
    conf.daysToRun = new uint16_t[conf.numHydroMaps];
    for (size_t i = 0; i < conf.numHydroMaps; i++)
    {
        conf.setFileName(hydromaps.at(i), conf.hydroMaps[i]);
        conf.daysToRun[i] = days.at(i);
    }
    conf.setFileName(getPARFile(), conf.parFile);
    conf.setFileName(getTempFile(), conf.tempFile);

    conf.write(file.toStdString().c_str());
}

void MainWindow::loadConfiguration()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open Configuration"),
                                                defaultFileLocation(), tr("Config Files (*.conf)"));
    if (!name.isEmpty())
    {
        loadConfiguration(name);
    }
}

void MainWindow::loadConfiguration(QString file)
{
    Configuration conf;
    conf.read(file.toStdString().c_str());

    // basic values
    setAdjacent(conf.adjacent);
    setOutputFreq(conf.outputFreq);
    setTimestep(conf.timestep);
    setTSS(conf.tss);
    setKPhyto(conf.kPhyto);
    setKMacro(conf.kMacro);

    // stock parameters
    setMacroBase(conf.macro);
    setPhytoBase(conf.phyto);
    setConsumerBase(conf.consumer);
    setDecompBase(conf.decomp);
    setSedconsumerBase(conf.sedconsumer);
    setSeddecompBase(conf.seddecomp);
    setHerbivoreBase(conf.herbivore);
    setDetritusBase(conf.detritus);
    setPocBase(conf.poc);
    setDocBase(conf.doc);

    setPhytoSenescence(conf.phytoSenescence);
    setPhytoRespiration(conf.phytoRespiration);
    setPhytoExretion(conf.phytoExcretion);
    setPhytoAj(conf.phytoAj);
    setPhytoGj(conf.phytoGj);

    setHerbivoreAiPhyto(conf.herbivoreAiPhyto);
    setHerbivoreGiPhyto(conf.herbivoreGiPhyto);
    setHerbivorePrefPhyto(conf.herbivorePrefPhyto);
    setHerbivoreAiPeri(conf.herbivoreAiPeri);
    setHerbivoreGiPeri(conf.herbivoreGiPeri);
    setHerbivorePrefPeri(conf.herbivorePrefPeri);
    setHerbivoreAiWaterdecomp(conf.herbivoreAiWaterdecomp);
    setHerbivoreGiWaterdecomp(conf.herbivoreGiWaterdecomp);
    setHerbivorePrefWaterdecomp(conf.herbivorePrefWaterdecomp);
    setHerbivoreAj(conf.herbivoreAj);
    setHerbivoreGj(conf.herbivoreGj);
    setHerbivoreRespiration(conf.herbivoreRespiration);
    setHerbivoreExcretion(conf.herbivoreExcretion);
    setHerbivoreEgestion(conf.herbivoreEgestion);
    setHerbivoreSenescence(conf.herbivoreSenescence);
    setHerbivoreMax(conf.herbivoreMax);

    setWaterdecompAiDoc(conf.waterdecompAiDoc);
    setWaterdecompGiDoc(conf.waterdecompGiDoc);
    setWaterdecompPrefDoc(conf.waterdecompPrefDoc);
    setWaterdecompAiPoc(conf.waterdecompAiPoc);
    setWaterdecompGiPoc(conf.waterdecompGiPoc);
    setWaterdecompPrefPoc(conf.waterdecompPrefPoc);
    setWaterdecompAj(conf.waterdecompAj);
    setWaterdecompGj(conf.waterdecompGj);
    setWaterdecompRespiration(conf.waterdecompRespiration);
    setWaterdecompExcretion(conf.waterdecompExcretion);
    setWaterdecompSenescence(conf.waterdecompSenescence);
    setWaterdecompMax(conf.waterdecompMax);

    setSeddecompAiDetritus(conf.seddecompAiDetritus);
    setSeddecompGiDetritus(conf.seddecompGiDetritus);
    setSeddecompPrefDetritus(conf.seddecompPrefDetritus);
    setSeddecompAj(conf.seddecompAj);
    setSeddecompGj(conf.seddecompGj);
    setSeddecompRespiration(conf.seddecompRespiration);
    setSeddecompExcretion(conf.seddecompExcretion);
    setSeddecompSenescence(conf.seddecompSenescence);
    setSeddecompMax(conf.seddecompMax);

    setConsumerAiHerbivore(conf.consumerAiHerbivore);
    setConsumerGiHerbivore(conf.consumerGiHerbivore);
    setConsumerPrefHerbivore(conf.consumerPrefHerbivore);
    setConsumerAiSedconsumer(conf.consumerAiSedconsumer);
    setConsumerGiSedconsumer(conf.consumerGiSedconsumer);
    setConsumerPrefSedconsumer(conf.consumerPrefSedconsumer);
    setConsumerAj(conf.consumerAj);
    setConsumerGj(conf.consumerGj);
    setConsumerRespiration(conf.consumerRespiration);
    setConsumerExcretion(conf.consumerExcretion);
    setConsumerSenescence(conf.consumerSenescence);
    setConsumerEgestion(conf.consumerEgestion);
    setConsumerMax(conf.consumerMax);

    setMacroSenescence(conf.macroSenescence);
    setMacroRespiration(conf.macroRespiration);
    setMacroExcretion(conf.macroExcretion);
    setMacroTemp(conf.macroTemp);
    setMacroGross(conf.macroGross);
    setMacroMassMax(conf.macroMassMax);
    setMacroVelocityMax(conf.macroVelocityMax);

    setSedconsumerAiDetritus(conf.sedconsumerAiDetritus);
    setSedconsumerGiDetritus(conf.sedconsumerGiDetritus);
    setSedconsumerPrefDetritus(conf.sedconsumerPrefDetritus);
    setSedconsumerAiSeddecomp(conf.sedconsumerAiSeddecomp);
    setSedconsumerGiSeddecomp(conf.sedconsumerGiSeddecomp);
    setSedconsumerPrefSeddecomp(conf.sedconsumerPrefSeddecomp);
    setSedconsumerAj(conf.sedconsumerAj);
    setSedconsumerGj(conf.sedconsumerGj);
    setSedconsumerRespiration(conf.sedconsumerRespiration);
    setSedconsumerExcretion(conf.sedconsumerExcretion);
    setSedconsumerSenescence(conf.sedconsumerSenescence);
    setSedconsumerMax(conf.sedconsumerMax);

    // files
    setTempFile(conf.tempFile);
    setPARFile(conf.parFile);
    setHydroMaps(conf.hydroMaps, conf.daysToRun, conf.numHydroMaps);
}

/* END private slots */

/* BEGIN public functions */

void MainWindow::setToolTips()
{
/*
    ui->lineEditMacroGrossCoef->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditKMacro->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditKPhyto->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditTSS->setToolTip(tr("Enter a number between 0.0 and 20.0"));
    ui->lineEditMacroMassMax->setToolTip(tr("Enter a value between 500.0 and 1500.0"));
    ui->lineEditMacroTemp->setToolTip(tr("Enter a number between 11.7 and 27.7"));
    ui->lineEditMacroVelocityMax->setToolTip(tr("Enter a value between 0.2 and 1.6"));
    ui->lineEditMacroRespiration->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditMacroSenescence->setToolTip(tr("Enter a value between 0.0 and 1.0"));
*/
}

/* GETTERS */
bool MainWindow::getAdjacent() const { return ui->checkBoxAdjacentCells->isChecked(); }

uint8_t MainWindow::getOutputFreq() const { return ui->lineEditOutputFreq->text().toInt(); }
uint8_t MainWindow::getTimestep() const { return ui->horizontalSliderTimestep->value(); }
uint16_t MainWindow::getNumHydroMaps() const { return wholeHydroMapFiles.size(); }

float MainWindow::getTSS() const { return ui->lineEditTSS->text().toFloat(); }
float MainWindow::getKPhyto() const { return ui->lineEditKPhyto->text().toFloat(); }
float MainWindow::getKMacro() const { return ui->lineEditKMacro->text().toFloat(); }

// stock parameters
float MainWindow::getMacroBase() const { return ui->lineEditMacro->text().toFloat(); }
float MainWindow::getPhytoBase() const { return ui->lineEditPhyto->text().toFloat(); }
float MainWindow::getConsumerBase() const { return ui->lineEditConsumer->text().toFloat(); }
float MainWindow::getDecompBase() const { return ui->lineEditDecomp->text().toFloat(); }
float MainWindow::getSedconsumerBase() const { return ui->lineEditSedconsumer->text().toFloat(); }
float MainWindow::getSeddecompBase() const { return ui->lineEditSeddecomp->text().toFloat(); }
float MainWindow::getHerbivoreBase() const { return ui->lineEditHerbivore->text().toFloat(); }
float MainWindow::getDetritusBase() const { return ui->lineEditDetritus->text().toFloat(); }
float MainWindow::getPocBase() const { return ui->lineEditPoc->text().toFloat(); }
float MainWindow::getDocBase() const { return ui->lineEditDoc->text().toFloat(); }

float MainWindow::getPhytoSenescence() const { return ui->lineEditPhytoSenescence->text().toFloat(); }
float MainWindow::getPhytoRespiration() const { return ui->lineEditPhytoRespiration->text().toFloat(); }
float MainWindow::getPhytoExcretion() const { return ui->lineEditPhytoExcretion->text().toFloat(); }
float MainWindow::getPhytoAj() const { return ui->lineEditPhytoAj->text().toFloat(); }
float MainWindow::getPhytoGj() const { return ui->lineEditPhytoGj->text().toFloat(); }

float MainWindow::getHerbivoreAiPhyto() const { return ui->lineEditHerbivoreAiPhyto->text().toFloat(); }
float MainWindow::getHerbivoreGiPhyto() const { return ui->lineEditHerbivoreGiPhyto->text().toFloat(); }
float MainWindow::getHerbivorePrefPhyto() const { return ui->lineEditHerbivorePrefPhyto->text().toFloat(); }
float MainWindow::getHerbivoreAiPeri() const { return ui->lineEditHerbivoreAiPeri->text().toFloat(); }
float MainWindow::getHerbivoreGiPeri() const { return ui->lineEditHerbivoreGiPeri->text().toFloat(); }
float MainWindow::getHerbivorePrefPeri() const { return ui->lineEditHerbivorePrefPeri->text().toFloat(); }
float MainWindow::getHerbivoreAiWaterdecomp() const { return ui->lineEditHerbivoreAiWaterdecomp->text().toFloat(); }
float MainWindow::getHerbivoreGiWaterdecomp() const { return ui->lineEditHerbivoreGiWaterdecomp->text().toFloat(); }
float MainWindow::getHerbivorePrefWaterdecomp() const { return ui->lineEditHerbivorePrefWaterdecomp->text().toFloat(); }
float MainWindow::getHerbivoreAj() const { return ui->lineEditHerbivoreAj->text().toFloat(); }
float MainWindow::getHerbivoreGj() const { return ui->lineEditHerbivoreGj->text().toFloat(); }
float MainWindow::getHerbivoreRespiration() const { return ui->lineEditHerbivoreRespiration->text().toFloat(); }
float MainWindow::getHerbivoreExcretion() const { return ui->lineEditHerbivoreExcretion->text().toFloat(); }
float MainWindow::getHerbivoreEgestion() const { return ui->lineEditHerbivoreEgestion->text().toFloat(); }
float MainWindow::getHerbivoreSenescence() const { return ui->lineEditHerbivoreSenescence->text().toFloat(); }
float MainWindow::getHerbivoreMax() const { return ui->lineEditHerbivoreMax->text().toFloat(); }

float MainWindow::getWaterdecompAiDoc() const { return ui->lineEditWaterdecompAiDoc->text().toFloat(); }
float MainWindow::getWaterdecompGiDoc() const { return ui->lineEditWaterdecompGiDoc->text().toFloat(); }
float MainWindow::getWaterdecompPrefDoc() const { return ui->lineEditWaterdecompPrefDoc->text().toFloat(); }
float MainWindow::getWaterdecompAiPoc() const { return ui->lineEditWaterdecompAiPoc->text().toFloat(); }
float MainWindow::getWaterdecompGiPoc() const { return ui->lineEditWaterdecompGiPoc->text().toFloat(); }
float MainWindow::getWaterdecompPrefPoc() const { return ui->lineEditWaterdecompPrefPoc->text().toFloat(); }
float MainWindow::getWaterdecompAj() const { return ui->lineEditWaterdecompAj->text().toFloat(); }
float MainWindow::getWaterdecompGj() const { return ui->lineEditWaterdecompGj->text().toFloat(); }
float MainWindow::getWaterdecompRespiration() const { return ui->lineEditWaterdecompRespiration->text().toFloat(); }
float MainWindow::getWaterdecompExcretion() const { return ui->lineEditWaterdecompExcretion->text().toFloat(); }
float MainWindow::getWaterdecompSenescence() const { return ui->lineEditWaterdecompSenescence->text().toFloat(); }
float MainWindow::getWaterdecompMax() const { return ui->lineEditWaterdecompMax->text().toFloat(); }

float MainWindow::getSeddecompAiDetritus() const { return ui->lineEditSeddecompAiDetritus->text().toFloat(); }
float MainWindow::getSeddecompGiDetritus() const { return ui->lineEditSeddecompGiDetritus->text().toFloat(); }
float MainWindow::getSeddecompPrefDetritus() const { return ui->lineEditSeddecompPrefDetritus->text().toFloat(); }
float MainWindow::getSeddecompAj() const { return ui->lineEditSeddecompAj->text().toFloat(); }
float MainWindow::getSeddecompGj() const { return ui->lineEditSeddecompGj->text().toFloat(); }
float MainWindow::getSeddecompRespiration() const { return ui->lineEditSeddecompRespiration->text().toFloat(); }
float MainWindow::getSeddecompExcretion() const { return ui->lineEditSeddecompExcretion->text().toFloat(); }
float MainWindow::getSeddecompSenescence() const { return ui->lineEditSeddecompSenescence->text().toFloat(); }
float MainWindow::getSeddecompMax() const { return ui->lineEditSeddecompMax->text().toFloat(); }

float MainWindow::getConsumerAiHerbivore() const { return ui->lineEditConsumerAiHerbivore->text().toFloat(); }
float MainWindow::getConsumerGiHerbivore() const { return ui->lineEditConsumerGiHerbivore->text().toFloat(); }
float MainWindow::getConsumerPrefHerbivore() const { return ui->lineEditConsumerPrefHerbivore->text().toFloat(); }
float MainWindow::getConsumerAiSedconsumer() const { return ui->lineEditConsumerAiSedconsumer->text().toFloat(); }
float MainWindow::getConsumerGiSedconsumer() const { return ui->lineEditConsumerGiSedconsumer->text().toFloat(); }
float MainWindow::getConsumerPrefSedconsumer() const { return ui->lineEditConsumerPrefSedconsumer->text().toFloat(); }
float MainWindow::getConsumerAj() const { return ui->lineEditConsumerAj->text().toFloat(); }
float MainWindow::getConsumerGj() const { return ui->lineEditConsumerGj->text().toFloat(); }
float MainWindow::getConsumerRespiration() const { return ui->lineEditConsumerRespiration->text().toFloat(); }
float MainWindow::getConsumerExcretion() const { return ui->lineEditConsumerExcretion->text().toFloat(); }
float MainWindow::getConsumerSenescence() const { return ui->lineEditConsumerSenescence->text().toFloat(); }
float MainWindow::getConsumerEgestion() const { return ui->lineEditConsumerEgestion->text().toFloat(); }
float MainWindow::getConsumerMax() const { return ui->lineEditConsumerMax->text().toFloat(); }

float MainWindow::getMacroSenescence() const { return ui->lineEditMacroSenescence->text().toFloat(); }
float MainWindow::getMacroRespiration() const { return ui->lineEditMacroRespiration->text().toFloat(); }
float MainWindow::getMacroExcretion() const { return ui->lineEditMacroExcretion->text().toFloat();}
float MainWindow::getMacroTemp() const { return ui->lineEditMacroTemp->text().toFloat(); }
float MainWindow::getMacroGross() const { return ui->lineEditMacroGrossCoef->text().toFloat(); }
float MainWindow::getMacroMassMax() const { return ui->lineEditMacroMassMax->text().toFloat(); }
float MainWindow::getMacroVelocityMax() const { return ui->lineEditMacroVelocityMax->text().toFloat(); }

float MainWindow::getSedconsumerAiDetritus() const { return ui->lineEditSedconsumerAiDetritus->text().toFloat(); }
float MainWindow::getSedconsumerGiDetritus() const { return ui->lineEditSedconsumerGiDetritus->text().toFloat(); }
float MainWindow::getSedconsumerPrefDetritus() const { return ui->lineEditSedconsumerPrefDetritus->text().toFloat(); }
float MainWindow::getSedconsumerAiSeddecomp() const { return ui->lineEditSedconsumerAiSeddecomp->text().toFloat(); }
float MainWindow::getSedconsumerGiSeddecomp() const { return ui->lineEditSedconsumerGiSeddecomp->text().toFloat(); }
float MainWindow::getSedconsumerPrefSeddecomp() const { return ui->lineEditSedconsumerPrefSeddecomp->text().toFloat(); }
float MainWindow::getSedconsumerAj() const { return ui->lineEditSedconsumerAj->text().toFloat(); }
float MainWindow::getSedconsumerGj() const { return ui->lineEditSedconsumerGj->text().toFloat(); }
float MainWindow::getSedconsumerRespiration() const { return ui->lineEditSedconsumerRespiration->text().toFloat(); }
float MainWindow::getSedconsumerExcretion() const { return ui->lineEditSedconsumerExcretion->text().toFloat(); }
float MainWindow::getSedconsumerSenescence() const { return ui->lineEditSedconsumerSenescence->text().toFloat(); }
float MainWindow::getSedconsumerMax() const { return ui->lineEditSedconsumerMax->text().toFloat(); }

QString MainWindow::getWhichStock() const { return ui->comboBoxWhichStock->currentText(); }
QString MainWindow::getTempFile() const { return wholeTempFile; }
QString MainWindow::getPARFile() const { return wholePARFile; }

QList<uint16_t> MainWindow::getDaysToRun() const { return daysToRun; }
QList<QString> MainWindow::getHydroMaps() const { return wholeHydroMapFiles; }


/* SETTERS */
void MainWindow::setAdjacent(bool val) { ui->checkBoxAdjacentCells->setChecked(val); }

void MainWindow::setOutputFreq(uint8_t val) { ui->lineEditOutputFreq->setText(QString::number(val)); }
void MainWindow::setTimestep(uint8_t val) { timestepUpdate(val);}

void MainWindow::setKPhyto(float val) { ui->lineEditKPhyto->setText(QString::number(val)); }
void MainWindow::setKMacro(float val) { ui->lineEditKMacro->setText(QString::number(val)); }
void MainWindow::setTSS(float val) { ui->lineEditTSS->setText(QString::number(val)); }

// stock parameters
void MainWindow::setWhichStock(char *stock) { ui->comboBoxWhichStock->setCurrentIndex(stockIndex(stock)); }

void MainWindow::setMacroBase(float val) { ui->lineEditMacro->setText(QString::number(val)); }
void MainWindow::setPhytoBase(float val) { ui->lineEditPhyto->setText(QString::number(val)); }
void MainWindow::setConsumerBase(float val) { ui->lineEditConsumer->setText(QString::number(val)); }
void MainWindow::setDecompBase(float val) { ui->lineEditDecomp->setText(QString::number(val)); }
void MainWindow::setSedconsumerBase(float val) { ui->lineEditSedconsumer->setText(QString::number(val)); }
void MainWindow::setSeddecompBase(float val) { ui->lineEditSeddecomp->setText(QString::number(val)); }
void MainWindow::setHerbivoreBase(float val) { ui->lineEditHerbivore->setText(QString::number(val)); }
void MainWindow::setDetritusBase(float val) { ui->lineEditDetritus->setText(QString::number(val)); }
void MainWindow::setPocBase(float val) { ui->lineEditPoc->setText(QString::number(val)); }
void MainWindow::setDocBase(float val) { ui->lineEditDoc->setText(QString::number(val)); }

void MainWindow::setPhytoSenescence(float val) { ui->lineEditPhytoSenescence->setText(QString::number(val)); }
void MainWindow::setPhytoRespiration(float val) { ui->lineEditPhytoRespiration->setText(QString::number(val)); }
void MainWindow::setPhytoExretion(float val) { ui->lineEditPhytoExcretion->setText(QString::number(val)); }
void MainWindow::setPhytoAj(float val) { ui->lineEditPhytoAj->setText(QString::number(val)); }
void MainWindow::setPhytoGj(float val) { ui->lineEditPhytoGj->setText(QString::number(val)); }

void MainWindow::setHerbivoreAiPhyto(float val) { ui->lineEditHerbivoreAiPhyto->setText(QString::number(val)); }
void MainWindow::setHerbivoreGiPhyto(float val) { ui->lineEditHerbivoreGiPhyto->setText(QString::number(val)); }
void MainWindow::setHerbivorePrefPhyto(float val) { ui->lineEditHerbivorePrefPhyto->setText(QString::number(val)); }
void MainWindow::setHerbivoreAiPeri(float val) { ui->lineEditHerbivoreAiPeri->setText(QString::number(val)); }
void MainWindow::setHerbivoreGiPeri(float val) { ui->lineEditHerbivoreGiPeri->setText(QString::number(val)); }
void MainWindow::setHerbivorePrefPeri(float val) { ui->lineEditHerbivorePrefPeri->setText(QString::number(val)); }
void MainWindow::setHerbivoreAiWaterdecomp(float val) { ui->lineEditHerbivoreAiWaterdecomp->setText(QString::number(val)); }
void MainWindow::setHerbivoreGiWaterdecomp(float val) { ui->lineEditHerbivoreGiWaterdecomp->setText(QString::number(val)); }
void MainWindow::setHerbivorePrefWaterdecomp(float val) { ui->lineEditHerbivorePrefWaterdecomp->setText(QString::number(val)); }
void MainWindow::setHerbivoreAj(float val) { ui->lineEditHerbivoreAj->setText(QString::number(val)); }
void MainWindow::setHerbivoreGj(float val) { ui->lineEditHerbivoreGj->setText(QString::number(val)); }
void MainWindow::setHerbivoreRespiration(float val) { ui->lineEditHerbivoreRespiration->setText(QString::number(val)); }
void MainWindow::setHerbivoreExcretion(float val) { ui->lineEditHerbivoreExcretion->setText(QString::number(val)); }
void MainWindow::setHerbivoreEgestion(float val) { ui->lineEditHerbivoreEgestion->setText(QString::number(val)); }
void MainWindow::setHerbivoreSenescence(float val) { ui->lineEditHerbivoreSenescence->setText(QString::number(val)); }
void MainWindow::setHerbivoreMax(float val) { ui->lineEditHerbivoreMax->setText(QString::number(val)); }

void MainWindow::setWaterdecompAiDoc(float val) { ui->lineEditWaterdecompAiDoc->setText(QString::number(val)); }
void MainWindow::setWaterdecompGiDoc(float val) { ui->lineEditWaterdecompGiDoc->setText(QString::number(val)); }
void MainWindow::setWaterdecompPrefDoc(float val) { ui->lineEditWaterdecompPrefDoc->setText(QString::number(val)); }
void MainWindow::setWaterdecompAiPoc(float val) { ui->lineEditWaterdecompAiPoc->setText(QString::number(val)); }
void MainWindow::setWaterdecompGiPoc(float val) { ui->lineEditWaterdecompGiPoc->setText(QString::number(val)); }
void MainWindow::setWaterdecompPrefPoc(float val) { ui->lineEditWaterdecompPrefPoc->setText(QString::number(val)); }
void MainWindow::setWaterdecompAj(float val) { ui->lineEditWaterdecompAj->setText(QString::number(val)); }
void MainWindow::setWaterdecompGj(float val) { ui->lineEditWaterdecompGj->setText(QString::number(val)); }
void MainWindow::setWaterdecompRespiration(float val) { ui->lineEditWaterdecompRespiration->setText(QString::number(val)); }
void MainWindow::setWaterdecompExcretion(float val) { ui->lineEditWaterdecompExcretion->setText(QString::number(val)); }
void MainWindow::setWaterdecompSenescence(float val) { ui->lineEditWaterdecompSenescence->setText(QString::number(val)); }
void MainWindow::setWaterdecompMax(float val) { ui->lineEditWaterdecompMax->setText(QString::number(val)); }

void MainWindow::setSeddecompAiDetritus(float val) { ui->lineEditSeddecompAiDetritus->setText(QString::number(val)); }
void MainWindow::setSeddecompGiDetritus(float val) { ui->lineEditSeddecompGiDetritus->setText(QString::number(val)); }
void MainWindow::setSeddecompPrefDetritus(float val) { ui->lineEditSeddecompPrefDetritus->setText(QString::number(val)); }
void MainWindow::setSeddecompAj(float val) { ui->lineEditSeddecompAj->setText(QString::number(val)); }
void MainWindow::setSeddecompGj(float val) { ui->lineEditSeddecompGj->setText(QString::number(val)); }
void MainWindow::setSeddecompRespiration(float val) { ui->lineEditSeddecompRespiration->setText(QString::number(val)); }
void MainWindow::setSeddecompExcretion(float val) { ui->lineEditSeddecompExcretion->setText(QString::number(val)); }
void MainWindow::setSeddecompSenescence(float val) { ui->lineEditSeddecompSenescence->setText(QString::number(val)); }
void MainWindow::setSeddecompMax(float val) { ui->lineEditSeddecompMax->setText(QString::number(val)); }

void MainWindow::setConsumerAiHerbivore(float val) { ui->lineEditConsumerAiHerbivore->setText(QString::number(val)); }
void MainWindow::setConsumerGiHerbivore(float val) { ui->lineEditConsumerGiHerbivore->setText(QString::number(val)); }
void MainWindow::setConsumerPrefHerbivore(float val) { ui->lineEditConsumerPrefHerbivore->setText(QString::number(val)); }
void MainWindow::setConsumerAiSedconsumer(float val) { ui->lineEditConsumerAiSedconsumer->setText(QString::number(val)); }
void MainWindow::setConsumerGiSedconsumer(float val) { ui->lineEditConsumerGiSedconsumer->setText(QString::number(val)); }
void MainWindow::setConsumerPrefSedconsumer(float val) { ui->lineEditConsumerPrefSedconsumer->setText(QString::number(val)); }
void MainWindow::setConsumerAj(float val) { ui->lineEditConsumerAj->setText(QString::number(val)); }
void MainWindow::setConsumerGj(float val) { ui->lineEditConsumerGj->setText(QString::number(val)); }
void MainWindow::setConsumerRespiration(float val) { ui->lineEditConsumerRespiration->setText(QString::number(val)); }
void MainWindow::setConsumerExcretion(float val) { ui->lineEditConsumerExcretion->setText(QString::number(val)); }
void MainWindow::setConsumerSenescence(float val) { ui->lineEditConsumerSenescence->setText(QString::number(val)); }
void MainWindow::setConsumerEgestion(float val) { ui->lineEditConsumerEgestion->setText(QString::number(val)); }
void MainWindow::setConsumerMax(float val) { ui->lineEditConsumerMax->setText(QString::number(val)); }

void MainWindow::setMacroSenescence(float val) { ui->lineEditMacroSenescence->setText(QString::number(val)); }
void MainWindow::setMacroRespiration(float val) { ui->lineEditMacroRespiration->setText(QString::number(val)); }
void MainWindow::setMacroExcretion(float val) { ui->lineEditMacroExcretion->setText(QString::number(val)); }
void MainWindow::setMacroTemp(float val) { ui->lineEditMacroTemp->setText(QString::number(val)); }
void MainWindow::setMacroGross(float val) { ui->lineEditMacroGrossCoef->setText(QString::number(val)); }
void MainWindow::setMacroMassMax(float val) { ui->lineEditMacroMassMax->setText(QString::number(val)); }
void MainWindow::setMacroVelocityMax(float val) { ui->lineEditMacroVelocityMax->setText(QString::number(val)); }

void MainWindow::setSedconsumerAiDetritus(float val) { ui->lineEditSedconsumerAiDetritus->setText(QString::number(val)); }
void MainWindow::setSedconsumerGiDetritus(float val) { ui->lineEditSedconsumerGiDetritus->setText(QString::number(val)); }
void MainWindow::setSedconsumerPrefDetritus(float val) { ui->lineEditSedconsumerPrefDetritus->setText(QString::number(val)); }
void MainWindow::setSedconsumerAiSeddecomp(float val) { ui->lineEditSedconsumerAiSeddecomp->setText(QString::number(val)); }
void MainWindow::setSedconsumerGiSeddecomp(float val) { ui->lineEditSedconsumerGiSeddecomp->setText(QString::number(val)); }
void MainWindow::setSedconsumerPrefSeddecomp(float val) { ui->lineEditSedconsumerPrefSeddecomp->setText(QString::number(val)); }
void MainWindow::setSedconsumerAj(float val) { ui->lineEditSedconsumerAj->setText(QString::number(val)); }
void MainWindow::setSedconsumerGj(float val) { ui->lineEditSedconsumerGj->setText(QString::number(val)); }
void MainWindow::setSedconsumerRespiration(float val) { ui->lineEditSedconsumerRespiration->setText(QString::number(val)); }
void MainWindow::setSedconsumerExcretion(float val) { ui->lineEditSedconsumerExcretion->setText(QString::number(val)); }
void MainWindow::setSedconsumerSenescence(float val) { ui->lineEditSedconsumerSenescence->setText(QString::number(val)); }
void MainWindow::setSedconsumerMax(float val) { ui->lineEditSedconsumerMax->setText(QString::number(val)); }

void MainWindow::setTempFile(char* filename)
{
    wholeTempFile = QString(filename);
    ui->labelTempFile->setText(stripFile(tr(filename)));
}

void MainWindow::setPARFile(char* filename)
{
    wholePARFile = QString(filename);
    ui->labelPARFile->setText(stripFile(tr(filename)));
}

void MainWindow::setHydroMaps(char** filenames, uint16_t* daysToRun, size_t num)
{
    for (size_t index = 0; index < num; index++)
    {
        addHydroMap(filenames[index], QString::number(daysToRun[index]), true);
    }
}

/* END public functions */

/* BEGIN private functions */

void MainWindow::clearErrors() const
{
    displayErrors("None", false);
}

bool MainWindow::isBoxFilled(QLineEdit * const input) const
{
    return !input->text().isEmpty();
}

bool MainWindow::isFileSelected(QLabel * const input) const
{
    return !(input->text().isEmpty() || input->text() == QString("None"));
}

bool MainWindow::isStockSelected(QCheckBox * const input) const
{
    return input->isChecked();
}

int MainWindow::stockIndex(char* stock) const
{
    // if not found, just default to 0
    int index = ui->comboBoxWhichStock->findText(stock);
    return (index < 0) ? 0 : index;
}

void MainWindow::displayErrors(const char *message, bool showConfig) const
{
    if (showConfig)
    {
        setTab(CONFIGURATION);
    }
    ui->textBrowserErrors->setText(tr(message));
}

void MainWindow::addHydroMap(QString file, QString days, bool addInfo, bool display)
{
    if (addInfo)
    {
        wholeHydroMapFiles.append(file);
        daysToRun.append(days.toInt());
        file = stripFile(file);
    }
    if (display)
    {
        QString output = file + ": " + days + " Day" + (days != "1" ? "s" : "");
        ui->listWidgetHydroMap->addItem(new QListWidgetItem(output, ui->listWidgetHydroMap));
    }
}

QString MainWindow::stripFile(QString path) const
{
    int lastSlashIndex = path.lastIndexOf("/");
    return path.mid(lastSlashIndex + 1);
}

uint16_t MainWindow::parseDaysToRun(QListWidgetItem* item) const
{
    QString text = item->text();
    size_t colonIndex = text.lastIndexOf(':');
    size_t daysIndex = text.indexOf('D', colonIndex + 2);
    size_t size = daysIndex - colonIndex - 3;

    return atoi(text.toStdString().substr(colonIndex + 2, size).c_str());
}

QString MainWindow::parseHydroMapName(QListWidgetItem* item) const
{
    QString text = item->text();
    size_t colonIndex = text.lastIndexOf(':');

    return text.mid(0, colonIndex);
}

void MainWindow::getAllInput()
{
    // TODO: is this confusing with the different naming conventions?
    QList<QString> maps = getHydroMaps();
    QList<uint16_t> days = getDaysToRun();
    for(int i = 0; i < maps.size(); i++){
        model.set_hydro_filenames(maps[i], days[i]);
    }
    model.set_par_file(getPARFile().toStdString().c_str());
    model.set_temperature_file(getTempFile().toStdString().c_str());
    model.set_timestep(getTimestep());
    // TODO: need separate dropdown for this, re-configure GUI a bit
    model.set_whichstock(getWhichStock().toStdString().c_str());
    model.set_TSS(getTSS());
    model.set_k_phyto(getKPhyto());
    model.set_k_macro(getKMacro());
    model.set_output_frequency(getOutputFreq());
    // TODO: is this the "adjacent cells only" boolean?
    model.set_flow_corners(getAdjacent());

    getAllStockInput(); // There are so many, it would be best to separate this

    //saveConfiguration(QString(defaultFileLocation())); // save configuration for next time
}

void MainWindow::getAllStockInput()
{
    set_stocks(getMacroBase(),
               getPhytoBase(),
               getDecompBase(),
               getSeddecompBase(),
               getHerbivoreBase(),
               getSedconsumerBase(),
               getDocBase(),
               getPocBase(),
               getDetritusBase(),
               getConsumerBase());

    // All values with /24 at the end are per hour
    //   values passed in as per day values
    model.set_senescence_phyto(getPhytoSenescence()/24);
    model.set_respiration_phyto(getPhytoRespiration()/24);
    model.set_excretion_phyto(getPhytoExcretion()/24);
    model.set_aj_phyto(getPhytoAj());
    model.set_gj_phyto(getPhytoGj());

    model.set_ai_herbivore_phyto(getHerbivoreAiPhyto());
    model.set_gi_herbivore_phyto(getHerbivoreGiPhyto());
    model.set_pref_herbivore_phyto(getHerbivorePrefPhyto());
    model.set_ai_herbivore_peri(getHerbivoreAiPeri());
    model.set_gi_herbivore_peri(getHerbivoreGiPeri());
    model.set_pref_herbivore_peri(getHerbivorePrefPeri());
    model.set_ai_herbivore_waterdecomp(getHerbivoreAiWaterdecomp());
    model.set_gi_herbivore_waterdecomp(getHerbivoreGiWaterdecomp());
    model.set_pref_herbivore_waterdecomp(getHerbivorePrefWaterdecomp());
    model.set_aj_herbivore(getHerbivoreAj());
    model.set_gj_herbivore(getHerbivoreGj());
    model.set_respiration_herbivore(getHerbivoreRespiration()/24);
    model.set_excretion_herbivore(getHerbivoreExcretion()/24);
    model.set_herbivore_egestion(getHerbivoreEgestion());
    model.set_senescence_herbivore(getHerbivoreSenescence()/24);
    model.set_max_herbivore(getHerbivoreMax()/24);

    model.set_ai_waterdecomp_doc(getWaterdecompAiDoc());
    model.set_gi_waterdecomp_doc(getWaterdecompGiDoc());
    model.set_pref_waterdecomp_doc(getWaterdecompPrefDoc());
    model.set_ai_waterdecomp_poc(getWaterdecompAiPoc());
    model.set_gi_waterdecomp_poc(getWaterdecompGiPoc());
    model.set_pref_waterdecomp_poc(getWaterdecompPrefPoc());
    model.set_aj_waterdecomp(getWaterdecompAj());
    model.set_gj_waterdecomp(getWaterdecompGj());
    model.set_respiration_waterdecomp(getWaterdecompRespiration()/24);
    model.set_excretion_waterdecomp(getWaterdecompExcretion()/24);
    model.set_senescence_waterdecomp(getWaterdecompSenescence()/24);
    model.set_max_waterdecomp(getWaterdecompMax()/24);

    model.set_ai_seddecomp_detritus(getSeddecompAiDetritus());
    model.set_gi_seddecomp_detritus(getSeddecompGiDetritus());
    model.set_pref_seddecomp_detritus(getSeddecompPrefDetritus());
    model.set_aj_seddecomp(getSeddecompAj());
    model.set_gj_seddecomp(getSeddecompGj());
    model.set_respiration_seddecomp(getSeddecompRespiration()/24);
    model.set_excretion_seddecomp(getSeddecompExcretion()/24);
    model.set_senescence_seddecomp(getSeddecompSenescence()/24);
    model.set_max_seddecomp(getSeddecompMax()/24);

    model.set_ai_consum_herbivore(getConsumerAiHerbivore());
    model.set_gi_consum_herbivore(getConsumerGiHerbivore());
    model.set_pref_consum_herbivore(getConsumerPrefHerbivore());
    model.set_ai_consum_sedconsumer(getConsumerAiSedconsumer());
    model.set_gi_consum_sedconsumer(getConsumerGiSedconsumer());
    model.set_pref_consum_sedconsumer(getConsumerPrefSedconsumer());
    model.set_aj_consum(getConsumerAj());
    model.set_gj_consum(getConsumerGj());
    model.set_respiration_consum(getConsumerRespiration()/24);
    model.set_excretion_consum(getConsumerExcretion()/24);
    model.set_senescence_consum(getConsumerSenescence()/24);
    model.set_consum_egestion(getConsumerEgestion());
    model.set_max_consum(getConsumerMax()/24);

    model.set_sen_macro_coef(getMacroSenescence()/24);
    model.set_resp_macro_coef(getMacroRespiration()/24);
    model.set_excretion_macro(getMacroExcretion());
    model.set_macro_base_temp(getMacroTemp());
    model.set_gross_macro_coef(getMacroGross());
    model.set_macro_mass_max(getMacroMassMax());
    model.set_macro_vel_max(getMacroVelocityMax());

    model.set_ai_sedconsumer_detritus(getSedconsumerAiDetritus());
    model.set_gi_sedconsumer_detritus(getSedconsumerGiDetritus());
    model.set_pref_sedconsumer_detritus(getSedconsumerPrefDetritus());
    model.set_ai_sedconsumer_seddecomp(getSedconsumerAiSeddecomp());
    model.set_gi_sedconsumer_seddecomp(getSedconsumerGiSeddecomp());
    model.set_pref_sedconsumer_seddecomp(getSedconsumerPrefSeddecomp());
    // TODO: peri?
    model.set_aj_sedconsumer(getSedconsumerAj());
    model.set_gj_sedconsumer(getSedconsumerGj());
    model.set_respiration_sedconsumer(getSedconsumerRespiration()/24);
    model.set_excretion_sedconsumer(getSedconsumerExcretion()/24);
    model.set_senescence_sedconsumer(getSedconsumerSenescence()/24);
    model.set_max_sedconsumer(getSedconsumerMax()/24);
}

void MainWindow::dischargeToHydro(QString file)
{
    ifstream fStream;
    fStream.open(file.toStdString().c_str());
    string str;

    // TODO: need a better way to do this
    QString hydroMapBase(defaultFileLocation());
    hydroMapBase.append("/HydroSets");

    std::getline(fStream, str);
    size_t count = 1;
    // TODO: this requires an empty line at the end of the discharge file
    while (!str.empty())
    {
        int hydro = atoi(str.c_str());
        QString hydroFile = intToHydroFile(hydro, hydroMapBase);
        // TODO: do a smart update of count
        addHydroMap(hydroFile, QString::number(count), true, false);
        std::getline(fStream, str);
    }
    fStream.close();
}

QString MainWindow::intToHydroFile(int hydro, QString base) const
{
    // TODO: should this round?
    QString file("0k-new.txt");
    if (hydro < 10000)
    {
        hydro = 10000;
    }
    hydro += 5000; // this is to make rounding accurate
    file.prepend(QString::number(hydro/10000));
    return base + "/" + file;
}

void MainWindow::compressHydroFiles()
{
    if (wholeHydroMapFiles.isEmpty())
    {
        return;
    }

    QList<QString> newFiles;
    QList<uint16_t> newDays;
    size_t size = wholeHydroMapFiles.size();

    QString currFile = wholeHydroMapFiles.at(0);
    size_t count = daysToRun.at(0);
    for (size_t i = 1; i < size; i++)
    {
        if (currFile.compare(wholeHydroMapFiles.at(i)) == 0) // they are the same
        {
            count += daysToRun.at(i);
        }
        else // they are different, add currFile to list
        {
            newFiles.append(currFile);
            newDays.append(count);
            currFile = wholeHydroMapFiles.at(i);
            count = daysToRun.at(i);
        }
    }
    newFiles.append(currFile);
    newDays.append(count);

    wholeHydroMapFiles = newFiles;
    daysToRun = newDays;
    displayHydroFiles();
}

void MainWindow::displayHydroFiles()
{
    clearHydroFiles();
    for (size_t i = 0; i < getNumHydroMaps(); i++)
    {
        addHydroMap(stripFile(wholeHydroMapFiles.at(i)), QString::number(daysToRun.at(i)), false);
    }
}

void MainWindow::clearHydroFiles()
{
    ui->listWidgetHydroMap->clear();
}

const char* MainWindow::qstringToCStr(const QString & input) const
{
    // TODO: this function has serious scoping problems, the returned char* is immediately invalid
    return input.toStdString().c_str();
}

QString MainWindow::defaultFileLocation() const
{
    // change output to wherever data dir is
    return  QDir::currentPath().append("/data");
}

void MainWindow::setTab(MainWindow::Tab tab) const
{
    ui->tabWidget->setCurrentIndex(tab);
}

/* END private functions */
