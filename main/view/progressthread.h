#ifndef PROGRESSTHREAD_H
#define PROGRESSTHREAD_H

#include <QThread>
#include <stdint.h>

#include "../model/status.h"
#include "../model/rivermodel.h"

class ProgressThread : public QThread
{
    Q_OBJECT
public:
    /**
     * Constructor for this thread object. Takes in parent
     * for QT compliance and RiverModel to be run.
     */
    explicit ProgressThread(QObject* parent = NULL, RiverModel* rModel = NULL, unsigned long interval = 1L);

    /**
     * Set the model for this thread to run.
     */
    void setModel(RiverModel * rModel);

    /**
     * Overidden run method that is called when the thread
     * is executed. Checks for status updates periodically.
     */
    void run();

signals:
    /**
     * Tells the GUI of current percentage completed.
     */
    void progressPercentUpdate(int level);

    /**
     * Tells the GUI of current time elapsed/remaining.
     */
    void progressTimeUpdate(int elapsed, int remaining);

    /**
     * Tells the GUI of most recent image computed.
     */
    void imageUpdate(QImage stockImage);

    /**
     * Tells the GUI that the model is done. Cuurently
     * this just re-enables the run button.
     */
    void finished();

public slots:
    // No slots

private:
    RiverModel* model;

    unsigned long sleepTimeSeconds;

    /**
     * Emit the signals involved in progress updates.
     */
    void emitProgress(int percentageDone, int timeElapsed, int timeRemaining);
    
};

#endif // PROGRESSTHREAD_H
