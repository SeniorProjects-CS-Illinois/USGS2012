#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "configuration.h"
#include "modelthread.h"
#include "progressthread.h"
#include "../model/rivermodel.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    /* Open dialog for selecting hydro map file */
    void selectHydroMapClicked();

    /* Adds the selected hydro map to the model */
    void addHydroMapClicked();

    /* Removes the selected hydro map from the model */
    void removeHydroMapClicked();

    /* Open dialog for selecting a discharge file */
    void selectDischargeFileClicked();

    /* Open dialog for selecting temperature file */
    void selectTemperatureFileClicked();

    /* Open dialog for selecting PAR file */
    void selectPARFileClicked();

    /* Run the model */
    void runClicked();

    /* Update which stock */
    void whichstockChanged(QString newStock);

    /* Allow the user to click run button */
    void enableRun();

    /* Disallow the user to click the run button */
    void disableRun();

    /* Update timestep slider information */
    void timestepUpdate(int newVal);

    /* Update progress bar information */
    void progressPercentUpdate(int percent);

    /* Update progress time information */
    void progressTimeUpdate(int elapsed, int remaining);

    /* Update the output image */
    void imageUpdate(QImage stockImage);
    
private slots:

    /* Save the current configuration to a file */
    void saveConfiguration();

    /* Load a configuration file */
    void loadConfiguration();

public:

    /* GETTERS */
    bool getAdjacent() const;

    uint8_t getOutputFreq() const;
    uint8_t getTimestep() const;
    uint16_t getNumHydroMaps() const;

    float getTSS() const;
    float getKPhyto() const;
    float getKMacro() const;

    // Stock parameters
    QString getWhichStock() const;

    float getMacroBase() const;
    float getPhytoBase() const;
    float getConsumerBase() const;
    float getDecompBase() const;
    float getSedconsumerBase() const;
    float getSeddecompBase() const;
    float getHerbivoreBase() const;
    float getDetritusBase() const;
    float getPocBase() const;
    float getDocBase() const;

    float getPhytoSenescence() const;
    float getPhytoRespiration() const;
    float getPhytoExcretion() const;
    float getPhytoAj() const;
    float getPhytoGj() const;

    float getHerbivoreAiPhyto() const;
    float getHerbivoreGiPhyto() const;
    float getHerbivorePrefPhyto() const;
    float getHerbivoreAiPeri() const;
    float getHerbivoreGiPeri() const;
    float getHerbivorePrefPeri() const;
    float getHerbivoreAiWaterdecomp() const;
    float getHerbivoreGiWaterdecomp() const;
    float getHerbivorePrefWaterdecomp() const;
    float getHerbivoreAj() const;
    float getHerbivoreGj() const;
    float getHerbivoreRespiration() const;
    float getHerbivoreExcretion() const;
    float getHerbivoreEgestion() const;
    float getHerbivoreSenescence() const;
    float getHerbivoreMax() const;

    float getWaterdecompAiDoc() const;
    float getWaterdecompGiDoc() const;
    float getWaterdecompPrefDoc() const;
    float getWaterdecompAiPoc() const;
    float getWaterdecompGiPoc() const;
    float getWaterdecompPrefPoc() const;
    float getWaterdecompAj() const;
    float getWaterdecompGj() const;
    float getWaterdecompRespiration() const;
    float getWaterdecompExcretion() const;
    float getWaterdecompSenescence() const;
    float getWaterdecompMax() const;

    float getSeddecompAiDetritus() const;
    float getSeddecompGiDetritus() const;
    float getSeddecompPrefDetritus() const;
    float getSeddecompAj() const;
    float getSeddecompGj() const;
    float getSeddecompRespiration() const;
    float getSeddecompExcretion() const;
    float getSeddecompSenescence() const;
    float getSeddecompMax() const;

    float getConsumerAiHerbivore() const;
    float getConsumerGiHerbivore() const;
    float getConsumerPrefHerbivore() const;
    float getConsumerAiSedconsumer() const;
    float getConsumerGiSedconsumer() const;
    float getConsumerPrefSedconsumer() const;
    float getConsumerAj() const;
    float getConsumerGj() const;
    float getConsumerRespiration() const;
    float getConsumerExcretion() const;
    float getConsumerSenescence() const;
    float getConsumerEgestion() const;
    float getConsumerMax() const;

    float getMacroSenescence() const;
    float getMacroRespiration() const;
    float getMacroExcretion() const;
    float getMacroTemp() const;
    float getMacroGross() const;
    float getMacroMassMax() const;
    float getMacroVelocityMax() const;

    float getSedconsumerAiDetritus() const;
    float getSedconsumerGiDetritus() const;
    float getSedconsumerPrefDetritus() const;
    float getSedconsumerAiSeddecomp() const;
    float getSedconsumerGiSeddecomp() const;
    float getSedconsumerPrefSeddecomp() const;
    float getSedconsumerAj() const;
    float getSedconsumerGj() const;
    float getSedconsumerRespiration() const;
    float getSedconsumerExcretion() const;
    float getSedconsumerSenescence() const;
    float getSedconsumerMax() const;

    // Files
    QString getTempFile() const;
    QString getPARFile() const;

    QVector<uint16_t> getDaysToRun() const;
    QVector<QString> getHydroMaps() const;

    /* SETTERS */
    void setAdjacent(bool val);

    void setOutputFreq(uint8_t val);
    void setTimestep(uint8_t val);

    void setTSS(float val);
    void setKPhyto(float val);
    void setKMacro(float val);

    // Stock parameters
    void setWhichStock(QString stock);

    void setMacroBase(float val);
    void setPhytoBase(float val);
    void setConsumerBase(float val);
    void setDecompBase(float val);
    void setSedconsumerBase(float val);
    void setSeddecompBase(float val);
    void setHerbivoreBase(float val);
    void setDetritusBase(float val);
    void setPocBase(float val);
    void setDocBase(float val);

    void setPhytoSenescence(float val);
    void setPhytoRespiration(float val);
    void setPhytoExretion(float val);
    void setPhytoAj(float val);
    void setPhytoGj(float val);

    void setHerbivoreAiPhyto(float val);
    void setHerbivoreGiPhyto(float val);
    void setHerbivorePrefPhyto(float val);
    void setHerbivoreAiPeri(float val);
    void setHerbivoreGiPeri(float val);
    void setHerbivorePrefPeri(float val);
    void setHerbivoreAiWaterdecomp(float val);
    void setHerbivoreGiWaterdecomp(float val);
    void setHerbivorePrefWaterdecomp(float val);
    void setHerbivoreAj(float val);
    void setHerbivoreGj(float val);
    void setHerbivoreRespiration(float val);
    void setHerbivoreExcretion(float val);
    void setHerbivoreEgestion(float val);
    void setHerbivoreSenescence(float val);
    void setHerbivoreMax(float val);

    void setWaterdecompAiDoc(float val);
    void setWaterdecompGiDoc(float val);
    void setWaterdecompPrefDoc(float val);
    void setWaterdecompAiPoc(float val);
    void setWaterdecompGiPoc(float val);
    void setWaterdecompPrefPoc(float val);
    void setWaterdecompAj(float val);
    void setWaterdecompGj(float val);
    void setWaterdecompRespiration(float val);
    void setWaterdecompExcretion(float val);
    void setWaterdecompSenescence(float val);
    void setWaterdecompMax(float val);

    void setSeddecompAiDetritus(float val);
    void setSeddecompGiDetritus(float val);
    void setSeddecompPrefDetritus(float val);
    void setSeddecompAj(float val);
    void setSeddecompGj(float val);
    void setSeddecompRespiration(float val);
    void setSeddecompExcretion(float val);
    void setSeddecompSenescence(float val);
    void setSeddecompMax(float val);

    void setConsumerAiHerbivore(float val);
    void setConsumerGiHerbivore(float val);
    void setConsumerPrefHerbivore(float val);
    void setConsumerAiSedconsumer(float val);
    void setConsumerGiSedconsumer(float val);
    void setConsumerPrefSedconsumer(float val);
    void setConsumerAj(float val);
    void setConsumerGj(float val);
    void setConsumerRespiration(float val);
    void setConsumerExcretion(float val);
    void setConsumerSenescence(float val);
    void setConsumerEgestion(float val);
    void setConsumerMax(float val);

    void setMacroSenescence(float val);
    void setMacroRespiration(float val);
    void setMacroExcretion(float val);
    void setMacroTemp(float val);
    void setMacroGross(float val);
    void setMacroMassMax(float val);
    void setMacroVelocityMax(float val);

    void setSedconsumerAiDetritus(float val);
    void setSedconsumerGiDetritus(float val);
    void setSedconsumerPrefDetritus(float val);
    void setSedconsumerAiSeddecomp(float val);
    void setSedconsumerGiSeddecomp(float val);
    void setSedconsumerPrefSeddecomp(float val);
    void setSedconsumerAj(float val);
    void setSedconsumerGj(float val);
    void setSedconsumerRespiration(float val);
    void setSedconsumerExcretion(float val);
    void setSedconsumerSenescence(float val);
    void setSedconsumerMax(float val);

    // Files
    void setTempFile(QString filename);
    void setPARFile(QString filename);
    void setHydroMaps(QVector<QString> filenames, QVector<uint16_t> days, size_t num);

private:

    enum Tab { CONFIGURATION, STOCK, OUTPUT };

    Ui::MainWindow* ui;
    RiverModel model;

    ModelThread modelThread;
    ProgressThread progressThread;

    Configuration uiConfig;

    /* Reset error message output box - all slots should call this in the beginning */
    void clearErrors() const;

    /* Check if given input box has data */
    bool isBoxFilled(QLineEdit * const input) const;

    /* Check if file has been selected */
    bool isFileSelected(QLabel * const input) const;

    /* Check if given stock value has been checked */
    bool isStockSelected(QCheckBox * const input) const;

    /* Get the index of the given string in the stock combo box */
    int stockIndex(char* stock) const;

    /* Set an error message */
    void displayErrors(const char * message, bool showConfig = true) const;

    /* Add hydro map information to list */
    void addHydroMap(QString file, uint16_t days, bool addInfo, bool display = true);

    /* Save the configuration to the given file */
    void saveConfiguration(QString file) const;

    /* Load the configuration from the given file */
    void loadConfiguration(QString file);

    /* Strips off all path info except file name*/
    QString stripFile(QString path) const;

    /** Format for a QListWidgetItem:
      *     <Filename>: <Days To Run> Days
      *         <Filename> = char*
      *         <Days To Run> = int
      */

    /* Get the days to run value from the given item */
    uint16_t parseDaysToRun(QListWidgetItem* item) const;

    /* Get the hydro map file name from the given item */
    QString parseHydroMapName(QListWidgetItem* item) const;

    /* Get all the input from the GUI and set appropriate globals */
    void getAllInput();

    /* Get all the stock input from the GUI and set globals */
    void getAllStockInput();

    /* Takes a discharge file and populates hydro map information */
    void dischargeToHydro(QString file);

    /* Finds the appropriate hydro file based on the given integer */
    QString intToHydroFile(int hydro, QString base) const;

    /* Combines all adjacent same-name files and sums their DTR */
    void compressHydroFiles();

    /* Write all hydro map data to screen */
    void displayHydroFiles();

    /* Clear the display of all hydro map data on the screen */
    void clearHydroFilesDisplay();

    /* Clear the display and the stored information of the hydro files */
    void clearHydroFiles();

    /* Convert QString to const char* */
    const char* qstringToCStr(const QString & input) const;

    /* Used to make file selection faster */
    QString defaultFileLocation() const;

    /* Set the displayed tab to the given tab */
    void setTab(Tab tab) const;
};

#endif // MAINWINDOW_H
