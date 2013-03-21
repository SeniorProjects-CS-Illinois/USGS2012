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
    return getImage(config.whichStock);
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

void RiverModel::initializeModelStatus()
{
    QVector<uint16_t>::Iterator it;
    for (it = config.daysToRun.begin(); it != config.daysToRun.end(); it++)
    {
        modelStatus.addWorkUnitsToProcess((*it) * 24);
    }

    modelStatus.setState(Status::READY);
}

//     was doing aside from creating output dirs.
void RiverModel::run(void) {
    setup(config);

    initialize_globals();
    initializeModelStatus();

    modelStatus.setState(Status::RUNNING);

    g.gui_days_to_run = 0;
    int days_elapsed = 0;
    int hours_elapsed = 0;

    for(int index = 0; index < config.hydroMaps.size(); index++)
    {
        cout << "RUNNING FILE: " << config.hydroMaps[index].toStdString();
        cout << " FOR " << config.daysToRun[index] << " DAYS" << endl;

        g.gui_days_to_run += config.daysToRun[index];  //Set howmany days to run the new hydromap
        g.hydro_group = (g.hydromap_index_vector[index] + 1); //Set the new hydromap that will run
        g.hydro_changed = 1;  //Confirm that a new hydro map has been loaded

        while( days_elapsed < g.gui_days_to_run)
        {
            cout << "Day: " << (days_elapsed + 1) << " - Hour: " << ((g.hours)%24) \
                << " | Progress: " << (int)(modelStatus.getProgress()*100) \
                << "% - Time Elapsed/Remaining (sec): " << modelStatus.getTimeElapsed() \
                << " / " << modelStatus.getTimeRemaining() << endl;
            go(config);
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
    initialize_globals(); //Fine


    int totalDaysToRun = 0;
    //TODO: Stick this in its own function.
    QVector<uint16_t>::Iterator it;
    for (it = config.daysToRun.begin(); it != config.daysToRun.end(); it++)
    {
        totalDaysToRun += *it;
    }

    //TODO refactor and integrate all the setup stuff...
    //setup(config);

    //TODO Create a function for hydroFileDict initialization
    QStringList hydroFileNames;
    for(int i = 0; i < config.hydroMaps.size(); i++){
        hydroFileNames.append(config.hydroMaps[i]);
    }
    HydroFileDict hydroFiles(hydroFileNames);

    //TODO Create a function for waterTemp initialization
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

    //TODO Create a function for parValue initialization
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

    //TODO pass in totalDaysToRun as a parameter.
    initializeModelStatus();

    modelStatus.setState(Status::RUNNING); //Fine

    //TODO Already set in initialize_globals, does it need to be a global?
    g.gui_days_to_run = 0;
    int weeks_elapsed = 0; //Fine
    int days_elapsed = 0; //Fine
    int hours_elapsed = 0; //Fine

    //Creates a new river and initializes its patches
    River river(config, hydroFiles);
    int width = hydroFiles.getMaxWidth();
    int height = hydroFiles.getMaxHeight();

    Grid<FlowData> * source = new Grid<FlowData>(width, height);
    Grid<FlowData> * dest = new Grid<FlowData>(width, height);

    for (int hydroIndex = 0; hydroIndex < config.hydroMaps.size(); hydroIndex++) {
        QString hydroFileName = config.hydroMaps[hydroIndex];
        int daysToRunHydroFile = config.daysToRun[hydroIndex];

        g.gui_days_to_run += config.daysToRun[hydroIndex];  //Set howmany days to run the new hydromap

        HydroFile * currHydroFile = hydroFiles[hydroFileName];
        river.setCurrentHydroFile(currHydroFile);

        cout << "RUNNING FILE: " << hydroFileName.toStdString() << " FOR " << daysToRunHydroFile << " DAYS" << endl;

        for(int dayOnHydroFile = 0; dayOnHydroFile < daysToRunHydroFile; dayOnHydroFile++) {
            river.setCurrentWaterTemperature( waterTemps[weeks_elapsed] );

            for(int hour = 0; hour < HOURS_PER_DAY; hour++) {
                //TODO Make the following cout statement a function.
                int currentDay = days_elapsed + 1;
                cout << "Day: " << currentDay << " - Hour: " << hour \
                    << " | Progress: " << (int)(modelStatus.getProgress()*100) \
                    << "% - Time Elapsed/Remaining (sec): " << modelStatus.getTimeElapsed() \
                    << " / " << modelStatus.getTimeRemaining() << endl;

                river.setCurrentPAR( parValues[hours_elapsed] );
                river.processPatches();
                river.flow(source, dest);

                modelStatus.updateProgress();
                hours_elapsed++;
            }
            //TODO Gather max patch values here if other code needs them
            //TODO Pass as a parameter which stock and days_elapsed.
            river.saveCSV();

            //TODO Add back in image generation

            days_elapsed++;
            modelStatus.hasNewImage(true);
            if(days_elapsed % 7 == 0){
                weeks_elapsed++;
            }
        }
    }

    delete source;
    delete dest;

    //TODO Identify refactoring changes in cleanup.  Delete new'd data (i.e. hydromaps)
    //cleanup();

    cout << endl << "PROCESSING COMPLETE" << endl;
    modelStatus.setState(Status::COMPLETE);

}

void RiverModel::setConfiguration(const Configuration & configuration)
{
    //TODO change this so it also sets a whichstock member variable
    config = configuration;
}

void RiverModel::setWhichStock(QString stockName)
{
    //TODO Change this so it assigns to a member variable
    config.whichStock = stockName;
}
