#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "configuration.h"

namespace Ui {
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
    void on_actionSave_Configuration_triggered();

    /* Load a configuration file */
    void on_actionLoad_Configuration_triggered();

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

    float getTSS() const;
    float getMacroTemp() const;
    float getGrossMacroCoef() const;
    float getRespirationMacroCoef() const;
    float getSenescenceMacroCoef() const;
    float getMacroMassMax() const;
    float getMacroVelocityMax() const;
    float getKPhyto() const;
    float getKMacro() const;


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

private:

    Ui::MainWindow *ui;

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
    void displayErrors(char * message) const;

    /* Strips off all path info except file name*/
    QString stripFile(QString path) const;
};

#endif // MAINWINDOW_H
