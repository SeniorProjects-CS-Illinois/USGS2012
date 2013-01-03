#ifndef MODELTHREAD_H
#define MODELTHREAD_H

#include <QThread>
#include "../model/rivermodel.h"

class ModelThread : public QThread
{
    Q_OBJECT
public:
    /**
     * Constructor for this thread object. Takes in parent
     * for QT compliance and RiverModel to be run.
     */
    explicit ModelThread(QObject *parent = 0, RiverModel* rModel = 0);

    /**
     * Overidden run method that is called when the thread
     * is executed. Just runs the model.
     */
    void run();

signals:
    // No signals
    
public slots:
    // No slots

private:
    RiverModel* model;
};

#endif // MODELTHREAD_H
