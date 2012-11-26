#include "modelthread.h"

ModelThread::ModelThread(QObject* parent, RiverModel* r) :
    QThread(parent)
{
    if (r != NULL)
    {
        model = *r;
    }
}

void ModelThread::run()
{
    model.run();
}
