#include "progressthread.h"

ProgressThread::ProgressThread(QObject* parent, RiverModel *rModel, unsigned long interval) :
    QThread(parent),
    model(rModel), // intentional shallow copy
    sleepTimeMilliseconds(interval)
{
    // No work needed in constructor
}

void ProgressThread::run()
{
    int timeElapsed, timeRemaining, percentageDone;
    percentageDone = timeElapsed = timeRemaining = 0;

    // main progress loop: update GUI, then sleep for a bit
    while (true)
    {
        // get the current status
        Status currentStatus = model->getStatus();
        emit statusMessageUpdate(currentStatus.getMessage());

        // see if there is a new image to be displayed
        if (currentStatus.hasNewImage())
        {
            emit imageUpdate(model->getImage());
            // TODO: if they are not looking at the most recent image,
            //       maybe don't update the current image...
        }

        // check if the model is still running
        if (currentStatus.getState() == Status::RUNNING)
        {
            percentageDone = (int)(100*currentStatus.getProgress());
            timeElapsed = currentStatus.getTimeElapsed();
            timeRemaining = currentStatus.getTimeRemaining();
            emitProgress(percentageDone, timeElapsed, timeRemaining);
        }

        // check if model is finished
        else if (currentStatus.getState() == Status::COMPLETE)
        {
            break;
        }

        // sleep for now so it doesn't spend too much time in this thread
        msleep(sleepTimeMilliseconds);
    }

    // fix the values for the progress
    if (model->getStatus().getState() == Status::COMPLETE)
    {
        emitProgress(100, timeElapsed, 0);
        emit imageUpdate(model->getImage());
    }

    // tell GUI that it is finished
    emit finished();
}

void ProgressThread::emitProgress(int percentageDone, int timeElapsed, int timeRemaining)
{
    emit progressPercentUpdate(percentageDone);
    emit progressTimeUpdate(timeElapsed, timeRemaining);
}


void ProgressThread::setModel(RiverModel * rModel)
{
    model = rModel;
}
