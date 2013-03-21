#include "rivermodel.h"

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
    //TODO Get rid of these two functions if possible.
    initialize_globals();
    reset_globals();

    int daysToRun = getDaysToRun(modelConfig);

    initializeHydroMaps(modelConfig);
    initializeWaterTemps(modelConfig);
    initializePARValues(modelConfig);

    initializeModelStatus(daysToRun);
    modelStatus.setState(Status::RUNNING);

    int weeksElapsed = 0;
    int daysElapsed = 0;
    int hoursElapsed = 0;

    //Creates the river and initializes its patches
    River river(modelConfig, hydroFileDict);

    // These are temp structures used in the flowing of the river.  Created
    // here so they are not initialized and destroyed repeatedly.
    int width = hydroFileDict.getMaxWidth();
    int height = hydroFileDict.getMaxHeight();
    Grid<FlowData> * source = new Grid<FlowData>(width, height);
    Grid<FlowData> * dest = new Grid<FlowData>(width, height);

    //Get a hydrofile to process
    for (int hydroIndex = 0; hydroIndex < modelConfig.hydroMaps.size(); hydroIndex++) {
        //NEW HYDROFILE
        QString hydroFileName = modelConfig.hydroMaps[hydroIndex];
        int daysToRunHydroFile = modelConfig.daysToRun[hydroIndex];

        HydroFile * currHydroFile = hydroFileDict[hydroFileName];
        river.setCurrentHydroFile(currHydroFile);
        cout << "RUNNING FILE: " << hydroFileName.toStdString() << " FOR " << daysToRunHydroFile << " DAYS" << endl;

        for(int dayOnHydroFile = 0; dayOnHydroFile < daysToRunHydroFile; dayOnHydroFile++) {
            if(daysElapsed % 7 == 0){
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

            //TODO Gather max patch values here if other code needs them
            river.saveCSV(displayedStock, daysElapsed);

            //TODO Add back in image generation
            modelStatus.hasNewImage(true);

            daysElapsed++;
            if(daysElapsed % 7 == 0){
                //END OF WEEK
                weeksElapsed++;
            }
        }
    }

    //Remove temp structures used for flowing river
    delete source;
    delete dest;

    //TODO Identify refactoring changes in cleanup.  Delete new'd data (i.e. hydromaps)
    //cleanup();

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

void RiverModel::initializeModelStatus(int daysToRun)
{
    modelStatus.addWorkUnitsToProcess(daysToRun * 24);
    modelStatus.setState(Status::READY);
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

int RiverModel::getDaysToRun(const Configuration &config) {
    int daysToRun = 0;
    QVector<uint16_t>::ConstIterator it;
    for (it = config.daysToRun.begin(); it != config.daysToRun.end(); it++)
    {
        daysToRun += *it;
    }

    return daysToRun;
}

