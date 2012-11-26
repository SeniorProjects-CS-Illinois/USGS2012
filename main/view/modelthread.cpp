#include "modelthread.h"

ModelThread::ModelThread(QObject *parent) :
    QThread(parent)
{
}

void ModelThread::run()
{
    go_command();
}
