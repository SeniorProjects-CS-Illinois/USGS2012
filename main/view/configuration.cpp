#include "configuration.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

Configuration::Configuration() :
    adjacent(false),
    consum(false),
    detritus(false),
    doc(false),
    herbivore(false),
    macro(false),
    poc(false),
    phyto(false),
    sedconsumer(false),
    seddecomp(false),
    waterdecomp(false),
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
    senescenceMacroCoef(-1.0),
    macroMassMax(-1.0),
    macroVelocityMax(-1.0),
    kPhyto(-1.0),
    kMacro(-1.0)
{

}

Configuration::Configuration(Configuration const & other)
{
    copy(other);
}

Configuration::~Configuration()
{
    clear();
}

Configuration const & Configuration::operator=(Configuration const & other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

void Configuration::write(const char* filename) const
{
    ofstream file;
    file.open(filename);

    // write booleans
    file << adjacent << endl;
    file << consum << endl;
    file << detritus << endl;
    file << doc << endl;
    file << herbivore << endl;
    file << macro << endl;
    file << poc << endl;
    file << phyto << endl;
    file << sedconsumer << endl;
    file << seddecomp << endl;
    file << waterdecomp << endl;

    // write file names
    file << tempFile << endl;
    file << parFile << endl;

    // for hydro maps, need number of maps first
    file << (int)numHydroMaps << endl;
    for (int hydro = 0; hydro < numHydroMaps; hydro++)
    {
        file << hydroMaps[hydro] << endl;
    }

    // write integer values
    file << (int)outputFreq << endl;
    file << (int)timestep << endl;
    for (int hydro = 0; hydro < numHydroMaps; hydro++)
    {
        file << (int)daysToRun[hydro] << endl;
    }

    // write floating point values
    file << tss << endl;
    file << macroTemp << endl;
    file << grossMacroCoef << endl;
    file << respMacroCoef << endl;
    file << senescenceMacroCoef << endl;
    file << macroMassMax << endl;
    file << macroVelocityMax << endl;
    file << kPhyto << endl;
    file << kMacro << endl;

    file.close();
}

void Configuration::read(const char* filename)
{
    ifstream file;
    file.open(filename);
    string str;

    std::getline(file, str);
    adjacent = convertBool(str);
    std::getline(file, str);
    consum = convertBool(str);
    std::getline(file, str);
    detritus = convertBool(str);
    std::getline(file, str);
    doc = convertBool(str);
    std::getline(file, str);
    herbivore = convertBool(str);
    std::getline(file, str);
    macro = convertBool(str);
    std::getline(file, str);
    poc = convertBool(str);
    std::getline(file, str);
    phyto = convertBool(str);
    std::getline(file, str);
    sedconsumer = convertBool(str);
    std::getline(file, str);
    seddecomp = convertBool(str);
    std::getline(file, str);
    waterdecomp = convertBool(str);

    std::getline(file, str);
    setFileName(QString::fromStdString(str), tempFile);
    std::getline(file, str);
    setFileName(QString::fromStdString(str), parFile);

    std::getline(file, str);
    numHydroMaps = convertInt(str);

    hydroMaps = new char*[numHydroMaps];
    for (size_t i = 0; i < numHydroMaps; i++)
    {
        std::getline(file, str);
        setFileName(QString::fromStdString(str), hydroMaps[i]);
    }

    std::getline(file, str);
    outputFreq = convertInt(str);
    std::getline(file, str);
    timestep = convertInt(str);

    daysToRun = new uint8_t[numHydroMaps];
    for (size_t i = 0; i < numHydroMaps; i++)
    {
        std::getline(file, str);
        daysToRun[i] = convertInt(str);
    }

    std::getline(file, str);
    tss = convertFloat(str);
    cout << str << endl;
    std::getline(file, str);
    macroTemp = convertFloat(str);
    std::getline(file, str);
    grossMacroCoef = convertFloat(str);
    std::getline(file, str);
    respMacroCoef = convertFloat(str);
    std::getline(file, str);
    senescenceMacroCoef = convertFloat(str);
    std::getline(file, str);
    macroMassMax = convertFloat(str);
    std::getline(file, str);
    macroVelocityMax = convertFloat(str);
    std::getline(file, str);
    kPhyto = convertFloat(str);
    std::getline(file, str);
    kMacro = convertFloat(str);

    file.close();
}

void Configuration::setFileName(QString source, char* & dest)
{
    dest = new char[source.length() + 1];
    strcpy(dest, source.toStdString().c_str());
}

bool Configuration::convertBool(string str)
{
    return str[0] == '1';
}

uint8_t Configuration::convertInt(string str)
{
    return QString::fromStdString(str).toInt();
}

float Configuration::convertFloat(string str)
{
    return QString::fromStdString(str).toFloat();
}

void Configuration::clear()
{
    // assumes numHydroMaps is correct value
    for (size_t i = 0; i < numHydroMaps; i++)
    {
        delete hydroMaps[i];
    }

    delete hydroMaps;
    delete parFile;
    delete tempFile;
}

void Configuration::copy(const Configuration &other)
{
    // basic copy for bools and ints
    adjacent                = other.adjacent;
    consum                  = other.consum;
    detritus                = other.detritus;
    doc                     = other.doc;
    herbivore               = other.herbivore;
    macro                   = other.macro;
    poc                     = other.poc;
    phyto                   = other.phyto;
    sedconsumer             = other.sedconsumer;
    seddecomp               = other.seddecomp;
    waterdecomp             = other.waterdecomp;
    numStocks               = other.numStocks;
    numHydroMaps            = other.numHydroMaps;
    outputFreq              = other.outputFreq;
    timestep                = other.timestep;
    daysToRun               = other.daysToRun;
    tss                     = other.tss;
    macroTemp               = other.macroTemp;
    grossMacroCoef          = other.grossMacroCoef;
    respMacroCoef           = other.respMacroCoef;
    senescenceMacroCoef     = other.senescenceMacroCoef;
    macroMassMax            = other.macroMassMax;
    macroVelocityMax        = other.macroVelocityMax;
    kPhyto                  = other.kPhyto;
    kMacro                  = other.kMacro;

    // need more care for char*
    hydroMaps = new char*[numHydroMaps];
    for (size_t i = 0; i < numHydroMaps; i++)
    {
        setFileName(other.hydroMaps[i], hydroMaps[i]);
    }
    setFileName(other.tempFile, tempFile);
    setFileName(other.parFile, parFile);
}
