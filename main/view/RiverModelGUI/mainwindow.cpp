#include "mainwindow.h"
#include <iostream>

using std::cout;
using std::endl;

/** TODO
  *     - save to .conf file
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

void MainWindow::setToolTips()
{
    /* Buttons */
    ui->pushButtonAddHydroMap->setToolTip(tr("Push to add the current hydro file"));
    ui->pushButtonRemoveHydroMap->setToolTip(tr("Push to remove currently selected hydro map"));
    ui->pushButtonRun->setToolTip(tr("Push to run model"));
    ui->pushButtonSelectHydroMap->setToolTip(tr("Push to select hydro map data file"));
    ui->pushButtonSelectPARFile->setToolTip(tr("Push to select PAR data file"));
    ui->pushButtonSelectTempFile->setToolTip(tr("Push to add temperature data file"));

    /* Check Boxes */
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

    /* Labels */
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

    /* Sliders */
    int val = ui->horizontalSliderTimestep->value();
    ui->horizontalSliderTimestep->setToolTip(QString::number(val));

    /* Text Input Boxes */
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

    /* Text Output Boxes */
    ui->listWidgetHydroMap->setToolTip(tr("The currently selected hydro map data files"));
    ui->textBrowserErrors->setToolTip(tr("Shows erros with current configuration"));
}

/* BEGIN public slots */

void MainWindow::selectHydroMapClicked()
{
    clearErrors();
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Hydro Map File"),
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

    // make sure a hydro map file was selected
    if (!selected.isEmpty())
    {
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
    QString output = ui->labelHydroMap->text() + ": " + ui->lineEditDaysToRun->text() + " Days";
    ui->listWidgetHydroMap->addItem(new QListWidgetItem(output, ui->listWidgetHydroMap));
}

void MainWindow::removeHydroMapClicked()
{
    clearErrors();
    QList<QListWidgetItem*> selected = ui->listWidgetHydroMap->selectedItems();

    // make sure at least one item selected
    if (selected.isEmpty())
    {
        displayErrors("No hydro map files selected");
        return;
    }

    // for each selected item, remove it
    for (QList<QListWidgetItem*>::iterator it = selected.begin(); it != selected.end(); it++)
    {
        ui->listWidgetHydroMap->takeItem(ui->listWidgetHydroMap->row(*it));
    }
}

void MainWindow::selectTemperatureFileClicked()
{
    clearErrors();
    QString selected = QFileDialog::getOpenFileName(this, tr("Select Temperature Data File"),
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

    // make sure a temperature file was selected
    if (!selected.isEmpty())
    {
        QString filename = stripFile(selected);
        ui->labelTempFile->setText(filename);
        ui->labelTempFile->setToolTip(filename);
    }
}

void MainWindow::selectPARFileClicked()
{
    clearErrors();
    QString selected = QFileDialog::getOpenFileName(this, tr("Select PAR Data File"),
                                                    tr(defaultFileLocation()), tr("Text Files (*.txt)"));

    // make sure a par file was selected
    if (!selected.isEmpty())
    {
        QString filename = stripFile(selected);
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

void MainWindow::on_actionSave_Configuration_triggered()
{
    displayErrors("Save not implemented");
}

void MainWindow::on_actionLoad_Configuration_triggered()
{
    displayErrors("Load not implemented");
}

/* END private slots */

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

QString MainWindow::stripFile(QString path) const
{
    int n = path.lastIndexOf("/");
    return QString::fromStdString(path.toStdString().substr(n + 1));
}

char* MainWindow::defaultFileLocation() const
{
    return  "C:/Users/Owner/Desktop/data";
}
