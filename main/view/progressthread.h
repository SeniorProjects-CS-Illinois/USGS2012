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
     * @param interval sleep time in milliseconds
     */
    explicit ProgressThread(QObject* parent = NULL, RiverModel* rModel = NULL, unsigned long interval = 100L);

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
     * @brief Tells the GUI of current percentage completed.
     * @param level the approximate percentage complete.
     */
    void progressPercentUpdate(int level);

    /**
     * @brief Tells the GUI of current time elapsed/remaining.
     * @param elapsed the time that has elapsed thus far.
     * @param remaining the approximate amount of time remaining.
     */
    void progressTimeUpdate(int elapsed, int remaining);

    /**
     * @brief Tells the GUI of most recent image computed.
     * @param stockImage the most recent image computed.
     */
    void imageUpdate(QImage stockImage);

    /**
     * @brief Tells the GUI of status message of the model.
     * @param message the current status for the model.
     */
    void statusMessageUpdate(QString message);

    /**
     * @brief Tells the GUI that the model is done. Cuurently
     * this just re-enables the run button.
     */
    void finished();

public slots:
    // No slots

private:
    RiverModel* model;

    unsigned long sleepTimeMilliseconds;

    /**
     * Emit the signals involved in progress updates.
     */
    void emitProgress(int percentageDone, int timeElapsed, int timeRemaining);
    
};

#endif // PROGRESSTHREAD_H
