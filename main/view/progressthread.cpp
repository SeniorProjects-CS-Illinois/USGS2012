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
        Status currentStatus = model->getStatus();
        if (currentStatus.getState() == Status::RUNNING)
        {
            percentageDone = (int)(100*currentStatus.getProgress());
            timeElapsed = currentStatus.getTimeElapsed();
            timeRemaining = currentStatus.getTimeRemaining();

            // emit signals to GUI
            emit progressPercentUpdate(percentageDone);
            emit progressTimeUpdate(timeElapsed, timeRemaining);
        }
        else if (currentStatus.getState() == Status::COMPLETE)
        {
            break;
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
