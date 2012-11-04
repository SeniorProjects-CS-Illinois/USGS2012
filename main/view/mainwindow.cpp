#include "mainwindow.h"
#include <iostream>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;

/** TODO
  *     - whole bunch of stock input
  *         1) tool tips
  *         2) save/load from configuration
  *     - dynamic slider tooltip
  *     - error checking for run
  *     - break this hideously long file into more
  */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

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
    bool anyRemoved = false;
    size_t size = list->count();

    // loop through all items, remove selected items
    for (size_t i = 0; i < size; i++)
    {
        if (list->item(i)->isSelected())
        {
            list->takeItem(i); // may need to delete this here
            wholeHydroMapFiles.removeAt(i);
            daysToRun.removeAt(i);
            anyRemoved = true;
        }
    }
    if (!anyRemoved)
    {
        displayErrors("No files selected for removal");
    }
}

void MainWindow::selectDischargeFileClicked()
{
    clearErrors();

    // open prompt to select file
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Discharge File"),
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

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
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

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
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

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
    getAllInput();
    go_command();
}

void MainWindow::timestepUpdate(int newVal)
{
    clearErrors();
    ui->horizontalSliderTimestep->setToolTip(QString::number(newVal));
}

/* END public slots */

/* BEGIN private slots */

void MainWindow::saveConfiguration()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Save Configuration As"),
                                                tr(defaultFileLocation()), tr("Config Files (*.conf)"));
    if (!name.isEmpty())
    {
        saveConfiguration(name);
    }
}

void MainWindow::saveConfiguration(QString file) const
{
    Configuration conf;

    // set all values for configuration
    conf.adjacent               = getAdjacent();
    conf.grossMacroCoef         = getMacroGross();
    conf.kMacro                 = getKMacro();
    conf.kPhyto                 = getKPhyto();
    conf.macroMassMax           = getMacroMassMax();
    conf.macroTemp              = getMacroTemp();
    conf.macroVelocityMax       = getMacroVelocityMax();
    conf.numHydroMaps           = getNumHydroMaps();
    conf.outputFreq             = getOutputFreq();
    conf.respMacroCoef          = getMacroRespiration();
    conf.senescenceMacroCoef    = getMacroSenescence();
    conf.timestep               = getTimestep();
    conf.tss                    = getTSS();
    conf.consum                 = getConsum();
    conf.detritus               = getDetritus();
    conf.doc                    = getDOC();
    conf.herbivore              = getHerbivore();
    conf.macro                  = getMacro();
    conf.poc                    = getPOC();
    conf.phyto                  = getPhyto();
    conf.sedconsumer            = getSedconsumer();
    conf.seddecomp              = getSeddecomp();
    conf.waterdecomp            = getWaterdecomp();

    // file names need special attention
    QList<QString> hydromaps = getHydroMaps();
    conf.hydroMaps = new char*[conf.numHydroMaps];
    QList<uint8_t> days = getDaysToRun();
    conf.daysToRun = new uint8_t[conf.numHydroMaps];
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
                                                tr(defaultFileLocation()), tr("Config Files (*.conf)"));
    if (!name.isEmpty())
    {
        loadConfiguration(name);
    }
}

void MainWindow::loadConfiguration(QString file)
{
    Configuration conf;
    conf.read(file.toStdString().c_str());

    // set all values
    setConsum(conf.consum);
    setDetritus(conf.detritus);
    setDOC(conf.doc);
    setHerbivore(conf.herbivore);
    setMacro(conf.macro);
    setPOC(conf.poc);
    setPhyto(conf.phyto);
    setSedconsumer(conf.sedconsumer);
    setSeddecomp(conf.seddecomp);
    setWaterdecomp(conf.waterdecomp);
    setAdjacent(conf.adjacent);
    setOutputFreq(conf.outputFreq);
    setTimestep(conf.timestep);
    setTSS(conf.tss);
    setMacroTemp(conf.macroTemp);
    setMacroGross(conf.grossMacroCoef);
    setMacroRespiration(conf.respMacroCoef);
    setMacroSenescence(conf.senescenceMacroCoef);
    setMacroMassMax(conf.macroMassMax);
    setMacroVelocityMax(conf.macroVelocityMax);
    setKPhyto(conf.kPhyto);
    setKMacro(conf.kMacro);
    setTempFile(conf.tempFile);
    setPARFile(conf.parFile);
    setHydroMaps(conf.hydroMaps, conf.daysToRun, conf.numHydroMaps);
}

/* END private slots */

/* BEGIN public functions */

void MainWindow::setToolTips()
{
    // Buttons
    ui->pushButtonAddHydroMap->setToolTip(tr("Push to add the current hydro file"));
    ui->pushButtonRemoveHydroMap->setToolTip(tr("Push to remove currently selected hydro map"));
    ui->pushButtonRun->setToolTip(tr("Push to run model"));
    ui->pushButtonSelectHydroMap->setToolTip(tr("Push to select hydro map data file"));
    ui->pushButtonSelectPARFile->setToolTip(tr("Push to select PAR data file"));
    ui->pushButtonSelectTempFile->setToolTip(tr("Push to add temperature data file"));
    ui->pushButtonSelectDischargeFile->setToolTip(tr("Push to add hydro files based on a discharge file"));

    // Check Boxes
    ui->checkBoxAdjacentCells->setToolTip(tr("Check this box if you want carbon flows to be limited to only adjacent cells"));
    ui->checkBoxConsum->setToolTip(tr("Consum Stock"));
    ui->checkBoxDetritus->setToolTip(tr("Detritus stock"));
    ui->checkBoxDOC->setToolTip(tr("DOC stock"));
    ui->checkBoxHerbivore->setToolTip(tr("Herbivore stock"));
    ui->checkBoxMacro->setToolTip(tr("Macro stock"));
    ui->checkBoxPhyto->setToolTip(tr("Phyto stock"));
    ui->checkBoxPOC->setToolTip(tr("POC stock"));
    ui->checkBoxSedconsumer->setToolTip(tr("Sedconsumer stock"));
    ui->checkBoxSeddecomp->setToolTip(tr("Seddecomp stock"));
    ui->checkBoxWaterdecomp->setToolTip(tr("Waterdecomp"));

    // Labels
    ui->labelDaysToRun->setToolTip(tr("The number of days to simulate for this model"));
    ui->labelErrors->setToolTip(tr("This is the header for the error display"));
    ui->labelMacroGrossCoef->setToolTip(tr("I have no idea what this is..."));
    ui->labelHydroMap->setToolTip(tr("No file selected yet"));
    ui->labelKMacro->setToolTip(tr("I have no idea what this is..."));
    ui->labelKPhyto->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroMassMax->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroTemp->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroVelocityMax->setToolTip(tr("I have no idea what this is..."));
    ui->labelOutputFreq->setToolTip(tr("The rate at which images should be output in # of days"));
    ui->labelPARFile->setToolTip(tr("No file selected yet"));
    ui->labelMacroRespiration->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroSenescence->setToolTip(tr("I have no idea what this is..."));
    ui->labelTempFile->setToolTip(tr("No file selected yet"));
    ui->labelTimestep->setToolTip(tr("Granularity of calculation"));
    ui->labelTSS->setToolTip(tr("I have no idea what this is..."));

    // Sliders
    ui->horizontalSliderTimestep->setToolTip(QString::number(getTimestep()));

    // Combo Boxes
    ui->comboBoxWhichStock->setToolTip("Which stock");

    // Text Input Boxes
    ui->lineEditDaysToRun->setToolTip(tr("Enter a positive integer"));
    ui->lineEditMacroGrossCoef->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditKMacro->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditKPhyto->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditMacroMassMax->setToolTip(tr("Enter a value between 500.0 and 1500.0"));
    ui->lineEditMacroTemp->setToolTip(tr("Enter a number between 11.7 and 27.7"));
    ui->lineEditMacroVelocityMax->setToolTip(tr("Enter a value between 0.2 and 1.6"));
    ui->lineEditOutputFreq->setToolTip(tr("Enter a positive integer"));
    ui->lineEditMacroRespiration->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditMacroSenescence->setToolTip(tr("Enter a value between 0.0 and 1.0"));
    ui->lineEditTSS->setToolTip(tr("Enter a number between 0.0 and 20.0"));

    // Text Output Boxes
    ui->listWidgetHydroMap->setToolTip(tr("The currently selected hydro map data files"));
    ui->textBrowserErrors->setToolTip(tr("Shows erros with current configuration"));
}

bool MainWindow::getConsum() const { return ui->checkBoxConsum->isChecked(); }
bool MainWindow::getDetritus() const { return ui->checkBoxDetritus->isChecked(); }
bool MainWindow::getDOC() const { return ui->checkBoxDOC->isChecked(); }
bool MainWindow::getHerbivore() const { return ui->checkBoxHerbivore->isChecked(); }
bool MainWindow::getMacro() const { return ui->checkBoxMacro->isChecked(); }
bool MainWindow::getPOC() const { return ui->checkBoxPOC->isChecked(); }
bool MainWindow::getPhyto() const { return ui->checkBoxPhyto->isChecked(); }
bool MainWindow::getSedconsumer() const { return ui->checkBoxSedconsumer->isChecked(); }
bool MainWindow::getSeddecomp() const { return ui->checkBoxSeddecomp->isChecked(); }
bool MainWindow::getWaterdecomp() const { return ui->checkBoxWaterdecomp->isChecked(); }
bool MainWindow::getAdjacent() const { return ui->checkBoxAdjacentCells->isChecked(); }

uint8_t MainWindow::getOutputFreq() const { return ui->lineEditOutputFreq->text().toInt(); }
uint8_t MainWindow::getTimestep() const { return ui->horizontalSliderTimestep->value(); }
uint8_t MainWindow::getNumHydroMaps() const { return ui->listWidgetHydroMap->count(); }

float MainWindow::getTSS() const { return ui->lineEditTSS->text().toFloat(); }
float MainWindow::getKPhyto() const { return ui->lineEditKPhyto->text().toFloat(); }
float MainWindow::getKMacro() const { return ui->lineEditKMacro->text().toFloat(); }

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

QList<uint8_t> MainWindow::getDaysToRun() const { return daysToRun; }
QList<QString> MainWindow::getHydroMaps() const { return wholeHydroMapFiles; }


/* SETTERS */
void MainWindow::setConsum(bool val) { ui->checkBoxConsum->setChecked(val); }
void MainWindow::setDetritus(bool val) { ui->checkBoxDetritus->setChecked(val); }
void MainWindow::setDOC(bool val) { ui->checkBoxDOC->setChecked(val); }
void MainWindow::setHerbivore(bool val) { ui->checkBoxHerbivore->setChecked(val); }
void MainWindow::setMacro(bool val) { ui->checkBoxMacro->setChecked(val); }
void MainWindow::setPOC(bool val) { ui->checkBoxPOC->setChecked(val); }
void MainWindow::setPhyto(bool val) { ui->checkBoxPhyto->setChecked(val); }
void MainWindow::setSedconsumer(bool val) { ui->checkBoxSedconsumer->setChecked(val); }
void MainWindow::setSeddecomp(bool val) { ui->checkBoxSeddecomp->setChecked(val); }
void MainWindow::setWaterdecomp(bool val) { ui->checkBoxSeddecomp->setChecked(val); }
void MainWindow::setAdjacent(bool val) { ui->checkBoxWaterdecomp->setChecked(val); }

void MainWindow::setOutputFreq(uint8_t val) { ui->lineEditOutputFreq->setText(QString::number(val)); }
void MainWindow::setTimestep(uint8_t val) { ui->horizontalSliderTimestep->setValue(val); }

void MainWindow::setKPhyto(float val) { ui->lineEditKPhyto->setText(QString::number(val)); }
void MainWindow::setKMacro(float val) { ui->lineEditKMacro->setText(QString::number(val)); }
void MainWindow::setTSS(float val) { ui->lineEditTSS->setText(QString::number(val)); }

void MainWindow::setWhichStock(char *stock) { ui->comboBoxWhichStock->setCurrentIndex(stockIndex(stock)); }

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

void MainWindow::setHydroMaps(char** filenames, uint8_t* daysToRun, size_t num)
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
    displayErrors("None");
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

void MainWindow::displayErrors(const char *message) const
{
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

uint8_t MainWindow::parseDaysToRun(QListWidgetItem* item) const
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

void MainWindow::getAllInput() const
{
    // TODO: is this confusing with the different naming conventions?
    set_hydro_filenames(formatHydroMaps().toStdString().c_str());
    set_par_file(getPARFile().toStdString().c_str());
    set_temperature_file(getTempFile().toStdString().c_str());
    set_timestep(getTimestep());
    // TODO: need separate dropdown for this, re-configure GUI a bit
    set_whichstock(getWhichStock().toStdString().c_str());
    set_TSS(getTSS());
    set_k_phyto(getKPhyto());
    set_k_macro(getKMacro());
    set_output_frequency(getOutputFreq());
    // TODO: is this the "adjacent cells only" boolean?
    set_flow_corners(getAdjacent());

    getAllStockInput(); // There are so many, it would be best to separate this

    //saveConfiguration(QString(defaultFileLocation())); // save configuration for next time
}

void MainWindow::getAllStockInput() const
{
    //getPhytoSenescence()/24
    //getPhytoRespiration()/24
    //getPhytoExcretion()/24
    //getPhytoAj()
    //getPhytoGj()

    set_ai_herbivore_phyto(getHerbivoreAiPhyto());
    set_gi_herbivore_phyto(getHerbivoreGiPhyto());
    set_pref_herbivore_phyto(getHerbivorePrefPhyto());
    set_ai_herbivore_peri(getHerbivoreAiPeri());
    set_gi_herbivore_peri(getHerbivoreGiPeri());
    set_pref_herbivore_peri(getHerbivorePrefPeri());
    set_ai_herbivore_waterdecomp(getHerbivoreAiWaterdecomp());
    set_gi_herbivore_waterdecomp(getHerbivoreGiWaterdecomp());
    set_pref_herbivore_waterdecomp(getHerbivorePrefWaterdecomp());
    set_aj_herbivore(getHerbivoreAj());
    set_gj_herbivore(getHerbivoreGj());
    set_respiration_herbivore(getHerbivoreRespiration()/24);
    set_excretion_herbivore(getHerbivoreExcretion()/24);
    set_herbivore_egestion(getHerbivoreEgestion());
    set_senescence_herbivore(getHerbivoreSenescence()/24);
    set_max_herbivore(getHerbivoreMax()/24);

    set_ai_waterdecomp_doc(getWaterdecompAiDoc());
    set_gi_waterdecomp_doc(getWaterdecompGiDoc());
    set_pref_waterdecomp_doc(getWaterdecompPrefDoc());
    set_ai_waterdecomp_poc(getWaterdecompAiPoc());
    set_gi_waterdecomp_poc(getWaterdecompGiPoc());
    set_pref_waterdecomp_poc(getWaterdecompPrefPoc());
    set_aj_waterdecomp(getWaterdecompAj());
    set_gj_waterdecomp(getWaterdecompGj());
    set_respiration_waterdecomp(getWaterdecompRespiration()/24);
    set_excretion_waterdecomp(getWaterdecompExcretion()/24);
    set_senescence_waterdecomp(getWaterdecompSenescence()/24);
    set_max_waterdecomp(getWaterdecompMax()/24);

    set_ai_seddecomp_detritus(getSeddecompAiDetritus());
    set_gi_seddecomp_detritus(getSeddecompGiDetritus());
    set_pref_seddecomp_detritus(getSeddecompPrefDetritus());
    set_aj_seddecomp(getSeddecompAj());
    set_gj_seddecomp(getSeddecompGj());
    set_respiration_seddecomp(getSeddecompRespiration()/24);
    set_excretion_seddecomp(getSeddecompExcretion()/24);
    set_senescence_seddecomp(getSeddecompSenescence()/24);
    set_max_seddecomp(getSeddecompMax()/24);

    set_ai_consum_herbivore(getConsumerAiHerbivore());
    set_gi_consum_herbivore(getConsumerGiHerbivore());
    set_pref_consum_herbivore(getConsumerPrefHerbivore());
    set_ai_consum_sedconsumer(getConsumerAiSedconsumer());
    set_gi_consum_sedconsumer(getConsumerGiSedconsumer());
    set_pref_consum_sedconsumer(getConsumerPrefSedconsumer());
    set_aj_consum(getConsumerAj());
    set_gj_consum(getConsumerGj());
    set_respiration_consum(getConsumerRespiration()/24);
    set_excretion_consum(getConsumerExcretion()/24);
    set_senescence_consum(getConsumerSenescence()/24);
    set_consum_egestion(getConsumerEgestion());
    set_max_consum(getConsumerMax()/24);

    set_sen_macro_coef(getMacroSenescence()/24);
    set_resp_macro_coef(getMacroRespiration()/24);
    //getMacroExcretion()
    set_macro_base_temp(getMacroTemp());
    set_gross_macro_coef(getMacroGross());
    set_macro_mass_max(getMacroMassMax());
    set_macro_vel_max(getMacroVelocityMax());

    set_ai_sedconsumer_detritus(getSedconsumerAiDetritus());
    set_gi_sedconsumer_detritus(getSedconsumerGiDetritus());
    set_pref_sedconsumer_detritus(getSedconsumerPrefDetritus());
    set_ai_sedconsumer_seddecomp(getSedconsumerAiSeddecomp());
    set_gi_sedconsumer_seddecomp(getSedconsumerGiSeddecomp());
    set_pref_sedconsumer_seddecomp(getSedconsumerPrefSeddecomp());
    // TODO: peri?
    set_aj_sedconsumer(getSedconsumerAj());
    set_gj_sedconsumer(getSedconsumerGj());
    set_respiration_sedconsumer(getSedconsumerRespiration()/24);
    set_excretion_sedconsumer(getSedconsumerExcretion()/24);
    set_senescence_sedconsumer(getSedconsumerSenescence()/24);
    set_max_sedconsumer(getSedconsumerMax()/24);
}

QString MainWindow::formatHydroMaps() const
{
    QList<QString> maps = getHydroMaps();
    QList<uint8_t> days = getDaysToRun();
    size_t numMaps = maps.size();
    QString builder;
    builder.append(QString::number(numMaps) + "?");
    for (size_t i = 0; i < numMaps; i++)
    {
        builder.append(maps.at(i) + "?");
        builder.append(QString::number(days.at(i)) + "?");
    }

    return builder;
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
    // TODO: should this be floor function?
    QString file("0k-new.txt");
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
    QList<uint8_t> newDays;
    size_t size = wholeHydroMapFiles.size();

    QString currFile = wholeHydroMapFiles.at(0);
    size_t count = daysToRun.at(0);
    for (size_t i = 1; i < size; i++)
    {
        cout << currFile.toStdString() << ", " << wholeHydroMapFiles.at(i).toStdString() << ", " << currFile.compare(wholeHydroMapFiles.at(i)) << endl;
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
    for (size_t i = 0; i < wholeHydroMapFiles.size(); i++)
    {
        addHydroMap(stripFile(wholeHydroMapFiles.at(i)), QString::number(daysToRun.at(i)), false);
    }
}

const char* MainWindow::qstringToCStr(const QString & input) const
{
    // TODO: this function has serious scoping problems, the returned char* is immediately invalid
    return input.toStdString().c_str();
}

char* MainWindow::defaultFileLocation() const
{
    // change output to wherever data dir is
    return  "C:/cygwin/home/Owner/cs492/USGS2012/main/model/data";
}

/* END private functions */
