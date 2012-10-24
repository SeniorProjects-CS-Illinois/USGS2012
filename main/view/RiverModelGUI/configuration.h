#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

struct Configuration
{

/** Structure of the .conf file:
  *
  *             Item                            (type)
  *---------------------------------------------------------
  *     Adjacent cells                          (bool)
  *     Consum stock selected                   (bool)
  *     Detritus stock selected                 (bool)
  *     DOC stock selected                      (bool)
  *     Herbivore stock selected                (bool)
  *     Macro stock selected                    (bool)
  *     POC stock selected                      (bool)
  *     Phyto stock selected                    (bool)
  *     Sedconsumer stock selected              (bool)
  *     Seddecomp stock selected                (bool)
  *     Waterdecomp stock selected              (bool)
  *     Temperature file name                   (char*)
  *     PAR file name                           (char*)
  *     Number of hydro maps selected           (int)
  *     Hydro Map file names (one per line)     (char*)
  *     Output frequency                        (int)
  *     Timestep                                (int)
  *     Days to Run (one per line)              (int)
  *     TSS                                     (float)
  *     Macro temperature                       (float)
  *     Gross macro coefficient                 (float)
  *     Respiration macro coefficient           (float)
  *     Senescence macro coefficient            (float)
  *     Macro mass max                          (float)
  *     Macro velocity max                      (float)
  *     KPhyto                                  (float)
  *     KMacro                                  (float)
  */

public:
    Configuration();
    Configuration(Configuration const & other);

    ~Configuration();

    Configuration const & operator=(Configuration const & other);

    /* Write all data to a file */
    void write(const char *filename) const;

    /* Read in a file */
    void read(const char *filename);

    /* Sets a filename properly */
    void setFileName(QString source, char* & dest);

    bool adjacent;
    bool consum;
    bool detritus;
    bool doc;
    bool herbivore;
    bool macro;
    bool poc;
    bool phyto;
    bool sedconsumer;
    bool seddecomp;
    bool waterdecomp;

    char* tempFile;
    char* parFile;
    char** hydroMaps;

    uint8_t numStocks;
    uint8_t numHydroMaps;

    uint8_t outputFreq;
    uint8_t timestep;
    uint8_t* daysToRun;

    float tss;
    float macroTemp;
    float grossMacroCoef;
    float respMacroCoef;
    float senescenceMacroCoef;
    float macroMassMax;
    float macroVelocityMax;
    float kPhyto;
    float kMacro;

private:
    void clear();
    void copy(Configuration const & other);

    bool convertBool(std::string str);
    uint8_t convertInt(std::string str);
    float convertFloat(std::string str);
};

#endif // CONFIGURATION_H
