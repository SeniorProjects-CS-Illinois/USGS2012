#ifndef STATUS_H
#define STATUS_H

#include <QString>
#include <QTime>
#include <climits>

class Status {
    public:
        enum ModelState { UNCONFIGURED, READY, RUNNING, COMPLETE, PAUSED, ERROR };

        //------------------------------
        //Functions relevant to the view

        /**
         * Returns a percent complete for the current run.
         */
        float getProgress(void);

        /**
         * Returns the state of the model.
         */
        ModelState getState(void);

        /**
         * Returns an error message if an error occurred.
         */
        QString getErrorMessage(void);

        /**
         * Returns the time elapsed in seconds.
         */
        int getTimeElapsed(void);

        /**
         * Returns the estimated time remaining in seconds.
         */
        int getTimeRemaining(void);



        //-------------------------------
        //Functions relevant to the model

        /**
         * Constructor.  Sets state to UNCONFIGURED.  Note that the model must be configured before you
         * can query for any status other than the model's state.
         */
        Status(void);

        /**
         * Sets the ammount of work we have.
         */
        void setWorkUnitsToProcess(unsigned long workUnitsToProcess);

        /**
         * Allows the model to update its state.
         */
        void setState(ModelState newState);

        /**
         * Updated workUnitsProcessed by 1
         */
        void updateProgress(void);

        /**
         * Updated workUnitsProcessed by a defined value.
         */
        void updateProgress(unsigned long workUnitsCompleted);

        /**
         * Sets model state to error and records a message.
         */
        void setErrorMessage(QString newErrorMessage);


    private:
        ModelState currentState;
        unsigned long workUnits;
        unsigned long workUnitsProcessed;
        QTime timer;
        QString errorMessage;
        int timeElapsedBeforePauseState;
};

#endif
