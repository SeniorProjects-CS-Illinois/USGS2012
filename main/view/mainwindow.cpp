#include "mainwindow.h"
#include <iostream>

using std::ifstream;
using std::string;

/** TODO
 *      - units in tool tips for configuration input
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect signals from progress thread
    connect(&progressThread, SIGNAL(progressPercentUpdate(int)), this, SLOT(progressPercentUpdate(int)));
    connect(&progressThread, SIGNAL(progressTimeUpdate(int, int)), this, SLOT(progressTimeUpdate(int, int)));
    connect(&progressThread, SIGNAL(finished()), this, SLOT(finished()));
    connect(&progressThread, SIGNAL(imageUpdate(QImage)), this, SLOT(imageUpdate(QImage)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete getCurrentModel();
}

/* BEGIN public slots */

void MainWindow::selectHydroMapClicked()
{
    // if the currently selected hydro map was not added, remove it
    if (uiConfig.hydroMaps.size() != uiConfig.daysToRun.size())
    {
        uiConfig.hydroMaps.pop_back();
    }

    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Hydro Map File"),
                                                    Files::defaultFileLocation(), tr("Text Files (*.txt)"));

    // make sure a hydro map file was selected
    if (!selected.isEmpty())
    {
        uiConfig.hydroMaps.append(selected);
        QString filename = Files::stripFile(selected);
        ui->labelHydroMap->setText(filename);
        ui->labelHydroMap->setToolTip(filename);
    }
}

void MainWindow::addHydroMapClicked()
{
    QString errorMessage;
    if (!UI::isBoxNumerical(ui->lineEditDaysToRun))
    {
        displayErrors("Need to insert # days to run");
        return;
    }
    if (!UI::isFileSelected(ui->labelHydroMap))
    {
        displayErrors("No hydro map file selected");
        return;
    }

    // filename already added to list, but days to run not added
    uint16_t days = ui->lineEditDaysToRun->text().toInt();
    uiConfig.daysToRun.append(days);

    addHydroMap(ui->labelHydroMap->text(), days, false);
}

void MainWindow::removeHydroMapClicked()
{
    QListWidget* list = ui->listWidgetHydroMap;
    QMutableVectorIterator<QString> itHydro(uiConfig.hydroMaps);
    QMutableVectorIterator<uint16_t> itDays(uiConfig.daysToRun);
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
    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Discharge File"),
                                                    Files::defaultFileLocation(), tr("Text Files (*.txt)"));

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
    selectFile(ui->labelTempFile, uiConfig.tempFile,
               tr("Select Temperature Data File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectPARFileClicked()
{
    selectFile(ui->labelPARFile, uiConfig.parFile,
               tr("Select PAR Data File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile1Clicked()
{
    selectFile(ui->labelHydroFile1, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile2Clicked()
{
    selectFile(ui->labelHydroFile2, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile3Clicked()
{
    selectFile(ui->labelHydroFile3, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile4Clicked()
{
    selectFile(ui->labelHydroFile4, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile5Clicked()
{
    selectFile(ui->labelHydroFile5, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile6Clicked()
{
    selectFile(ui->labelHydroFile6, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile7Clicked()
{
    selectFile(ui->labelHydroFile7, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile8Clicked()
{
    selectFile(ui->labelHydroFile8, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile9Clicked()
{
    selectFile(ui->labelHydroFile9, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::selectHydroFile10Clicked()
{
    selectFile(ui->labelHydroFile10, uiConfig.parFile,
               tr("Select Hydro File"), tr("Text Files (*.txt)"));
}

void MainWindow::runClicked()
{
    clearOutput();

    // check if all input is valid
    if (!verifyAllInput())
    {
        // if not, do nothing (errors will be displayed)
        return;
    }

    // set model values
    Configuration modelConfig;
    getAllInput(modelConfig);

    delete getCurrentModel();

    RiverModel * model = new RiverModel; // where to free this?
    model->setConfiguration(modelConfig);

    modelThread.setModel(model);
    progressThread.setModel(model);

    modelThread.start();
    progressThread.start();

    // open output tab
    setTab(OUTPUT);

    // disable run button for now
    disableRun();
}

void MainWindow::clearOutput() const
{
    progressTimeUpdate(0, 0);
    ui->progressBar->reset();
    ui->labelImageOutput->clear();
}

void MainWindow::whichstockChanged(QString const & newStock)
{
    RiverModel * model = getCurrentModel();
    if (model == NULL)
    {
        return;
    }

    model->setWhichStock(newStock);

    Status status = model->getStatus();
    // TODO: if no images available, don't do this
    if (    status.getState() == Status::COMPLETE
         || status.getState() == Status::RUNNING
         || status.getState() == Status::PAUSED)
    {
        imageUpdate(model->getImage(newStock));
    }
}

void MainWindow::maxFlow1Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow1, ui->lineEditMinFlow2,  1); }
void MainWindow::minFlow2Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow2, ui->lineEditMaxFlow1, -1); }

void MainWindow::maxFlow2Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow2, ui->lineEditMinFlow3,  1); }
void MainWindow::minFlow3Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow3, ui->lineEditMaxFlow2, -1); }

void MainWindow::maxFlow3Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow3, ui->lineEditMinFlow4,  1); }
void MainWindow::minFlow4Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow4, ui->lineEditMaxFlow3, -1); }

void MainWindow::maxFlow4Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow4, ui->lineEditMinFlow5,  1); }
void MainWindow::minFlow5Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow5, ui->lineEditMaxFlow4, -1); }

void MainWindow::maxFlow5Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow5, ui->lineEditMinFlow6,  1); }
void MainWindow::minFlow6Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow6, ui->lineEditMaxFlow5, -1); }

void MainWindow::maxFlow6Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow6, ui->lineEditMinFlow7,  1); }
void MainWindow::minFlow7Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow7, ui->lineEditMaxFlow6, -1); }

void MainWindow::maxFlow7Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow7, ui->lineEditMinFlow8,  1); }
void MainWindow::minFlow8Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow8, ui->lineEditMaxFlow7, -1); }

void MainWindow::maxFlow8Changed() { copyIntDisplaywithOffset(ui->lineEditMaxFlow8, ui->lineEditMinFlow9,  1); }
void MainWindow::minFlow9Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow9, ui->lineEditMaxFlow8, -1); }

void MainWindow::maxFlow9Changed()  { copyIntDisplaywithOffset(ui->lineEditMaxFlow9,  ui->lineEditMinFlow10,  1); }
void MainWindow::minFlow10Changed() { copyIntDisplaywithOffset(ui->lineEditMinFlow10, ui->lineEditMaxFlow9,  -1); }

void MainWindow::finished() const
{
    enableRun();
}

void MainWindow::enableRun() const
{
    UI::enableButton(ui->pushButtonRun);
}

void MainWindow::disableRun() const
{
    UI::disableButton(ui->pushButtonRun);
}

void MainWindow::timestepUpdate(int newVal) const
{
    ui->horizontalSliderTimestep->setValue(newVal);
    ui->horizontalSliderTimestep->setToolTip(QString::number(newVal));
    ui->labelTimestepVal->setText(QString::number(newVal));
    ui->labelTimestepVal->move(320 + (140*newVal)/60, ui->labelTimestepVal->y());
}

void MainWindow::progressPercentUpdate(int percent) const
{
    ui->progressBar->setValue(percent);
}

void MainWindow::progressTimeUpdate(int elapsed, int remaining) const
{
    ui->labelTimeElapsedValue->setText(QString::number(elapsed));
    ui->labelTimeRemainingValue->setText(QString::number(remaining));
}

void MainWindow::imageUpdate(QImage const & stockImage) const
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
                                                Files::defaultFileLocation(), tr("Config Files (*.conf)"));
    if (!name.isEmpty())
    {
        saveConfiguration(name);
    }
}

void MainWindow::saveConfiguration(QString const & file) const
{
    Configuration conf;
    getAllInput(conf);
    conf.write(file);
}

void MainWindow::loadConfiguration()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open Configuration"),
                                                Files::defaultFileLocation(), tr("Config Files (*.conf)"));
    if (!name.isEmpty())
    {
        loadConfiguration(name);
    }
}

RiverModel* MainWindow::getCurrentModel() const
{
    return modelThread.getCurrentModel();
}

void MainWindow::loadConfiguration(QString const & file)
{
    Configuration conf;
    conf.read(file);

    // basic values
    setAdjacent(conf.adjacent);
    setOutputFreq(conf.outputFreq);
    setTimestep(conf.timestep);
    setTSS(conf.tss);
    setKPhyto(conf.kPhyto);
    setKMacro(conf.kMacro);

    // stock parameters
    setWhichStock(conf.whichStock);

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

/* GETTERS */
bool MainWindow::getAdjacent() const { return ui->checkBoxAdjacentCells->isChecked(); }

uint8_t MainWindow::getOutputFreq() const { return ui->lineEditOutputFreq->text().toInt(); }
uint8_t MainWindow::getTimestep() const { return ui->horizontalSliderTimestep->value(); }
uint16_t MainWindow::getNumHydroMaps() const { return uiConfig.hydroMaps.size(); }

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
QString MainWindow::getTempFile() const { return uiConfig.tempFile; }
QString MainWindow::getPARFile() const { return uiConfig.parFile; }

QVector<uint16_t> MainWindow::getDaysToRun() const { return uiConfig.daysToRun; }
QVector<QString> MainWindow::getHydroMaps() const { return uiConfig.hydroMaps; }


/* SETTERS */
void MainWindow::setAdjacent(bool val) { ui->checkBoxAdjacentCells->setChecked(val); uiConfig.adjacent = val; }

void MainWindow::setOutputFreq(uint8_t val) { ui->lineEditOutputFreq->setText(QString::number(val)); uiConfig.outputFreq = val; }
void MainWindow::setTimestep(uint8_t val) { timestepUpdate(val); uiConfig.timestep = val; }

void MainWindow::setKPhyto(float val) { ui->lineEditKPhyto->setText(QString::number(val)); uiConfig.kPhyto = val; }
void MainWindow::setKMacro(float val) { ui->lineEditKMacro->setText(QString::number(val)); uiConfig.kMacro = val; }
void MainWindow::setTSS(float val) { ui->lineEditTSS->setText(QString::number(val)); uiConfig.tss = val; }

// stock parameters
void MainWindow::setWhichStock(QString const & stock) { ui->comboBoxWhichStock->setCurrentIndex(UI::comboBoxIndex(ui->comboBoxWhichStock, stock)); uiConfig.whichStock = stock; }

void MainWindow::setMacroBase(float val) { ui->lineEditMacro->setText(QString::number(val)); uiConfig.macro = val; }
void MainWindow::setPhytoBase(float val) { ui->lineEditPhyto->setText(QString::number(val)); uiConfig.phyto = val; }
void MainWindow::setConsumerBase(float val) { ui->lineEditConsumer->setText(QString::number(val)); uiConfig.consumer = val; }
void MainWindow::setDecompBase(float val) { ui->lineEditDecomp->setText(QString::number(val)); uiConfig.decomp = val; }
void MainWindow::setSedconsumerBase(float val) { ui->lineEditSedconsumer->setText(QString::number(val)); uiConfig.sedconsumer = val; }
void MainWindow::setSeddecompBase(float val) { ui->lineEditSeddecomp->setText(QString::number(val)); uiConfig.seddecomp = val; }
void MainWindow::setHerbivoreBase(float val) { ui->lineEditHerbivore->setText(QString::number(val)); uiConfig.herbivore = val; }
void MainWindow::setDetritusBase(float val) { ui->lineEditDetritus->setText(QString::number(val)); uiConfig.detritus = val; }
void MainWindow::setPocBase(float val) { ui->lineEditPoc->setText(QString::number(val)); uiConfig.poc = val; }
void MainWindow::setDocBase(float val) { ui->lineEditDoc->setText(QString::number(val)); uiConfig.doc = val; }

void MainWindow::setPhytoSenescence(float val) { ui->lineEditPhytoSenescence->setText(QString::number(val)); uiConfig.phytoSenescence = val; }
void MainWindow::setPhytoRespiration(float val) { ui->lineEditPhytoRespiration->setText(QString::number(val)); uiConfig.phytoRespiration = val; }
void MainWindow::setPhytoExretion(float val) { ui->lineEditPhytoExcretion->setText(QString::number(val)); uiConfig.phytoExcretion = val; }
void MainWindow::setPhytoAj(float val) { ui->lineEditPhytoAj->setText(QString::number(val)); uiConfig.phytoAj = val; }
void MainWindow::setPhytoGj(float val) { ui->lineEditPhytoGj->setText(QString::number(val)); uiConfig.phytoGj = val; }

void MainWindow::setHerbivoreAiPhyto(float val) { ui->lineEditHerbivoreAiPhyto->setText(QString::number(val)); uiConfig.herbivoreAiPhyto = val; }
void MainWindow::setHerbivoreGiPhyto(float val) { ui->lineEditHerbivoreGiPhyto->setText(QString::number(val)); uiConfig.herbivoreGiPhyto = val; }
void MainWindow::setHerbivorePrefPhyto(float val) { ui->lineEditHerbivorePrefPhyto->setText(QString::number(val)); uiConfig.herbivorePrefPhyto = val; }
void MainWindow::setHerbivoreAiPeri(float val) { ui->lineEditHerbivoreAiPeri->setText(QString::number(val)); uiConfig.herbivoreAiPeri = val; }
void MainWindow::setHerbivoreGiPeri(float val) { ui->lineEditHerbivoreGiPeri->setText(QString::number(val)); uiConfig.herbivoreGiPeri = val; }
void MainWindow::setHerbivorePrefPeri(float val) { ui->lineEditHerbivorePrefPeri->setText(QString::number(val)); uiConfig.herbivorePrefPeri = val; }
void MainWindow::setHerbivoreAiWaterdecomp(float val) { ui->lineEditHerbivoreAiWaterdecomp->setText(QString::number(val)); uiConfig.herbivoreAiWaterdecomp = val; }
void MainWindow::setHerbivoreGiWaterdecomp(float val) { ui->lineEditHerbivoreGiWaterdecomp->setText(QString::number(val)); uiConfig.herbivoreGiWaterdecomp = val; }
void MainWindow::setHerbivorePrefWaterdecomp(float val) { ui->lineEditHerbivorePrefWaterdecomp->setText(QString::number(val)); uiConfig.herbivorePrefWaterdecomp = val; }
void MainWindow::setHerbivoreAj(float val) { ui->lineEditHerbivoreAj->setText(QString::number(val)); uiConfig.herbivoreAj = val; }
void MainWindow::setHerbivoreGj(float val) { ui->lineEditHerbivoreGj->setText(QString::number(val)); uiConfig.herbivoreGj = val; }
void MainWindow::setHerbivoreRespiration(float val) { ui->lineEditHerbivoreRespiration->setText(QString::number(val)); uiConfig.herbivoreRespiration = val; }
void MainWindow::setHerbivoreExcretion(float val) { ui->lineEditHerbivoreExcretion->setText(QString::number(val)); uiConfig.herbivoreExcretion = val; }
void MainWindow::setHerbivoreEgestion(float val) { ui->lineEditHerbivoreEgestion->setText(QString::number(val)); uiConfig.herbivoreEgestion = val; }
void MainWindow::setHerbivoreSenescence(float val) { ui->lineEditHerbivoreSenescence->setText(QString::number(val)); uiConfig.herbivoreSenescence = val; }
void MainWindow::setHerbivoreMax(float val) { ui->lineEditHerbivoreMax->setText(QString::number(val)); uiConfig.herbivoreMax = val; }

void MainWindow::setWaterdecompAiDoc(float val) { ui->lineEditWaterdecompAiDoc->setText(QString::number(val)); uiConfig.waterdecompAiDoc = val; }
void MainWindow::setWaterdecompGiDoc(float val) { ui->lineEditWaterdecompGiDoc->setText(QString::number(val)); uiConfig.waterdecompGiDoc = val; }
void MainWindow::setWaterdecompPrefDoc(float val) { ui->lineEditWaterdecompPrefDoc->setText(QString::number(val)); uiConfig.waterdecompPrefDoc = val; }
void MainWindow::setWaterdecompAiPoc(float val) { ui->lineEditWaterdecompAiPoc->setText(QString::number(val)); uiConfig.waterdecompAiPoc = val; }
void MainWindow::setWaterdecompGiPoc(float val) { ui->lineEditWaterdecompGiPoc->setText(QString::number(val)); uiConfig.waterdecompGiPoc = val; }
void MainWindow::setWaterdecompPrefPoc(float val) { ui->lineEditWaterdecompPrefPoc->setText(QString::number(val)); uiConfig.waterdecompPrefPoc = val; }
void MainWindow::setWaterdecompAj(float val) { ui->lineEditWaterdecompAj->setText(QString::number(val)); uiConfig.waterdecompAj = val; }
void MainWindow::setWaterdecompGj(float val) { ui->lineEditWaterdecompGj->setText(QString::number(val)); uiConfig.waterdecompGj = val; }
void MainWindow::setWaterdecompRespiration(float val) { ui->lineEditWaterdecompRespiration->setText(QString::number(val)); uiConfig.waterdecompExcretion = val; }
void MainWindow::setWaterdecompExcretion(float val) { ui->lineEditWaterdecompExcretion->setText(QString::number(val)); uiConfig.waterdecompExcretion = val; }
void MainWindow::setWaterdecompSenescence(float val) { ui->lineEditWaterdecompSenescence->setText(QString::number(val)); uiConfig.waterdecompSenescence = val; }
void MainWindow::setWaterdecompMax(float val) { ui->lineEditWaterdecompMax->setText(QString::number(val)); uiConfig.waterdecompMax = val; }

void MainWindow::setSeddecompAiDetritus(float val) { ui->lineEditSeddecompAiDetritus->setText(QString::number(val)); uiConfig.seddecompAiDetritus = val; }
void MainWindow::setSeddecompGiDetritus(float val) { ui->lineEditSeddecompGiDetritus->setText(QString::number(val)); uiConfig.seddecompGiDetritus = val; }
void MainWindow::setSeddecompPrefDetritus(float val) { ui->lineEditSeddecompPrefDetritus->setText(QString::number(val)); uiConfig.seddecompPrefDetritus = val; }
void MainWindow::setSeddecompAj(float val) { ui->lineEditSeddecompAj->setText(QString::number(val)); uiConfig.seddecompAj = val; }
void MainWindow::setSeddecompGj(float val) { ui->lineEditSeddecompGj->setText(QString::number(val)); uiConfig.seddecompGj = val; }
void MainWindow::setSeddecompRespiration(float val) { ui->lineEditSeddecompRespiration->setText(QString::number(val)); uiConfig.seddecompRespiration = val; }
void MainWindow::setSeddecompExcretion(float val) { ui->lineEditSeddecompExcretion->setText(QString::number(val)); uiConfig.seddecompExcretion = val; }
void MainWindow::setSeddecompSenescence(float val) { ui->lineEditSeddecompSenescence->setText(QString::number(val)); uiConfig.seddecompSenescence = val; }
void MainWindow::setSeddecompMax(float val) { ui->lineEditSeddecompMax->setText(QString::number(val)); uiConfig.seddecompMax = val; }

void MainWindow::setConsumerAiHerbivore(float val) { ui->lineEditConsumerAiHerbivore->setText(QString::number(val)); uiConfig.consumerAiHerbivore = val; }
void MainWindow::setConsumerGiHerbivore(float val) { ui->lineEditConsumerGiHerbivore->setText(QString::number(val)); uiConfig.consumerGiHerbivore = val; }
void MainWindow::setConsumerPrefHerbivore(float val) { ui->lineEditConsumerPrefHerbivore->setText(QString::number(val)); uiConfig.consumerPrefHerbivore = val; }
void MainWindow::setConsumerAiSedconsumer(float val) { ui->lineEditConsumerAiSedconsumer->setText(QString::number(val)); uiConfig.consumerAiSedconsumer = val; }
void MainWindow::setConsumerGiSedconsumer(float val) { ui->lineEditConsumerGiSedconsumer->setText(QString::number(val)); uiConfig.consumerGiSedconsumer = val; }
void MainWindow::setConsumerPrefSedconsumer(float val) { ui->lineEditConsumerPrefSedconsumer->setText(QString::number(val)); uiConfig.consumerPrefSedconsumer = val; }
void MainWindow::setConsumerAj(float val) { ui->lineEditConsumerAj->setText(QString::number(val)); uiConfig.consumerAj = val; }
void MainWindow::setConsumerGj(float val) { ui->lineEditConsumerGj->setText(QString::number(val)); uiConfig.consumerGj = val; }
void MainWindow::setConsumerRespiration(float val) { ui->lineEditConsumerRespiration->setText(QString::number(val)); uiConfig.consumerRespiration = val; }
void MainWindow::setConsumerExcretion(float val) { ui->lineEditConsumerExcretion->setText(QString::number(val)); uiConfig.consumerExcretion = val; }
void MainWindow::setConsumerSenescence(float val) { ui->lineEditConsumerSenescence->setText(QString::number(val)); uiConfig.consumerSenescence = val; }
void MainWindow::setConsumerEgestion(float val) { ui->lineEditConsumerEgestion->setText(QString::number(val)); uiConfig.consumerEgestion = val; }
void MainWindow::setConsumerMax(float val) { ui->lineEditConsumerMax->setText(QString::number(val)); uiConfig.consumerMax = val; }

void MainWindow::setMacroSenescence(float val) { ui->lineEditMacroSenescence->setText(QString::number(val)); uiConfig.macroSenescence = val; }
void MainWindow::setMacroRespiration(float val) { ui->lineEditMacroRespiration->setText(QString::number(val)); uiConfig.macroRespiration = val; }
void MainWindow::setMacroExcretion(float val) { ui->lineEditMacroExcretion->setText(QString::number(val)); uiConfig.macroExcretion = val; }
void MainWindow::setMacroTemp(float val) { ui->lineEditMacroTemp->setText(QString::number(val)); uiConfig.macroTemp = val; }
void MainWindow::setMacroGross(float val) { ui->lineEditMacroGrossCoef->setText(QString::number(val)); uiConfig.macroGross = val; }
void MainWindow::setMacroMassMax(float val) { ui->lineEditMacroMassMax->setText(QString::number(val)); uiConfig.macroMassMax = val; }
void MainWindow::setMacroVelocityMax(float val) { ui->lineEditMacroVelocityMax->setText(QString::number(val)); uiConfig.macroVelocityMax = val; }

void MainWindow::setSedconsumerAiDetritus(float val) { ui->lineEditSedconsumerAiDetritus->setText(QString::number(val)); uiConfig.sedconsumerAiDetritus = val; }
void MainWindow::setSedconsumerGiDetritus(float val) { ui->lineEditSedconsumerGiDetritus->setText(QString::number(val)); uiConfig.sedconsumerGiDetritus = val; }
void MainWindow::setSedconsumerPrefDetritus(float val) { ui->lineEditSedconsumerPrefDetritus->setText(QString::number(val)); uiConfig.sedconsumerPrefDetritus = val; }
void MainWindow::setSedconsumerAiSeddecomp(float val) { ui->lineEditSedconsumerAiSeddecomp->setText(QString::number(val)); uiConfig.sedconsumerAiSeddecomp = val; }
void MainWindow::setSedconsumerGiSeddecomp(float val) { ui->lineEditSedconsumerGiSeddecomp->setText(QString::number(val)); uiConfig.sedconsumerGiSeddecomp = val; }
void MainWindow::setSedconsumerPrefSeddecomp(float val) { ui->lineEditSedconsumerPrefSeddecomp->setText(QString::number(val)); uiConfig.sedconsumerPrefSeddecomp = val; }
void MainWindow::setSedconsumerAj(float val) { ui->lineEditSedconsumerAj->setText(QString::number(val)); uiConfig.sedconsumerAj = val; }
void MainWindow::setSedconsumerGj(float val) { ui->lineEditSedconsumerGj->setText(QString::number(val)); uiConfig.sedconsumerGj = val; }
void MainWindow::setSedconsumerRespiration(float val) { ui->lineEditSedconsumerRespiration->setText(QString::number(val)); uiConfig.sedconsumerRespiration = val; }
void MainWindow::setSedconsumerExcretion(float val) { ui->lineEditSedconsumerExcretion->setText(QString::number(val)); uiConfig.sedconsumerExcretion = val; }
void MainWindow::setSedconsumerSenescence(float val) { ui->lineEditSedconsumerSenescence->setText(QString::number(val)); uiConfig.sedconsumerSenescence = val; }
void MainWindow::setSedconsumerMax(float val) { ui->lineEditSedconsumerMax->setText(QString::number(val)); uiConfig.sedconsumerMax = val; }

void MainWindow::setTempFile(const QString & filename)
{
    uiConfig.tempFile = filename;
    ui->labelTempFile->setText(Files::stripFile(filename));
}

void MainWindow::setPARFile(const QString & filename)
{
    uiConfig.parFile = filename;
    ui->labelPARFile->setText(Files::stripFile(filename));
}

void MainWindow::setHydroMaps(const QVector<QString> & filenames, const QVector<uint16_t> & days, size_t num)
{
    // first, clear out existing files
    clearHydroFiles();

    // add new files
    uiConfig.numHydroMaps = num;
    for (size_t index = 0; index < num; index++)
    {
        addHydroMap(filenames[index], days[index], true);
    }
}

/* END public functions */

/* BEGIN private functions */

void MainWindow::displayErrors(const QString & message) const
{
    if (message.isEmpty())
    {
        // do nothing and return
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error!");
    msgBox.setText(message);
    msgBox.exec(); // open box and keep it open
}

void MainWindow::addHydroMap(QString file, uint16_t days, bool addInfo, bool display)
{
    if (addInfo)
    {
        uiConfig.hydroMaps.append(file);
        uiConfig.daysToRun.append(days);
        file = Files::stripFile(file);
    }
    if (display)
    {
        QString output = file + ": " + QString::number(days) + " Day" + (days != 1 ? "s" : "");
        ui->listWidgetHydroMap->addItem(new QListWidgetItem(output, ui->listWidgetHydroMap));
    }
}

void MainWindow::copyIntDisplaywithOffset(QLineEdit* from, QLineEdit* to, int offset) const
{
    to->setText(QString::number(from->text().toInt() + offset));
}

void MainWindow::selectFile(QLabel* displayLabel, QString & configVal, const QString & title, const QString & filter)
{
    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, title, Files::defaultFileLocation(), filter);

    // make sure file was selected
    if (!selected.isEmpty())
    {
        configVal = selected;
        QString filename = Files::stripFile(selected);
        displayLabel->setText(filename);
        displayLabel->setToolTip(selected);
    }
}

void MainWindow::getAllInput(Configuration & c) const
{
    c.hydroMaps = getHydroMaps();
    c.numHydroMaps = c.hydroMaps.size();
    c.daysToRun = getDaysToRun();
    c.parFile = getPARFile();
    c.tempFile = getTempFile();
    c.timestep = getTimestep();
    c.whichStock = getWhichStock();
    c.tss = getTSS();
    c.kPhyto = getKPhyto();
    c.kMacro = getKMacro();
    c.outputFreq = getOutputFreq();
    c.adjacent = getAdjacent();

    getAllStockInput(c);
}

void MainWindow::getAllStockInput(Configuration & c) const
{
    c.macro = getMacroBase();
    c.phyto = getPhytoBase();
    c.decomp = getDecompBase();
    c.seddecomp = getSeddecompBase();
    c.herbivore = getHerbivoreBase();
    c.sedconsumer = getSedconsumerBase();
    c.doc = getDocBase();
    c.poc = getPocBase();
    c.detritus = getDetritusBase();
    c.consumer = getConsumerBase();

    c.phytoSenescence = getPhytoSenescence();
    c.phytoRespiration = getPhytoRespiration();
    c.phytoExcretion = getPhytoExcretion();
    c.phytoAj = getPhytoAj();
    c.phytoGj = getPhytoGj();

    c.herbivoreAiPhyto = getHerbivoreAiPhyto();
    c.herbivoreGiPhyto = getHerbivoreGiPhyto();
    c.herbivorePrefPhyto = getHerbivorePrefPhyto();
    c.herbivoreAiPeri = getHerbivoreAiPeri();
    c.herbivoreGiPeri = getHerbivoreGiPeri();
    c.herbivorePrefPeri = getHerbivorePrefPeri();
    c.herbivoreAiWaterdecomp = getHerbivoreAiWaterdecomp();
    c.herbivoreGiWaterdecomp = getHerbivoreGiWaterdecomp();
    c.herbivorePrefWaterdecomp = getHerbivorePrefWaterdecomp();
    c.herbivoreAj = getHerbivoreAj();
    c.herbivoreGj = getHerbivoreGj();
    c.herbivoreRespiration = getHerbivoreRespiration();
    c.herbivoreExcretion = getHerbivoreExcretion();
    c.herbivoreEgestion = getHerbivoreEgestion();
    c.herbivoreSenescence = getHerbivoreSenescence();
    c.herbivoreMax = getHerbivoreMax();

    c.waterdecompAiDoc = getWaterdecompAiDoc();
    c.waterdecompGiDoc = getWaterdecompGiDoc();
    c.waterdecompPrefDoc = getWaterdecompPrefDoc();
    c.waterdecompAiPoc = getWaterdecompAiPoc();
    c.waterdecompGiPoc = getWaterdecompGiPoc();
    c.waterdecompPrefPoc = getWaterdecompPrefPoc();
    c.waterdecompAj = getWaterdecompAj();
    c.waterdecompGj = getWaterdecompGj();
    c.waterdecompRespiration = getWaterdecompRespiration();
    c.waterdecompExcretion = getWaterdecompExcretion();
    c.waterdecompSenescence = getWaterdecompSenescence();
    c.waterdecompMax = getWaterdecompMax();

    c.seddecompAiDetritus = getSeddecompAiDetritus();
    c.seddecompGiDetritus = getSeddecompGiDetritus();
    c.seddecompPrefDetritus = getSeddecompPrefDetritus();
    c.seddecompAj = getSeddecompAj();
    c.seddecompGj = getSeddecompGj();
    c.seddecompRespiration = getSeddecompRespiration();
    c.seddecompExcretion = getSeddecompExcretion();
    c.seddecompSenescence = getSeddecompSenescence();
    c.seddecompMax = getSeddecompMax();

    c.consumerAiHerbivore = getConsumerAiHerbivore();
    c.consumerGiHerbivore = getConsumerGiHerbivore();
    c.consumerPrefHerbivore = getConsumerPrefHerbivore();
    c.consumerAiSedconsumer = getConsumerAiSedconsumer();
    c.consumerGiSedconsumer = getConsumerGiSedconsumer();
    c.consumerPrefSedconsumer = getConsumerPrefSedconsumer();
    c.consumerAj = getConsumerAj();
    c.consumerGj = getConsumerGj();
    c.consumerRespiration = getConsumerRespiration();
    c.consumerExcretion = getConsumerExcretion();
    c.consumerSenescence = getConsumerSenescence();
    c.consumerEgestion = getConsumerEgestion();
    c.consumerMax = getConsumerMax();

    c.macroSenescence = getMacroSenescence();
    c.macroRespiration = getMacroRespiration();
    c.macroExcretion = getMacroExcretion();
    c.macroTemp = getMacroTemp();
    c.macroGross = getMacroGross();
    c.macroMassMax = getMacroMassMax();
    c.macroVelocityMax = getMacroVelocityMax();

    c.sedconsumerAiDetritus = getSedconsumerAiDetritus();
    c.sedconsumerGiDetritus = getSedconsumerGiDetritus();
    c.sedconsumerPrefDetritus = getSedconsumerPrefDetritus();
    c.sedconsumerAiSeddecomp = getSedconsumerAiSeddecomp();
    c.sedconsumerGiSeddecomp = getSedconsumerGiSeddecomp();
    c.sedconsumerPrefSeddecomp = getSedconsumerPrefSeddecomp();
    /****************************************/
    // TODO: allow for this to be user input
    c.sedconsumerAiPeri = 2.0;
    c.sedconsumerGiPeri = 0.02;
    c.sedconsumerPrefPeri = 0.4;
    c.sedconsumerEgestionSeddecomp = 0.35; // what is this?
    c.sedconsumerEgestionDetritus = 0.9; // what is this?
    /****************************************/
    c.sedconsumerAj = getSedconsumerAj();
    c.sedconsumerGj = getSedconsumerGj();
    c.sedconsumerRespiration = getSedconsumerRespiration();
    c.sedconsumerExcretion = getSedconsumerExcretion();
    c.sedconsumerSenescence = getSedconsumerSenescence();
    c.sedconsumerMax = getSedconsumerMax();

    // c.periAj
    // c.periGj <-- these are written to in the model right away, I don't think it is supposed to be user input
}

bool MainWindow::verifyAllInput() const
{
    if (getNumHydroMaps() == 0)
    {
        displayErrors("No Hydromap Files selected");
        return false;
    }

    return  verifyAllStockInput() &&
            verifyNumber(ui->lineEditKMacro, "K-Macro value not filled out or invalid") &&
            verifyNumber(ui->lineEditKPhyto, "K-Phyto value not filled out or invalid") &&
            verifyNumber(ui->lineEditTSS, "TSS value not filled out or invalid") &&
            /* Hydro file flow */
            verifyNumber(ui->lineEditMinFlow1, "Min flow for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow2, "Min flow for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow3, "Min flow for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow4, "Min flow for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow5, "Min flow for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow6, "Min flow for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow7, "Min flow for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow8, "Min flow for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow9, "Min flow for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMinFlow10, "Min flow for the tenth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow1, "Max flow for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow2, "Max flow for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow3, "Max flow for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow4, "Max flow for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow5, "Max flow for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow6, "Max flow for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow7, "Max flow for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow8, "Max flow for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow9, "Max flow for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditMaxFlow10, "Max flow for the tenth hydro file not filled out or invalid") &&
            /* DOC input/output */
            verifyNumber(ui->lineEditInputDoc1, "DOC input for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc2, "DOC input for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc3, "DOC input for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc4, "DOC input for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc5, "DOC input for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc6, "DOC input for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc7, "DOC input for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc8, "DOC input for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc9, "DOC input for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputDoc10, "DOC input for the for the tenth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc1, "DOC output for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc2, "DOC output for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc3, "DOC output for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc4, "DOC output for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc5, "DOC output for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc6, "DOC output for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc7, "DOC output for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc8, "DOC output for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc9, "DOC output for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputDoc10, "DOC output for the for the tenth hydro file not filled out or invalid") &&
            /* POC input/output */
            verifyNumber(ui->lineEditInputPoc1, "POC input for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc2, "POC input for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc3, "POC input for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc4, "POC input for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc5, "POC input for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc6, "POC input for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc7, "POC input for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc8, "POC input for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc9, "POC input for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPoc10, "POC input for the for the tenth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc1, "POC output for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc2, "POC output for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc3, "POC output for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc4, "POC output for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc5, "POC output for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc6, "POC output for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc7, "POC output for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc8, "POC output for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc9, "POC output for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPoc10, "POC output for the for the tenth hydro file not filled out or invalid") &&
            /* Waterdecomp input/output */
            verifyNumber(ui->lineEditInputWaterdecomp1, "Waterdecomp input for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp2, "Waterdecomp input for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp3, "Waterdecomp input for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp4, "Waterdecomp input for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp5, "Waterdecomp input for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp6, "Waterdecomp input for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp7, "Waterdecomp input for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp8, "Waterdecomp input for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp9, "Waterdecomp input for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputWaterdecomp10, "Waterdecomp input for the for the tenth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp1, "Waterdecomp output for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp2, "Waterdecomp output for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp3, "Waterdecomp output for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp4, "Waterdecomp output for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp5, "Waterdecomp output for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp6, "Waterdecomp output for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp7, "Waterdecomp output for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp8, "Waterdecomp output for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp9, "Waterdecomp output for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputWaterdecomp10, "Waterdecomp output for the for the tenth hydro file not filled out or invalid") &&
            /* Phyto input/output */
            verifyNumber(ui->lineEditInputPhyto1, "Phyto input for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto2, "Phyto input for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto3, "Phyto input for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto4, "Phyto input for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto5, "Phyto input for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto6, "Phyto input for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto7, "Phyto input for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto8, "Phyto input for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto9, "Phyto input for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditInputPhyto10, "Phyto input for the for the tenth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto1, "Phyto output for the for the first hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto2, "Phyto output for the for the second hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto3, "Phyto output for the for the third hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto4, "Phyto output for the for the fourth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto5, "Phyto output for the for the fifth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto6, "Phyto output for the for the sixth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto7, "Phyto output for the for the seventh hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto8, "Phyto output for the for the eigth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto9, "Phyto output for the for the ninth hydro file not filled out or invalid") &&
            verifyNumber(ui->lineEditOutputPhyto10, "Phyto output for the for the tenth hydro file not filled out or invalid") &&
            /* Files */
            verifyFile(ui->labelTempFile, "Temperature File not selected") &&
            verifyFile(ui->labelPARFile, "PAR File not selected");
}

bool MainWindow::verifyAllStockInput() const
{
    return  /* Consumer */
            verifyNumber(ui->lineEditConsumer, "Consumer value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerAiHerbivore, "Consumer Ai Herbivore value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerAiSedconsumer, "Consumer Ai Sedconsumer value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerAj, "Consumer Aj value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerEgestion, "Consumer Egestion value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerExcretion, "Consumer Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerGiHerbivore, "Consumer Gi Herbivore value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerGiSedconsumer, "Consumer Gi Sedconsumer value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerGj, "Consumer Gj value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerMax, "Consumer Max value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerPrefHerbivore, "Consumer Pref Herbivore value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerPrefSedconsumer, "Consumer Pref Sedconsumer value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerRespiration, "Consumer Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditConsumerSenescence, "Consumer Senescence value not filled out or invalid") &&
            /* WaterDecomp */
            verifyNumber(ui->lineEditDecomp, "Decomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompAiDoc, "Waterdecomp Ai DOC value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompAiPoc, "Waterdecomp Ai POC value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompAj, "Waterdecomp Aj value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompExcretion, "Waterdecomp Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompGiDoc, "Waterdecomp Gi DOC value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompGiPoc, "Waterdecomp Gi POC value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompGj, "Waterdecomp Gj value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompMax, "Waterdecomp Max value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompPrefDoc, "Waterdecomp Pref DOC value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompPrefPoc, "Waterdecomp Pref POC value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompRespiration, "Waterdecomp Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditWaterdecompSenescence, "Waterdecomp Senescence value not filled out or invalid") &&
            /* Detritus */
            verifyNumber(ui->lineEditDetritus, "Detritus value not filled out or invalid") &&
            /* DOC */
            verifyNumber(ui->lineEditDoc, "DOC value not filled out or invalid") &&
            /* Herbivore */
            verifyNumber(ui->lineEditHerbivore, "Herbivore value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreAiPeri, "Herbivore Ai Peri value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreAiPhyto, "Herbivore Ai Phyto value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreAiWaterdecomp, "Herbivore Ai Waterdecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreAj, "Herbivore Aj value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreEgestion, "Herbivore Egestion value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreExcretion, "Herbivore Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreGiPeri, "Herbivore Gi Peri value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreGiPhyto, "Herbivore Gi Phyto value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreGiWaterdecomp, "Herbivore Gi Waterdecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreGj, "Herbivore Gj value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreMax, "Herbivore Max value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivorePrefPeri, "Herbivore Pref Peri value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivorePrefPhyto, "Herbivore Pref Phyto value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivorePrefWaterdecomp, "Herbivore Pref Waterdecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreRespiration, "Herbivore Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditHerbivoreSenescence, "Herbivore Senescence value not filled out or invalid") &&
            /* Macro */
            verifyNumber(ui->lineEditMacro, "Macro value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroExcretion, "Macro Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroGrossCoef, "Macro Gross Coefficient value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroMassMax, "Macro Mass Max value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroRespiration, "Macro Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroSenescence, "Macro Senescence value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroTemp, "Macro Temp value not filled out or invalid") &&
            verifyNumber(ui->lineEditMacroVelocityMax, "Macro Velocity Max value not filled out or invalid") &&
            /* Phyto */
            verifyNumber(ui->lineEditPhyto, "Phyto value not filled out or invalid") &&
            verifyNumber(ui->lineEditPhytoAj, "Phyto Aj value not filled out or invalid") &&
            verifyNumber(ui->lineEditPhytoExcretion, "Phyto Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditPhytoGj, "Phyto Gj value not filled out or invalid") &&
            verifyNumber(ui->lineEditPhytoRespiration, "Phyto Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditPhytoSenescence, "Phyto Senescence value not filled out or invalid") &&
            /* POC */
            verifyNumber(ui->lineEditPoc, "POC value not filled out or invalid") &&
            /* Sedconsumer */
            verifyNumber(ui->lineEditSedconsumer, "Sedconsumer value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerAiDetritus, "Sedconsumer Ai Detritus value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerAiSeddecomp, "Sedconsumer Ai Seddecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerAj, "Sedconsumer Aj value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerExcretion, "Sedconsumer Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerGiDetritus, "Sedconsumer Gi Detritus value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerGiSeddecomp, "Sedconsumer Gi Seddecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerGj, "Sedconsumer Gj value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerMax, "Sedconsumer Max value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerPrefDetritus, "Sedconsumer Pref Detritus value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerPrefSeddecomp, "Sedconsumer Pref Seddecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerRespiration, "Sedconsumer Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditSedconsumerSenescence, "Sedconsumer Senescence value not filled out or invalid") &&
            /* Seddecomp */
            verifyNumber(ui->lineEditSeddecomp, "Seddecomp value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompAiDetritus, "Seddecomp Ai Detritus value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompAj, "Seddecomp Aj value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompExcretion, "Seddecomp Excretion value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompGiDetritus, "Seddecomp Gi Detritus value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompGj, "Seddecomp Gj value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompMax, "Seddecomp Max value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompPrefDetritus, "Seddecomp Pref Detritus value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompRespiration, "Seddecomp Respiration value not filled out or invalid") &&
            verifyNumber(ui->lineEditSeddecompSenescence, "Seddecomp Senescence value not filled out or invalid or invalid");
}

bool MainWindow::verifyNumber(QLineEdit* widget, const QString & errorMessage) const
{
    if (!UI::isBoxNumerical(widget))
    {
        displayErrors(errorMessage);
        return false;
    }
    return true;
}

bool MainWindow::verifyFile(QLabel* widget, const QString & errorMessage) const
{
    if (!UI::isFileSelected(widget))
    {
        displayErrors(errorMessage);
        return false;
    }
    return true;
}

void MainWindow::dischargeToHydro(const QString & file)
{
    ifstream fStream;
    fStream.open(file.toStdString().c_str());
    string str;

    QString hydroMapBasePath(Files::defaultFileLocation());
    hydroMapBasePath.append("/HydroSets");

    if (!QDir(hydroMapBasePath).exists()) {
        hydroMapBasePath = QFileDialog::getExistingDirectory(this, tr("Select base directory for hydromaps"),
                                          Files::defaultFileLocation(), QFileDialog::ShowDirsOnly);
    }

    while (!fStream.eof())
    {
        std::getline(fStream, str);
        int hydro = atoi(str.c_str());
        QString hydroFile = HydroMaps::intToHydroFile(hydro, hydroMapBasePath);
        addHydroMap(hydroFile, 1, true, false);
    }
    fStream.close();
}

void MainWindow::compressHydroFiles()
{
    if (uiConfig.hydroMaps.isEmpty())
    {
        return;
    }

    QVector<QString> newFiles;
    QVector<uint16_t> newDays;
    size_t size = uiConfig.hydroMaps.size();

    QString currFile = uiConfig.hydroMaps.front();
    size_t count = uiConfig.daysToRun.front();
    for (size_t i = 1; i < size; i++)
    {
        if (currFile.compare(uiConfig.hydroMaps[i]) == 0) // they are the same
        {
            count += uiConfig.daysToRun[i];
        }
        else // they are different, add currFile to list
        {
            newFiles.append(currFile);
            newDays.append(count);
            currFile = uiConfig.hydroMaps[i];
            count = uiConfig.daysToRun[i];
        }
    }
    newFiles.append(currFile);
    newDays.append(count);

    uiConfig.hydroMaps = newFiles;
    uiConfig.daysToRun = newDays;
    displayHydroFiles();
}

void MainWindow::displayHydroFiles()
{
    clearHydroFilesDisplay();
    for (size_t i = 0; i < getNumHydroMaps(); i++)
    {
        addHydroMap(Files::stripFile(uiConfig.hydroMaps[i]), uiConfig.daysToRun[i], false);
    }
}

void MainWindow::clearHydroFilesDisplay() const
{
    ui->listWidgetHydroMap->clear();
}

void MainWindow::clearHydroFiles()
{
    clearHydroFilesDisplay();
    uiConfig.hydroMaps.clear();
    uiConfig.daysToRun.clear();
}

void MainWindow::setTab(MainWindow::Tab tab) const
{
    ui->tabWidget->setCurrentIndex(tab);
}

/* END private functions */
