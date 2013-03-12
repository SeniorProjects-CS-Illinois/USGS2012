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

void RiverModel::setConfiguration(const Configuration & configuration)
{
    config = configuration;
}

void RiverModel::setWhichStock(QString stockName)
{
    config.whichStock = stockName;
}
