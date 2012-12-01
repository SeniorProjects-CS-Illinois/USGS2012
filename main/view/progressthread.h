#ifndef PROGRESSTHREAD_H
#define PROGRESSTHREAD_H

#include <QThread>
#include "../model/status.h"
#include "../model/rivermodel.h"
#include <stdint.h>

class ProgressThread : public QThread
{
    Q_OBJECT
public:
    explicit ProgressThread(QObject* parent = 0, RiverModel* rModel = 0);
    void run();

    void setRiverModel(RiverModel* rModel);

signals:
    void progressPercentUpdate(int level);
    void progressTimeUpdate(int elapsed, int remaining);

    void finished();

public slots:
    // No slots

private:
    RiverModel* model;
    
};

#endif // PROGRESSTHREAD_H
