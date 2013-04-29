#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "modelthread.h"
#include "progressthread.h"
#include "../model/configuration.h"
#include "../model/rivermodel.h"
#include "../util/files.h"
#include "../util/ui.h"
#include "../util/hydromaps.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief Default constructor, basic initialization of
     * member variables. Also, makes connections of
     * thread siganls to GUI slots.
     */
    explicit MainWindow(QWidget * parent = 0);

    /**
     * @brief Destructor for deleting dynamic member variables.
     */
    ~MainWindow();

public slots:

    /**
     * @brief Open dialog for selecting hydromap file.
     */
    void selectHydroMapClicked();

    /**
     * @brief Adds the selected hydromap to the model.
     */
    void addHydroMapClicked();

    /**
     * @brief Removes the selected hydromap(s) from the model.
     */
    void removeHydroMapClicked();

    /**
     * @brief Open dialog for selecting a discharge file.
     */
    void selectDischargeFileClicked();

    /**
     * @brief Open dialog for selecting temperature file.
     */
    void selectTemperatureFileClicked();

    /**
     * @brief Open dialog for selecting PAR file.
     */
    void selectPARFileClicked();

    /**
     * @brief Open dialog for selecting highest hydro file.
     */
    void selectHydroFile1Clicked();

    /**
     * @brief Open dialog for selecting second highest hydro file.
     */
    void selectHydroFile2Clicked();

    /**
     * @brief Open dialog for selecting third highest hydro file.
     */
    void selectHydroFile3Clicked();

    /**
     * @brief Open dialog for selecting fourth highest hydro file.
     */
    void selectHydroFile4Clicked();

    /**
     * @brief Open dialog for selecting fifth highest hydro file.
     */
    void selectHydroFile5Clicked();

    /**
     * @brief Open dialog for selecting sixth highest hydro file.
     */
    void selectHydroFile6Clicked();

    /**
     * @brief Open dialog for selecting seventh highest hydro file.
     */
    void selectHydroFile7Clicked();

    /**
     * @brief Open dialog for selecting eigth highest hydro file.
     */
    void selectHydroFile8Clicked();

    /**
     * @brief Open dialog for selecting ninth highest hydro file.
     */
    void selectHydroFile9Clicked();

    /**
     * @brief Open dialog for selecting tenth highest hydro file.
     */
    void selectHydroFile10Clicked();

    /**
     * @brief Run the model with current configuration.
     */
    void runClicked();

    /**
     * @brief Update which stock image to show.
     */
    void whichstockChanged(const QString & newStock);

    /**
     * @brief Change the max flow 1 and min flow 2.
     */
    void maxFlow1Changed();
    void minFlow2Changed();

    /**
     * @brief Change the max flow 2 and min flow 3.
     */
    void maxFlow2Changed();
    void minFlow3Changed();

    /**
     * @brief Change the max flow 3 and min flow 4.
     */
    void maxFlow3Changed();
    void minFlow4Changed();

    /**
     * @brief Change the max flow 4 and min flow 5.
     */
    void maxFlow4Changed();
    void minFlow5Changed();

    /**
     * @brief Change the max flow 5 and min flow 6.
     */
    void maxFlow5Changed();
    void minFlow6Changed();

    /**
     * @brief Change the max flow 6 and min flow 7.
     */
    void maxFlow6Changed();
    void minFlow7Changed();

    /**
     * @brief Change the max flow 7 and min flow 8.
     */
    void maxFlow7Changed();
    void minFlow8Changed();

    /**
     * @brief Change the max flow 8 and min flow 9.
     */
    void maxFlow8Changed();
    void minFlow9Changed();

    /**
     * @brief Change the max flow 9 and min flow 10.
     */
    void maxFlow9Changed();
    void minFlow10Changed();

    /**
     * @brief Finish up the running model.
     */
    void finished() const;

    /**
     * @brief Allow the user to click the run button.
     */
    void enableRun() const;

    /**
     * @brief Disallow the user to click the run button.
     */
    void disableRun() const;

    /**
     * @brief Update timestep slider information.
     */
    void timestepUpdate(int newVal) const;

    /**
     * @brief Update progress bar information.
     */
    void progressPercentUpdate(int percent) const;

    /**
     * @brief Update progress time information.
     */
    void progressTimeUpdate(int elapsed, int remaining) const;

    /**
     * @brief Update the displayed stock image.
     */
    void imageUpdate(const QImage & stockImage) const;

    /**
     * @brief Update the message for the status of the model.
     * @param message the message to display
     */
    void statusMessageUpdate(const QString & message) const;

    /**
     * @brief Save the current configuration to a file.
     */
    void saveConfiguration();

    /**
     * @brief Load a configuration file.
     */
    void loadConfiguration();

public:

    /* GETTERS */
    RiverModel* getCurrentModel() const;

    bool getAdjacent() const;

    uint8_t getOutputFreq() const;
    uint8_t getTimestep() const;
    uint16_t getNumHydroMaps() const;

    float getTSS() const;
    float getKPhyto() const;
    float getKMacro() const;

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

    void setWhichStock(const QString & stock);

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

    void setTempFile(const QString & filename);
    void setPARFile(const QString & filename);
    void setHydroMaps(const QVector<QString> & filenames, const QVector<uint16_t> & days, size_t num);

private:

    /**
     * Enum for the tab index. The order here IS important.
     */
    enum Tab { CONFIGURATION, HYDRO_FILES, STOCK, OUTPUT };

    Ui::MainWindow* ui;

    ModelThread modelThread;
    ProgressThread progressThread;

    Configuration uiConfig;

    /**
     * @brief Display an error message in a popup window.
     */
    void displayErrors(const QString & message) const;

    /**
     * @brief Clear any previous output in the output tab.
     */
    void clearOutput() const;

    /**
     * @brief Add hydromap information to list.
     */
    void addHydroMap(QString file, uint16_t days, bool addInfo, bool display = true);

    /**
     * @brief Copy value from one display to another, with an offset.
     * @param from   the display to copy data from.
     * @param to     the display to copy data to.
     * @param offset the value to offset.
     */
    void copyIntDisplaywithOffset(QLineEdit* from, QLineEdit* to, int offset) const;

    /**
     * @brief select a file from a dialog.
     * @param displayLabel the label to display the selected file to.
     * @param configVal    the config value to store the whole path.
     * @param title        the title of the selection dialog.
     * @param filter       a filter for selecting files.
     * @see QFileDialog
     */
    void selectFile(QLabel* displayLabel, QString & configVal, const QString & title, const QString & filter);

    /**
     * @brief Save the configuration to the given file.
     */
    void saveConfiguration(const QString & file) const;

    /**
     * @brief Load the configuration from the given file.
     */
    void loadConfiguration(const QString & file);

    /**
     * @brief Get all the input from the GUI and set appropriate globals.
     */
    void getAllInput(Configuration & c) const;

    /**
     * @brief Get all the stock input from the GUI and set globals.
     */
    void getAllStockInput(Configuration & c) const;

    /**
     * @brief Verify all the input from the GUI and set appropriate globals.
     */
    bool verifyAllInput() const;

    /**
     * @brief Verify all the stock input from the GUI and set globals.
     */
    bool verifyAllStockInput() const;

    /**
     * @brief Verify that the widget is a number.
     * @param widget       the widget to check.
     * @param errorMessage the message to display if it fails.
     * @return true if the widget has a numerical value.
     */
    bool verifyNumber(QLineEdit* widget, const QString & errorMessage) const;

    /**
     * @brief Verify that the widget represents a selected file.
     * @param widget       the widget to check.
     * @param errorMessage the message to display if it fails.
     * @return true if the widget has a string for a file.
     */
    bool verifyFile(QLabel* widget, const QString & errorMessage) const;

    /**
     * @brief Takes a discharge file and populates hydro map information.
     */
    void dischargeToHydro(const QString & file);

    /**
     * @brief Combines all adjacent same-name files and sums their DTR.
     */
    void compressHydroFiles();

    /**
     * @brief Write all hydro map data to screen.
     */
    void displayHydroFiles();

    /**
     * @brief Clear the display of all hydro map data on the screen.
     */
    void clearHydroFilesDisplay() const;

    /**
     * @brief Clear the display and the stored information of the hydro files.
     */
    void clearHydroFiles();

    /**
     * @brief Set the displayed tab to the given tab.
     */
    void setTab(Tab tab) const;
};

#endif // MAINWINDOW_H
