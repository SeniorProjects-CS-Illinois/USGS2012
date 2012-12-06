#include "imagethread.h"

ImageThread::ImageThread(QObject* parent, RiverModel* m) :
    QThread(parent), model(m)
{
}

void ImageThread::run()
{
    unsigned long sleepTimeSeconds = 1;

    // main loop: update GUI, then sleep for a bit
    while (model->getStatus().getState() != Status::COMPLETE)
    {
        cout << "Hello, World!" << endl;
        // TODO: need a way to get most recent image
        QString test("test.jpg");
        QImage stockImage(test);
        emit imageUpdate(stockImage);

        // sleep for now so it doesn't spend too much time in this thread
        sleep(sleepTimeSeconds);
    }
}

void ImageThread::setRiverModel(RiverModel* rModel)
{
    model = rModel;
}
