#include "progressthread.h"

ProgressThread::ProgressThread(QObject* parent, RiverModel *rModel) :
    QThread(parent), model(rModel)
{
}

void ProgressThread::run()
{
    unsigned long sleepTimeSeconds = 1;
    while (true)
    {
        //cout << "PROGRESS THREAD: RUN" << endl;
        Status currentStatus = model->getStatus();
        if (currentStatus.getState() == Status::RUNNING)
        {
            int percentageDone = (int)(100*currentStatus.getProgress());
            int timeElapsed = currentStatus.getTimeElapsed();
            int timeRemaining = currentStatus.getTimeRemaining();

            // emit signals to GUI
            emit progressPercentUpdate(percentageDone);
            emit progressTimeUpdate(timeElapsed, timeRemaining);
        }
        else if (currentStatus.getState() == Status::COMPLETE)
        {
            break;
        }
        sleep(sleepTimeSeconds);
    }

    // tell GUI that it is finished
    emit finished();
}

void ProgressThread::setRiverModel(RiverModel* rModel)
{
    model = rModel;
}
