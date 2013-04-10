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
    explicit ModelThread(QObject * parent = NULL, RiverModel * rModel = NULL);

    /**
     * Overidden run method that is called when the thread
     * is executed. Just runs the model.
     */
    void run();

    /**
     * Set the model for this thread to run.
     */
    void setModel(RiverModel *rModel);

    /**
     * Get the current model <i>BY REFERENCE</i>
     */
    RiverModel* getCurrentModel() const;

signals:
    // No signals
    
public slots:
    // No slots

private:
    RiverModel* model;
};

#endif // MODELTHREAD_H
