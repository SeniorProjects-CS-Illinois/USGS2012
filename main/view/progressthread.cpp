#include "progressthread.h"

ProgressThread::ProgressThread(QObject* parent, RiverModel *rModel) :
    QThread(parent), model(rModel)
{
}

void ProgressThread::run()
{
    unsigned long sleepTimeSeconds = 1; // TODO: should this be configurable?
    int timeElapsed, timeRemaining;
    int percentageDone = timeElapsed = timeRemaining = 0;

    // main progress loop: update GUI, then sleep for a bit
    while (true)
    {
        // get the current status
        Status currentStatus = model->getStatus();

        // check if the model is still running
        if (currentStatus.getState() == Status::RUNNING)
        {
            percentageDone = (int)(100*currentStatus.getProgress());
            timeElapsed = currentStatus.getTimeElapsed();
            timeRemaining = currentStatus.getTimeRemaining();

            // emit signals to GUI
            emit progressPercentUpdate(percentageDone);
            emit progressTimeUpdate(timeElapsed, timeRemaining);
        }

        // check if model is finished
        else if (currentStatus.getState() == Status::COMPLETE)
        {
            break;
        }

        // see if there is a new image to be displayed
        if (currentStatus.hasNewImage())
        {
            // TODO: need a way to get most recent image
            QString test("test.jpg");
            QImage stockImage(test);
            emit imageUpdate(stockImage);
        }

        // sleep for now so it doesn't spend too much time in this thread
        sleep(sleepTimeSeconds);
    }

    // fix the values for the progress
    if (model->getStatus().getState() == Status::COMPLETE)
    {
        emit progressPercentUpdate(100);
        emit progressTimeUpdate(timeElapsed, 0);
    }

    // tell GUI that it is finished
    emit finished();
}

void ProgressThread::setRiverModel(RiverModel* rModel)
{
    model = rModel;
}
