#ifndef MODELTHREAD_H
#define MODELTHREAD_H

#include <QThread>
#include "../main.h"

class ModelThread : public QThread
{
    Q_OBJECT
public:
    explicit ModelThread(QObject *parent = 0);
    void run();

signals:
    // No signals
    
public slots:
    // No slots
};

#endif // MODELTHREAD_H
