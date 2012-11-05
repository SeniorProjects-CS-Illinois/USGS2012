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
    macroSenescence(-1.0),
    macroRespiration(-1.0),
    macroExcretion(-1.0),
    macroTemp(-1.0),
    macroGross(-1.0),
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
    for (int hydro = 0; hydro < numHydroMaps; hydro++)
    {
        file << (int)daysToRun[hydro] << endl;
    }
    file << (int)outputFreq << endl;
    file << (int)timestep << endl;

    // write floating point values
    file << tss << endl;
    file << kPhyto << endl;
    file << kMacro << endl;

    // all the stock parameters
    file << macroSenescence << endl;
    file << macroRespiration << endl;
    file << macroExcretion << endl;
    file << macroTemp << endl;
    file << macroGross << endl;
    file << macroMassMax << endl;
    file << macroVelocityMax << endl;

    file.close();
}

void Configuration::read(const char* filename)
{
    ifstream file;
    file.open(filename);
    string str;

    adjacent = nextBool(file, str);
    consum = nextBool(file, str);
    detritus = nextBool(file, str);
    doc = nextBool(file, str);
    herbivore = nextBool(file, str);
    macro = nextBool(file, str);
    poc = nextBool(file, str);
    phyto = nextBool(file, str);
    sedconsumer = nextBool(file, str);
    seddecomp = nextBool(file, str);
    waterdecomp = nextBool(file, str);

    setFileName(QString::fromStdString(nextLine(file, str)), tempFile);
    setFileName(QString::fromStdString(nextLine(file, str)), parFile);

    numHydroMaps = nextInt(file, str);
    hydroMaps = new char*[numHydroMaps];
    for (size_t i = 0; i < numHydroMaps; i++)
    {
        setFileName(QString::fromStdString(nextLine(file, str)), hydroMaps[i]);
    }

    daysToRun = new uint16_t[numHydroMaps];
    for (size_t i = 0; i < numHydroMaps; i++)
    {        
        daysToRun[i] = nextInt(file, str);
    }

    outputFreq = nextInt(file, str);
    timestep = nextInt(file, str);
    tss = nextFloat(file, str);
    kPhyto = nextFloat(file, str);
    kMacro = nextFloat(file, str);

    // stock parameters
    macroSenescence = nextFloat(file, str);
    macroRespiration = nextFloat(file, str);
    macroGross = nextFloat(file, str);
    macroTemp = nextFloat(file, str);
    macroGross = nextFloat(file, str);
    macroMassMax = nextFloat(file, str);
    macroVelocityMax = nextFloat(file, str);

    file.close();
}

void Configuration::setFileName(QString source, char* & dest)
{
    dest = new char[source.length() + 1];
    strcpy(dest, source.toStdString().c_str());
}

bool Configuration::nextBool(ifstream & file, string & str)
{
    return nextLine(file, str)[0] == '1';
}

uint16_t Configuration::nextInt(ifstream & file, string & str)
{
    return QString::fromStdString(nextLine(file, str)).toInt();
}

float Configuration::nextFloat(ifstream & file, string & str)
{
    return QString::fromStdString(nextLine(file, str)).toFloat();
}

string & Configuration::nextLine(ifstream & file, string & str) const
{
    std::getline(file, str);
    return str;
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
    macroGross              = other.macroGross;
    macroRespiration        = other.macroRespiration;
    macroSenescence         = other.macroSenescence;
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
