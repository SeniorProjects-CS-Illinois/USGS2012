#include "rivermodel.h"

RiverModel::RiverModel() {
    source = NULL;
    dest = NULL;
}

RiverModel::RiverModel(const RiverModel &other) {
    copy(other);
}

RiverModel::~RiverModel(){
    clear();
}

RiverModel & RiverModel::operator=(const RiverModel & rhs) {
    if(this != &rhs){
        clear();
        copy(rhs);
    }
    return *this;
}

Status RiverModel::getStatus(void){
    statusMutex.lock();
    Status modelStatusGUI = modelStatus;
    statusMutex.unlock();

    //After we get a copy for the GUI, reset the new image flag.
    modelStatus.hasNewImage(false);
    return modelStatusGUI;
}

/**
 * Returns an image of the currently selected stock.
 */
QImage RiverModel::getImage(void){
    return getImage(displayedStock);
}

/**
 * Returns the stock requested.
 */
QImage RiverModel::getImage(QString stockName){
    stockName = stockName.toLower();
    QImage stockImage;

    imageMutex.lock();
    for(int i = 0; i < NUM_IMAGES; i++){
        if(stockNames[i] == stockName){
            stockImage = images[i];
            break;
        }
    }
    imageMutex.unlock();

    return stockImage;
}

void RiverModel::run() {
    initializeModel(modelConfig);

    int daysToRun = getDaysToRun(modelConfig);

    int weeksElapsed = 0;
    int daysElapsed = 0;
    int hoursElapsed = 0;

    //Creates the river and initializes its patches
    River river(modelConfig, hydroFileDict);
    statusMutex.lock();
    modelStatus.setState(Status::RUNNING);
    statusMutex.unlock();

    //Get a hydrofile to process
    for (int hydroIndex = 0; hydroIndex < modelConfig.hydroMaps.size(); hydroIndex++) {
        //NEW HYDROFILE
        QString hydroFileName = modelConfig.hydroMaps[hydroIndex];
        int daysToRunHydroFile = modelConfig.daysToRun[hydroIndex];

        HydroData * currHydroData = hydroFileDict[hydroFileName];

        setStatusMessage("Transitioning to hydroFile: " + hydroFileName);
        river.setCurrentHydroData(currHydroData);
        cout << "RUNNING FILE: " << hydroFileName.toStdString() << " FOR " << daysToRunHydroFile << " DAYS" << endl;

        for(int dayOnHydroFile = 0; dayOnHydroFile < daysToRunHydroFile; dayOnHydroFile++) {
            if(daysElapsed % DAYS_PER_WEEK == 0){
                //BEGINNING OF WEEK
                river.setCurrentWaterTemperature( waterTemps[weeksElapsed] );
            }
            //BEGINNING OF DAY
            int currentDay = daysElapsed+1;


            for(int hour = 0; hour < HOURS_PER_DAY; hour++) {
                //NEW HOUR
                printHourlyMessage(currentDay, hour);
                river.setCurrentPAR( parValues[hoursElapsed] );
                river.processPatches();
                river.flow(source, dest);
                statusMutex.lock();
                modelStatus.updateProgress();
                statusMutex.unlock();

                hoursElapsed++;
            }
            //END OF DAY

            Statistics stats;
            setStatusMessage("Computing stats and writing output.");
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    stats = river.generateStatistics();
                    river.generateImages(images, stockNames, imageMutex, stats);
                    statusMutex.lock();
                    modelStatus.hasNewImage(true);
                    statusMutex.unlock();

                    saveAverages(stats,currentDay);
                }
                #pragma omp section
                {
                    //Make sure to output on final day.
                    if(currentDay % modelConfig.outputFreq == 0 || currentDay == daysToRun) {
                        river.saveCSV(displayedStock, daysElapsed);
                    }
                }
            }



            daysElapsed++;
            if(daysElapsed % DAYS_PER_WEEK == 0){
                //END OF WEEK

                weeksElapsed++;
            }
        }
    }

    //TODO Run program in valgrind to make sure all memory is freed.

    setStatusMessage("Simulation complete.");
    cout << endl << "PROCESSING COMPLETE" << endl;
    statusMutex.lock();
    modelStatus.setState(Status::COMPLETE);
    statusMutex.unlock();
}

void RiverModel::setConfiguration(const Configuration & configuration)
{
    modelConfig = configuration;
    displayedStock = modelConfig.whichStock;
}

void RiverModel::setWhichStock(QString stockName)
{
    displayedStock = stockName;
}

void RiverModel::printHourlyMessage(int currentDay, int hourOfDay) {
    QString message = "Flowing River: Day ";
    message.append(currentDay);
    message.append(" Hour: ");
    message.append(hourOfDay);

    setStatusMessage(message);
    cout << "Day: " << currentDay << " - Hour: " << hourOfDay \
        << " | Progress: " << (int)(modelStatus.getProgress()*100) \
        << "% - Time Elapsed/Remaining (sec): " << modelStatus.getTimeElapsed() \
        << " / " << modelStatus.getTimeRemaining() << endl;
}

//TODO Move this to construct and add the "Big three" (CCtor, assignment operator, destructor)
void RiverModel::initializeModel(const Configuration &config){
    setStatusMessage("Loading HydroFiles and precomputing flows... please wait.");
    initializeHydroMaps(modelConfig);

    setStatusMessage("Loading water temperatures from file.");
    initializeWaterTemps(modelConfig);

    setStatusMessage("Loading par values from file.");
    initializePARValues(modelConfig);

    // These are temp structures used in the flowing of the river.  Created
    // here so they are not initialized and destroyed repeatedly.
    initializeTempGrids(hydroFileDict);

    initializeImageVector(hydroFileDict);
    initializeStockNames();

    int daysToRun = getDaysToRun(modelConfig);
    initializeModelStatus(daysToRun);
}

void RiverModel::initializeModelStatus(int daysToRun)
{
    modelStatus.addWorkUnitsToProcess(daysToRun * 24);
    modelStatus.setState(Status::READY);
}

void RiverModel::initializeImageVector(HydroFileDict &hydroFileDict){
    int width = hydroFileDict.getMaxWidth();
    int height = hydroFileDict.getMaxHeight();
    for(int i = 0; i < NUM_IMAGES; i++) {
        images.append(QImage(width,height, QImage::Format_ARGB32));
    }
}

void RiverModel::initializeStockNames() {
    //Make sure these are added in the same order as the enum in constants.h
    stockNames.append("macro");
    stockNames.append("phyto");
    stockNames.append("herbivore");
    stockNames.append("waterdecomp");
    stockNames.append("seddecomp");
    stockNames.append("sedconsumer");
    stockNames.append("consumer");
    stockNames.append("doc");
    stockNames.append("poc");
    stockNames.append("detritus");
    stockNames.append("average");
}

void RiverModel::initializeHydroMaps(const Configuration &config) {
    cout << "LOADING HYDROFILES" << endl;
    QStringList hydroFileNames;
    for(int i = 0; i < config.hydroMaps.size(); i++) {
        hydroFileNames.append(config.hydroMaps[i]);
    }
    hydroFileDict = HydroFileDict(hydroFileNames);
}

void RiverModel::initializeWaterTemps(const Configuration &config) {
    cout << "LOADING WATER TEMPS" << endl;
    QString waterTempFilename = config.tempFile;
    QFile temperatureFile( waterTempFilename );
    if( !temperatureFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        printf("Failed to open the water temperature file");
        exit(1);
    }
    QTextStream temperatureInput( &temperatureFile );
    while( !temperatureInput.atEnd() ){
        QString line = temperatureInput.readLine();
        waterTemps.append(line.toDouble() );
    }
    temperatureFile.close();
}

void RiverModel::initializePARValues(const Configuration &config) {
    cout << "LOADING PAR VALUES" << endl;
    QString parFileFilename = config.parFile;

    QFile parFile( parFileFilename );
    if( !parFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        printf("Failed to open the photo radiation file");
        exit(1);
    }
    QTextStream parInput( &parFile );
    while( !parInput.atEnd() ){
        QString line = parInput.readLine();
        parValues.append( line.toInt() );
    }
    parFile.close();
}

void RiverModel::initializeTempGrids(HydroFileDict &hydroFileDict){
    int width = hydroFileDict.getMaxWidth();
    int height = hydroFileDict.getMaxHeight();
    delete source;
    delete dest;
    source = new Grid<FlowData>(width, height);
    dest = new Grid<FlowData>(width, height);
}


int RiverModel::getDaysToRun(const Configuration &config) {
    int daysToRun = 0;
    QVector<uint16_t>::ConstIterator it;
    for (it = config.daysToRun.begin(); it != config.daysToRun.end(); it++)
    {
        daysToRun += *it;
    }

    return daysToRun;
}

void RiverModel::saveAverages(Statistics & stats, int currentDay) {
    /* We are using file descriptors and fprintf after discovering horrible performance on
     * Windows when using QFile or ofstream...
     *
     * Note: QFile is still prefered when NOT saving a file in the program's main loop.
     */

    FILE* f;
    if(averagesFilename.isEmpty()) {
        //File does not yet exist.  We need to create a filename and add table headers
        QString dateAndTime = QDateTime::currentDateTime().toString("MMM_d_H_mm_ss");
        averagesFilename = "./results/data/carbon_avgs_" + dateAndTime + ".csv";


        f = fopen(averagesFilename.toStdString().c_str(), "w");
        if ( f == NULL ) {
            cout << "Failed to open averagesFile for write." << endl;
            abort();
        }
        fprintf(f, "%s\n","Day,Macro,Phyto,Waterdecomp,Seddecomp,Sedconsumer,Consumer, \
                DOC,POC,Herbivore,Detritus,All Carbon" );
    }else{
        //File already exists, open for append
        f = fopen(averagesFilename.toStdString().c_str(), "a");
        if ( f == NULL ) {
            cout << "Failed to open averagesFile for append." << endl;
            abort();
        }
    }

    fprintf(f, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", currentDay, stats.avgMacro,
            stats.avgPhyto, stats.avgWaterDecomp, stats.avgSedDecomp, stats.avgSedConsumer,
            stats.avgConsum, stats.avgDOC, stats.avgPOC, stats.avgHerbivore,
            stats.avgDetritus, stats.avgCarbon);

    fclose(f);
}

void RiverModel::setStatusMessage(QString message) {
    statusMutex.lock();
    modelStatus.setMessage(message);
    statusMutex.unlock();
}

void RiverModel::copy(const RiverModel & other) {
    modelStatus = other.modelStatus;
    if(modelStatus.getState() == Status::RUNNING) {
        abort();
    }

    modelStatus = other.modelStatus;
    modelConfig = other.modelConfig;
    hydroFileDict = other.hydroFileDict;
    waterTemps = other.waterTemps;
    parValues = other.parValues;
    displayedStock = other.displayedStock;
    stockNames = other.stockNames;
    averagesFilename = other.averagesFilename;
    source = new Grid<FlowData>(*other.source);
    dest = new Grid<FlowData>(*other.dest);

    images = other.images;
}

void RiverModel::clear() {
    delete source;
    delete dest;
}
