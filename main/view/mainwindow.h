#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "configuration.h"

#include "../main.h"

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

    /* Open up dialog for selecting hydro map file */
    void selectHydroMapClicked();

    /* Adds the selected hydro map to the model */
    void addHydroMapClicked();

    /* Removes the selected hydro map from the model */
    void removeHydroMapClicked();

    /* Open dialog for selecting temperature file */
    void selectTemperatureFileClicked();

    /* Open dialog for selecting PAR file */
    void selectPARFileClicked();

    /* Run the model */
    void runClicked();

    /* Update timestep slider information */
    void timestepUpdate(int newVal);
    
private slots:

    /* Save the current configuration to a file */
    void saveConfiguration();

    /* Load a configuration file */
    void loadConfiguration();

public:

    /* Set the tool tip information for the GUI */
    void setToolTips();

    /* GETTERS */
    bool getConsum() const;
    bool getDetritus() const;
    bool getDOC() const;
    bool getHerbivore() const;
    bool getMacro() const;
    bool getPOC() const;
    bool getPhyto() const;
    bool getSedconsumer() const;
    bool getSeddecomp() const;
    bool getWaterdecomp() const;
    bool getAdjacent() const;

    uint8_t getOutputFreq() const;
    uint8_t getTimestep() const;
    uint8_t getNumHydroMaps() const;

    float getTSS() const;
    float getMacroTemp() const;
    float getGrossMacroCoef() const;
    float getRespirationMacroCoef() const;
    float getSenescenceMacroCoef() const;
    float getMacroMassMax() const;
    float getMacroVelocityMax() const;
    float getKPhyto() const;
    float getKMacro() const;

    QString getTempFile() const;
    QString getPARFile() const;

    QList<uint8_t> getDaysToRun() const;
    QList<QString> getHydroMaps() const;

    /* SETTERS */
    void setConsum(bool val);
    void setDetritus(bool val);
    void setDOC(bool val);
    void setHerbivore(bool val);
    void setMacro(bool val);
    void setPOC(bool val);
    void setPhyto(bool val);
    void setSedconsumer(bool val);
    void setSeddecomp(bool val);
    void setWaterdecomp(bool val);
    void setAdjacent(bool val);

    void setOutputFreq(uint8_t val);
    void setTimestep(uint8_t val);

    void setTSS(float val);
    void setMacroTemp(float val);
    void setGrossMacroCoef(float val);
    void setRespirationMacroCoef(float val);
    void setSenescenceMacroCoef(float val);
    void setMacroMassMax(float val);
    void setMacroVelocityMax(float val);
    void setKPhyto(float val);
    void setKMacro(float val);

    void setTempFile(char* filename);
    void setPARFile(char* filename);

    void setHydroMaps(char** filenames, uint8_t* daysToRun, size_t num);

private:

    Ui::MainWindow *ui;

    QString wholeTempFile;
    QString wholePARFile;

    QList<QString> wholeHydroMapFiles;
    QList<uint8_t> daysToRun;

    /* Used to make file selection faster */
    char* defaultFileLocation() const;

    /* Reset error message output box - all slots should call this in the beginning */
    void clearErrors() const;

    /* Check if given input box has data */
    bool isBoxFilled(QLineEdit * const input) const;

    /* Check if file has been selected */
    bool isFileSelected(QLabel * const input) const;

    /* Check if given stock value has been checked */
    bool isStockSelected(QCheckBox * const input) const;

    /* Set an error message */
    void displayErrors(const char * message) const;

    /* Add hydro map information to list */
    void addHydroMap(QString filename, QString days, bool addInfo);

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
    uint8_t parseDaysToRun(QListWidgetItem* item) const;

    /* Get the hydro map file name from the given item */
    QString parseHydroMapName(QListWidgetItem* item) const;

    /* Get all the input from the GUI and set appropriate globals */
    void getAllInput() const;

    /* Turns hydro map info int properly formatted string expected by given code */
    QString formatHydroMaps() const;
};

#endif // MAINWINDOW_H
