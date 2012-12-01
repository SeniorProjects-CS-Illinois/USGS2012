#include "modelthread.h"

ModelThread::ModelThread(QObject* parent, RiverModel* rModel) :
    QThread(parent), model(rModel)
{
}

void ModelThread::run()
{
    model->run();
}

void ModelThread::setRiverModel(RiverModel *rModel)
{
    model = rModel;
}
