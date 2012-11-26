#ifndef MODELTHREAD_H
#define MODELTHREAD_H

#include <QThread>
#include "../model/rivermodel.h"

class ModelThread : public QThread
{
    Q_OBJECT
public:
    explicit ModelThread(QObject *parent = 0, RiverModel* rModel = 0);
    void run();

    void setRiverModel(RiverModel* rModel);

signals:
    // No signals
    
public slots:
    // No slots

private:
    RiverModel* model;
};

#endif // MODELTHREAD_H
