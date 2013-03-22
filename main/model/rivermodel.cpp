#include "rivermodel.h"

RiverModel::RiverModel() {

}

Status RiverModel::getStatus(void){
    Status modelStatusGUI = modelStatus;

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

    g.imageMutex.lock();
    for(int i = 0; i < g.NUM_STOCKS; i++){
        if(g.stock_names[i] == stockName){
            stockImage = *(g.images[i]);
            break;
        }
    }
    g.imageMutex.unlock();

    return stockImage;
}

//     was doing aside from creating output dirs.
void RiverModel::run(void) {
    setup(modelConfig);

    initialize_globals();
    initializeModelStatus(getDaysToRun(modelConfig));

    modelStatus.setState(Status::RUNNING);

    g.gui_days_to_run = 0;
    int days_elapsed = 0;
    int hours_elapsed = 0;

    for(int index = 0; index < modelConfig.hydroMaps.size(); index++)
    {
        cout << "RUNNING FILE: " << modelConfig.hydroMaps[index].toStdString();
        cout << " FOR " << modelConfig.daysToRun[index] << " DAYS" << endl;

        g.gui_days_to_run += modelConfig.daysToRun[index];  //Set howmany days to run the new hydromap
        g.hydro_group = (g.hydromap_index_vector[index] + 1); //Set the new hydromap that will run
        g.hydro_changed = 1;  //Confirm that a new hydro map has been loaded

        while( days_elapsed < g.gui_days_to_run)
        {
            cout << "Day: " << (days_elapsed + 1) << " - Hour: " << ((g.hours)%24) \
                << " | Progress: " << (int)(modelStatus.getProgress()*100) \
                << "% - Time Elapsed/Remaining (sec): " << modelStatus.getTimeElapsed() \
                << " / " << modelStatus.getTimeRemaining() << endl;
            go(modelConfig);
            modelStatus.updateProgress();

            hours_elapsed++;

            if( hours_elapsed % 24 == 0) {
                days_elapsed++;
                modelStatus.hasNewImage(true);
            }
        }
    }

    cleanup();

    cout << endl << "PROCESSING COMPLETE" << endl;
    modelStatus.setState(Status::COMPLETE);
}

void RiverModel::newRun() {
    initializeModel(modelConfig);

    int weeksElapsed = 0;
    int daysElapsed = 0;
    int hoursElapsed = 0;

    //Creates the river and initializes its patches
    River river(modelConfig, hydroFileDict);
    modelStatus.setState(Status::RUNNING);

    //Get a hydrofile to process
    for (int hydroIndex = 0; hydroIndex < modelConfig.hydroMaps.size(); hydroIndex++) {
        //NEW HYDROFILE
        QString hydroFileName = modelConfig.hydroMaps[hydroIndex];
        int daysToRunHydroFile = modelConfig.daysToRun[hydroIndex];

        HydroFile * currHydroFile = hydroFileDict[hydroFileName];
        river.setCurrentHydroFile(currHydroFile);
        cout << "RUNNING FILE: " << hydroFileName.toStdString() << " FOR " << daysToRunHydroFile << " DAYS" << endl;

        for(int dayOnHydroFile = 0; dayOnHydroFile < daysToRunHydroFile; dayOnHydroFile++) {
            if(daysElapsed % DAYS_PER_WEEK == 0){
                //BEGINNING OF WEEK
                river.setCurrentWaterTemperature( waterTemps[weeksElapsed] );
            }
            //BEGINNING OF DAY


            for(int hour = 0; hour < HOURS_PER_DAY; hour++) {
                //NEW HOUR
                printHourlyMessage(daysElapsed, hour);
                river.setCurrentPAR( parValues[hoursElapsed] );
                river.processPatches();
                river.flow(source, dest);
                modelStatus.updateProgress();

                hoursElapsed++;
            }
            //END OF DAY
            Statistics stats = river.generateStatistics();
            river.saveCSV(displayedStock, daysElapsed);
            river.generateImages(images, stockNames, imageMutex, stats);
            saveAverages(stats,daysElapsed);
            modelStatus.hasNewImage(true);

            daysElapsed++;
            if(daysElapsed % DAYS_PER_WEEK == 0){
                //END OF WEEK

                weeksElapsed++;
            }
        }
    }

    //Remove temp structures used for flowing river
    deleteTempGrids();

    //TODO Run program in valgrind to make sure all memory is freed.

    cout << endl << "PROCESSING COMPLETE" << endl;
    modelStatus.setState(Status::COMPLETE);
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

void RiverModel::printHourlyMessage(int daysElapsed, int hourOfDay) {
    int currentDay = daysElapsed + 1;
    cout << "Day: " << currentDay << " - Hour: " << hourOfDay \
        << " | Progress: " << (int)(modelStatus.getProgress()*100) \
        << "% - Time Elapsed/Remaining (sec): " << modelStatus.getTimeElapsed() \
        << " / " << modelStatus.getTimeRemaining() << endl;
}

//TODO Move this to construct and add the "Big three" (CCtor, assignment operator, destructor)
void RiverModel::initializeModel(const Configuration &config){
    //TODO Get rid of these two functions if possible.
    initialize_globals();
    reset_globals();

    initializeHydroMaps(modelConfig);
    initializeWaterTemps(modelConfig);
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
    stockNames.append("consum");
    stockNames.append("doc");
    stockNames.append("poc");
    stockNames.append("detritus");
    stockNames.append("all_carbon");
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
    source = new Grid<FlowData>(width, height);
    dest = new Grid<FlowData>(width, height);
}


//TODO Move to destructor when one is added.
void RiverModel::deleteTempGrids(){
    delete source;
    delete dest;
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

void RiverModel::saveAverages(Statistics & stats, int daysElapsed) {
    int currentDay = daysElapsed + 1;

    QFile averagesFile;
    QTextStream textStream;
    if(averagesFilename.isEmpty()) {
        //File does not yet exist.  We need to create a filename and add table headers
        QString dateAndTime = QDateTime::currentDateTime().toString("MMM_d_H_mm_ss");
        averagesFilename = "./results/data/carbon_avgs_" + dateAndTime + ".csv";
        averagesFile.setFileName(averagesFilename);
        if ( !averagesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            cout << "Failed to open averagesFile for write." << endl;
            abort();
        }
        textStream.setDevice(&averagesFile);
        textStream << "Day,Macro,Phyto,Waterdecomp,Seddecomp,Sedconsumer,Consumer,"
                   << "DOC,POC,Herbivore,Detritus,All Carbon\n";

    }else{
        //File already exists, open for append
        averagesFile.setFileName(averagesFilename);
        if ( !averagesFile.open(QIODevice::Append | QIODevice::Text)) {
            cout << "Failed to open averagesFile for append." << endl;
            abort();
        }
        textStream.setDevice(&averagesFile);
    }

    textStream << currentDay << "," << stats.avgMacro << "," << stats.avgPhyto << ","
               << stats.avgWaterDecomp << "," << stats.avgSedDecomp << ","
               << stats.avgSedConsumer << "," << stats.avgConsum << ","
               << stats.avgDOC << "," << stats.avgPOC << "," << stats.avgHerbivore << ","
               << stats.avgDetritus << "," << stats.avgCarbon << "\n";


    averagesFile.close();
}
