#include "modelthread.h"

ModelThread::ModelThread(QObject* parent, RiverModel* rModel) :
    QThread(parent),
    model(rModel) // intentional shallow copy
{
    // No work needed in constructor.
}

void ModelThread::run()
{
    model->run();
}

void ModelThread::setModel(RiverModel * rModel)
{
    model = rModel;
}

RiverModel* ModelThread::getCurrentModel() const
{
    return model;
}
