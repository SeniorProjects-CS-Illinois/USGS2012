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
    kPhyto(-1.0),
    kMacro(-1.0),
    phytoSenescence(-1.0),
    phytoRespiration(-1.0),
    phytoExcretion(-1.0),
    phytoAj(-1.0),
    phytoGj(-1.0),
    herbivoreAiPhyto(-1.0),
    herbivoreGiPhyto(-1.0),
    herbivorePrefPhyto(-1.0),
    herbivoreAiPeri(-1.0),
    herbivoreGiPeri(-1.0),
    herbivorePrefPeri(-1.0),
    herbivoreAiWaterdecomp(-1.0),
    herbivoreGiWaterdecomp(-1.0),
    herbivorePrefWaterdecomp(-1.0),
    herbivoreAj(-1.0),
    herbivoreGj(-1.0),
    herbivoreRespiration(-1.0),
    herbivoreExcretion(-1.0),
    herbivoreEgestion(-1.0),
    herbivoreSenescence(-1.0),
    herbivoreMax(-1.0),
    waterdecompAiDoc(-1.0),
    waterdecompGiDoc(-1.0),
    waterdecompPrefDoc(-1.0),
    waterdecompAiPoc(-1.0),
    waterdecompGiPoc(-1.0),
    waterdecompPrefPoc(-1.0),
    waterdecompAj(-1.0),
    waterdecompGj(-1.0),
    waterdecompRespiration(-1.0),
    waterdecompExcretion(-1.0),
    waterdecompSenescence(-1.0),
    waterdecompMax(-1.0),
    seddecompAiDetritus(-1.0),
    seddecompGiDetritus(-1.0),
    seddecompPrefDetritus(-1.0),
    seddecompAj(-1.0),
    seddecompGj(-1.0),
    seddecompRespiration(-1.0),
    seddecompExcretion(-1.0),
    seddecompSenescence(-1.0),
    seddecompMax(-1.0),
    consumerAiHerbivore(-1.0),
    consumerGiHerbivore(-1.0),
    consumerPrefHerbivore(-1.0),
    consumerAiSedconsumer(-1.0),
    consumerGiSedconsumer(-1.0),
    consumerPrefSedconsumer(-1.0),
    consumerAj(-1.0),
    consumerGj(-1.0),
    consumerRespiration(-1.0),
    consumerExcretion(-1.0),
    consumerSenescence(-1.0),
    consumerEgestion(-1.0),
    consumerMax(-1.0),
    macroSenescence(-1.0),
    macroRespiration(-1.0),
    macroExcretion(-1.0),
    macroTemp(-1.0),
    macroGross(-1.0),
    macroMassMax(-1.0),
    macroVelocityMax(-1.0),
    sedconsumerAiDetritus(-1.0),
    sedconsumerGiDetritus(-1.0),
    sedconsumerPrefDetritus(-1.0),
    sedconsumerAiSeddecomp(-1.0),
    sedconsumerGiSeddecomp(-1.0),
    sedconsumerPrefSeddecomp(-1.0),
    sedconsumerAj(-1.0),
    sedconsumerGj(-1.0),
    sedconsumerRespiration(-1.0),
    sedconsumerExcretion(-1.0),
    sedconsumerSenescence(-1.0),
    sedconsumerMax(-1.0)
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

    // write stock parameters
    file << phytoSenescence << endl;
    file << phytoRespiration << endl;
    file << phytoExcretion << endl;
    file << phytoAj << endl;
    file << phytoGj << endl;

    file << herbivoreAiPhyto << endl;
    file << herbivoreGiPhyto << endl;
    file << herbivorePrefPhyto << endl;
    file << herbivoreAiPeri << endl;
    file << herbivoreGiPeri << endl;
    file << herbivorePrefPeri << endl;
    file << herbivoreAiWaterdecomp << endl;
    file << herbivoreGiWaterdecomp << endl;
    file << herbivorePrefWaterdecomp << endl;
    file << herbivoreAj << endl;
    file << herbivoreGj << endl;
    file << herbivoreRespiration << endl;
    file << herbivoreExcretion << endl;
    file << herbivoreEgestion << endl;
    file << herbivoreSenescence << endl;
    file << herbivoreMax << endl;

    file << waterdecompAiDoc << endl;
    file << waterdecompGiDoc << endl;
    file << waterdecompPrefDoc << endl;
    file << waterdecompAiPoc << endl;
    file << waterdecompGiPoc << endl;
    file << waterdecompPrefPoc << endl;
    file << waterdecompAj << endl;
    file << waterdecompGj << endl;
    file << waterdecompRespiration << endl;
    file << waterdecompExcretion << endl;
    file << waterdecompSenescence << endl;
    file << waterdecompMax << endl;

    file << seddecompAiDetritus << endl;
    file << seddecompGiDetritus << endl;
    file << seddecompPrefDetritus << endl;
    file << seddecompAj << endl;
    file << seddecompGj << endl;
    file << seddecompRespiration << endl;
    file << seddecompExcretion << endl;
    file << seddecompSenescence << endl;
    file << seddecompMax << endl;

    file << consumerAiHerbivore << endl;
    file << consumerGiHerbivore << endl;
    file << consumerPrefHerbivore << endl;
    file << consumerAiSedconsumer << endl;
    file << consumerGiSedconsumer << endl;
    file << consumerPrefSedconsumer << endl;
    file << consumerAj << endl;
    file << consumerGj << endl;
    file << consumerRespiration << endl;
    file << consumerExcretion << endl;
    file << consumerSenescence << endl;
    file << consumerEgestion << endl;
    file << consumerMax << endl;

    file << macroSenescence << endl;
    file << macroRespiration << endl;
    file << macroExcretion << endl;
    file << macroTemp << endl;
    file << macroGross << endl;
    file << macroMassMax << endl;
    file << macroVelocityMax << endl;

    file << sedconsumerAiDetritus << endl;
    file << sedconsumerGiDetritus << endl;
    file << sedconsumerPrefDetritus << endl;
    file << sedconsumerAiSeddecomp << endl;
    file << sedconsumerGiSeddecomp << endl;
    file << sedconsumerPrefSeddecomp << endl;
    file << sedconsumerAj << endl;
    file << sedconsumerGj << endl;
    file << sedconsumerRespiration << endl;
    file << sedconsumerExcretion << endl;
    file << sedconsumerSenescence << endl;
    file << sedconsumerMax << endl;

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
    phytoSenescence = nextFloat(file, str);
    phytoRespiration = nextFloat(file, str);
    phytoExcretion = nextFloat(file, str);
    phytoAj = nextFloat(file, str);
    phytoGj = nextFloat(file, str);

    herbivoreAiPhyto = nextFloat(file, str);
    herbivoreGiPhyto = nextFloat(file, str);
    herbivorePrefPhyto = nextFloat(file, str);
    herbivoreAiPeri = nextFloat(file, str);
    herbivoreGiPeri = nextFloat(file, str);
    herbivorePrefPeri = nextFloat(file, str);
    herbivoreAiWaterdecomp = nextFloat(file, str);
    herbivoreGiWaterdecomp = nextFloat(file, str);
    herbivorePrefWaterdecomp = nextFloat(file, str);
    herbivoreAj = nextFloat(file, str);
    herbivoreGj = nextFloat(file, str);
    herbivoreRespiration = nextFloat(file, str);
    herbivoreExcretion = nextFloat(file, str);
    herbivoreEgestion = nextFloat(file, str);
    herbivoreSenescence = nextFloat(file, str);
    herbivoreMax = nextFloat(file, str);

    waterdecompAiDoc = nextFloat(file, str);
    waterdecompGiDoc = nextFloat(file, str);
    waterdecompPrefDoc = nextFloat(file, str);
    waterdecompAiPoc = nextFloat(file, str);
    waterdecompGiPoc = nextFloat(file, str);
    waterdecompPrefPoc = nextFloat(file, str);
    waterdecompAj = nextFloat(file, str);
    waterdecompGj = nextFloat(file, str);
    waterdecompRespiration = nextFloat(file, str);
    waterdecompExcretion = nextFloat(file, str);
    waterdecompSenescence = nextFloat(file, str);
    waterdecompMax = nextFloat(file, str);

    seddecompAiDetritus = nextFloat(file, str);
    seddecompGiDetritus = nextFloat(file, str);
    seddecompPrefDetritus = nextFloat(file, str);
    seddecompAj = nextFloat(file, str);
    seddecompGj = nextFloat(file, str);
    seddecompRespiration = nextFloat(file, str);
    seddecompExcretion = nextFloat(file, str);
    seddecompSenescence = nextFloat(file, str);
    seddecompMax = nextFloat(file, str);

    consumerAiHerbivore = nextFloat(file, str);
    consumerGiHerbivore = nextFloat(file, str);
    consumerPrefHerbivore = nextFloat(file, str);
    consumerAiSedconsumer = nextFloat(file, str);
    consumerGiSedconsumer = nextFloat(file, str);
    consumerPrefSedconsumer = nextFloat(file, str);
    consumerAj = nextFloat(file, str);
    consumerGj = nextFloat(file, str);
    consumerRespiration = nextFloat(file, str);
    consumerExcretion = nextFloat(file, str);
    consumerSenescence = nextFloat(file, str);
    consumerEgestion = nextFloat(file, str);
    consumerMax = nextFloat(file, str);

    macroSenescence = nextFloat(file, str);
    macroRespiration = nextFloat(file, str);
    macroExcretion = nextFloat(file, str);
    macroTemp = nextFloat(file, str);
    macroGross = nextFloat(file, str);
    macroMassMax = nextFloat(file, str);
    macroVelocityMax = nextFloat(file, str);

    sedconsumerAiDetritus = nextFloat(file, str);
    sedconsumerGiDetritus = nextFloat(file, str);
    sedconsumerPrefDetritus = nextFloat(file, str);
    sedconsumerAiSeddecomp = nextFloat(file, str);
    sedconsumerGiSeddecomp = nextFloat(file, str);
    sedconsumerPrefSeddecomp = nextFloat(file, str);
    sedconsumerAj = nextFloat(file, str);
    sedconsumerGj = nextFloat(file, str);
    sedconsumerRespiration = nextFloat(file, str);
    sedconsumerExcretion = nextFloat(file, str);
    sedconsumerSenescence = nextFloat(file, str);
    sedconsumerMax = nextFloat(file, str);

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
    kPhyto                  = other.kPhyto;
    kMacro                  = other.kMacro;

    // stock parameters
    phytoSenescence         = other.phytoSenescence;
    phytoRespiration        = other.phytoRespiration;
    phytoExcretion          = other.phytoExcretion;
    phytoAj                 = other.phytoAj;
    phytoGj                 = other.phytoGj;

    herbivoreAiPhyto        = other.herbivoreAiPhyto;
    herbivoreGiPhyto        = other.herbivoreGiPhyto;
    herbivorePrefPhyto      = other.herbivorePrefPhyto;
    herbivoreAiPeri         = other.herbivoreAiPeri;
    herbivoreGiPeri         = other.herbivoreGiPeri;
    herbivorePrefPeri       = other.herbivorePrefPeri;
    herbivoreAiWaterdecomp  = other.herbivoreAiWaterdecomp;
    herbivoreGiWaterdecomp  = other.herbivoreGiWaterdecomp;
    herbivorePrefWaterdecomp= other.herbivorePrefWaterdecomp;
    herbivoreAj             = other.herbivoreAj;
    herbivoreGj             = other.herbivoreGj;
    herbivoreRespiration    = other.herbivoreRespiration;
    herbivoreExcretion      = other.herbivoreExcretion;
    herbivoreEgestion       = other.herbivoreEgestion;
    herbivoreSenescence     = other.herbivoreSenescence;
    herbivoreMax            = other.herbivoreMax;

    waterdecompAiDoc        = other.waterdecompAiDoc;
    waterdecompGiDoc        = other.waterdecompGiDoc;
    waterdecompPrefDoc      = other.waterdecompPrefDoc;
    waterdecompAiPoc        = other.waterdecompAiPoc;
    waterdecompGiPoc        = other.waterdecompGiPoc;
    waterdecompPrefPoc      = other.waterdecompPrefPoc;
    waterdecompAj           = other.waterdecompAj;
    waterdecompGj           = other.waterdecompGj;
    waterdecompRespiration  = other.waterdecompRespiration;
    waterdecompExcretion    = other.waterdecompExcretion;
    waterdecompSenescence   = other.waterdecompSenescence;
    waterdecompMax          = other.waterdecompMax;

    seddecompAiDetritus     = other.seddecompAiDetritus;
    seddecompGiDetritus     = other.seddecompGiDetritus;
    seddecompPrefDetritus   = other.seddecompPrefDetritus;
    seddecompAj             = other.seddecompAj;
    seddecompGj             = other.seddecompGj;
    seddecompRespiration    = other.seddecompRespiration;
    seddecompExcretion      = other.seddecompExcretion;
    seddecompSenescence     = other.seddecompSenescence;
    seddecompMax            = other.seddecompMax;

    consumerAiHerbivore     = other.consumerAiHerbivore;
    consumerGiHerbivore     = other.consumerGiHerbivore;
    consumerPrefHerbivore   = other.consumerPrefHerbivore;
    consumerAiSedconsumer   = other.consumerAiSedconsumer;
    consumerGiSedconsumer   = other.consumerGiSedconsumer;
    consumerPrefSedconsumer = other.consumerPrefSedconsumer;
    consumerAj              = other.consumerAj;
    consumerGj              = other.consumerGj;
    consumerRespiration     = other.consumerRespiration;
    consumerExcretion       = other.consumerExcretion;
    consumerSenescence      = other.consumerSenescence;
    consumerEgestion        = other.consumerEgestion;
    consumerMax             = other.consumerMax;

    macroSenescence         = other.macroSenescence;
    macroRespiration        = other.macroRespiration;
    macroExcretion          = other.macroExcretion;
    macroTemp               = other.macroTemp;
    macroGross              = other.macroGross;
    macroMassMax            = other.macroMassMax;
    macroVelocityMax        = other.macroVelocityMax;

    sedconsumerAiDetritus   = other.sedconsumerAiDetritus;
    sedconsumerGiDetritus   = other.sedconsumerGiDetritus;
    sedconsumerPrefDetritus = other.sedconsumerPrefDetritus;
    sedconsumerAiSeddecomp  = other.sedconsumerAiSeddecomp;
    sedconsumerGiSeddecomp  = other.sedconsumerGiSeddecomp;
    sedconsumerPrefSeddecomp= other.sedconsumerPrefSeddecomp;
    sedconsumerAj           = other.sedconsumerAj;
    sedconsumerGj           = other.sedconsumerGj;
    sedconsumerRespiration  = other.sedconsumerRespiration;
    sedconsumerExcretion    = other.sedconsumerExcretion;
    sedconsumerSenescence   = other.sedconsumerSenescence;
    sedconsumerMax          = other.sedconsumerMax;

    // need more care for char*
    hydroMaps = new char*[numHydroMaps];
    for (size_t i = 0; i < numHydroMaps; i++)
    {
        setFileName(other.hydroMaps[i], hydroMaps[i]);
    }
    setFileName(other.tempFile, tempFile);
    setFileName(other.parFile, parFile);
}
