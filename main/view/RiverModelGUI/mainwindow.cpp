#include "mainwindow.h"
#include <iostream>

using std::cout;
using std::endl;

/** TODO
  *     - load from .conf file
  *     - dynamic slider tooltip
  *     - error checking for run
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
    displayErrors("Not mimplemented yet");
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
    Configuration conf;
    QString name = QFileDialog::getSaveFileName(this, tr("Save Configuration As"),
                                                tr(defaultFileLocation()), tr("Config Files (*.conf)"));

    // set all values for configuration
    conf.adjacent               = getAdjacent();
    conf.grossMacroCoef         = getGrossMacroCoef();
    conf.kMacro                 = getKMacro();
    conf.kPhyto                 = getKPhyto();
    conf.macroMassMax           = getMacroMassMax();
    conf.macroTemp              = getMacroTemp();
    conf.macroVelocityMax       = getMacroVelocityMax();
    conf.numHydroMaps           = getNumHydroMaps();
    conf.outputFreq             = getOutputFreq();
    conf.respMacroCoef          = getRespirationMacroCoef();
    conf.senescenceMacroCoef    = getSenescenceMacroCoef();
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

    conf.write(name.toStdString().c_str());
}

void MainWindow::loadConfiguration()
{
    Configuration conf;
    QString name = QFileDialog::getOpenFileName(this, tr("Open Configuration"),
                                                tr(defaultFileLocation()), tr("Config Files (*.conf)"));

    conf.read(name.toStdString().c_str());

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
    setGrossMacroCoef(conf.grossMacroCoef);
    setRespirationMacroCoef(conf.respMacroCoef);
    setSenescenceMacroCoef(conf.senescenceMacroCoef);
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
    ui->labelGrossMacroCoef->setToolTip(tr("I have no idea what this is..."));
    ui->labelHydroMap->setToolTip(tr("No file selected yet"));
    ui->labelKMacro->setToolTip(tr("I have no idea what this is..."));
    ui->labelKPhyto->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroMassMax->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroTemp->setToolTip(tr("I have no idea what this is..."));
    ui->labelMacroVelocityMax->setToolTip(tr("I have no idea what this is..."));
    ui->labelOutputFreq->setToolTip(tr("The rate at which images should be output in # of days"));
    ui->labelPARFile->setToolTip(tr("No file selected yet"));
    ui->labelRespMacroCoef->setToolTip(tr("I have no idea what this is..."));
    ui->labelSenescenceMacroCoef->setToolTip(tr("I have no idea what this is..."));
    ui->labelTempFile->setToolTip(tr("No file selected yet"));
    ui->labelTimestep->setToolTip(tr("Granularity of calculation"));
    ui->labelTSS->setToolTip(tr("I have no idea what this is..."));

    // Sliders
    ui->horizontalSliderTimestep->setToolTip(QString::number(getTimestep()));

    // Text Input Boxes
    ui->lineEditDaysToRun->setToolTip(tr("Enter a positive integer"));
    ui->lineEditGrossMacroCoef->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditKMacro->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditKPhyto->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditMacroMassMax->setToolTip(tr("Enter a value between 500.0 and 1500.0"));
    ui->lineEditMacroTemp->setToolTip(tr("Enter a number between 11.7 and 27.7"));
    ui->lineEditMacroVelocityMax->setToolTip(tr("Enter a value between 0.2 and 1.6"));
    ui->lineEditOutputFreq->setToolTip(tr("Enter a positive integer"));
    ui->lineEditRespMacroCoef->setToolTip(tr("Enter a number between 0.0 and 1.0"));
    ui->lineEditSenescenceMacroCoef->setToolTip(tr("Enter a value between 0.0 and 1.0"));
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
float MainWindow::getMacroTemp() const { return ui->lineEditMacroTemp->text().toFloat(); }
float MainWindow::getGrossMacroCoef() const { return ui->lineEditGrossMacroCoef->text().toFloat(); }
float MainWindow::getRespirationMacroCoef() const { return ui->lineEditRespMacroCoef->text().toFloat(); }
float MainWindow::getSenescenceMacroCoef() const { return ui->lineEditSenescenceMacroCoef->text().toFloat(); }
float MainWindow::getMacroMassMax() const { return ui->lineEditMacroMassMax->text().toFloat(); }
float MainWindow::getMacroVelocityMax() const { return ui->lineEditMacroVelocityMax->text().toFloat(); }
float MainWindow::getKPhyto() const { return ui->lineEditKPhyto->text().toFloat(); }
float MainWindow::getKMacro() const { return ui->lineEditKMacro->text().toFloat(); }

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

void MainWindow::setTSS(float val) { ui->lineEditTSS->setText(QString::number(val)); }
void MainWindow::setMacroTemp(float val) { ui->lineEditMacroTemp->setText(QString::number(val)); }
void MainWindow::setGrossMacroCoef(float val) { ui->lineEditGrossMacroCoef->setText(QString::number(val)); }
void MainWindow::setRespirationMacroCoef(float val) { ui->lineEditRespMacroCoef->setText(QString::number(val)); }
void MainWindow::setSenescenceMacroCoef(float val) { ui->lineEditSenescenceMacroCoef->setText(QString::number(val)); }
void MainWindow::setMacroMassMax(float val) { ui->lineEditMacroMassMax->setText(QString::number(val)); }
void MainWindow::setMacroVelocityMax(float val) { ui->lineEditMacroVelocityMax->setText(QString::number(val)); }
void MainWindow::setKPhyto(float val) { ui->lineEditKPhyto->setText(QString::number(val)); }
void MainWindow::setKMacro(float val) { ui->lineEditKMacro->setText(QString::number(val)); }

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

void MainWindow::displayErrors(char *message) const
{
    ui->textBrowserErrors->setText(tr(message));
}

void MainWindow::addHydroMap(QString filename, QString days, bool addInfo)
{
    if (addInfo)
    {
        wholeHydroMapFiles.append(filename);
        daysToRun.append(days.toInt());
        filename = stripFile(filename);
    }
    QString output = filename + ": " + days + " Days";
    ui->listWidgetHydroMap->addItem(new QListWidgetItem(output, ui->listWidgetHydroMap));
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

char* MainWindow::defaultFileLocation() const
{
    // change output to wherever data dir is
    return  "C:/Users/Owner/Desktop/data";
}

/* END private functions */
