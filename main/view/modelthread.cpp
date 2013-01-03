#include "modelthread.h"

ModelThread::ModelThread(QObject* parent, RiverModel* rModel) :
    QThread(parent),
    model(rModel)
{
    // No work needed in constructor
}

void ModelThread::run()
{
    model->run();
}
