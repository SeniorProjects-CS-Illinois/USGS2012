#include "configuration.h"

Configuration::Configuration() :
    adjacent(false),
    stocks(NULL),
    tempFile(NULL),
    parFile(NULL),
    hydroMaps(NULL),
    numStocks(10),
    numHydroMaps(-1),
    outputFreq(-1),
    timestep(-1),
    daysToRun(NULL),
    tss(-1.0),
    macroTemp(-1.0),
    grossMacroCoef(-1.0),
    respMacroCoef(-1.0),
    scenescenceMacroCoef(-1.0),
    macroMassMax(-1.0),
    macroVelocityMax(-1.0),
    kPhyto(-1.0),
    kMacro(-1.0)
{

}

void Configuration::write(char* filename) const
{
    ofstream file;
    file.open(filename);

    // write booleans
    file << adjacent << endl;
    for (int stock = 0; stock < numStocks; stock++)
    {
        file << stocks[stock] << endl;
    }

    // write file names
    file << tempFile << endl;
    file << parFile << endl;

    // for hydro maps, need number of maps first
    file << numHydroMaps << endl;
    for (int hydro = 0; hydro < numHydroMaps; hydro++)
    {
        file << hydroMaps[hydro] << endl;
    }

    // write integer values
    file << outputFreq << endl;
    file << timestep << endl;
    for (int hydro = 0; hydro < numHydroMaps; hydro++)
    {
        file << daysToRun[hydro] << endl;
    }

    // write floating point values
    file << tss << endl;
    file << macroTemp << endl;
    file << grossMacroCoef << endl;
    file << respMacroCoef << endl;
    file << scenescenceMacroCoef << endl;
    file << macroMassMax << endl;
    file << macroVelocityMax << endl;
    file << kPhyto << endl;
    file << kMacro << endl;

    file.close();
}

void Configuration::read(char* filename)
{

}
