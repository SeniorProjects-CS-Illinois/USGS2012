#ifndef STATUS_H
#define STATUS_H

#include <QString>
#include <QTime>
#include <climits>

class Status {
    public:
        enum ModelState {UNCONFIGURED, READY, RUNNING, COMPLETE, PAUSED, ERR};

        //------------------------------
        //Functions relevant to the view

        /**
         * \brief Returns a percent complete for the current run.
         */
        float getProgress(void);

        /**
         * \brief Returns the state of the model.
         */
        ModelState getState(void);

        /**
         * \brief Returns an error message if an error occurred.
         */
        QString getErrorMessage(void);

        /**
         * \brief Returns the time elapsed in seconds.
         */
        int getTimeElapsed(void);

        /**
         * \brief Returns the estimated time remaining in seconds.
         */
        int getTimeRemaining(void);

        /**
         * \brief Returns true if a new image exists.
         */
        bool hasNewImage(void);

        /**
         * \brief Sets image availability to boolean parameter
         */
        void hasNewImage(bool newImageStatus);



        //-------------------------------
        //Functions relevant to the model

        /**
         * \brief Constructor.  Sets state to UNCONFIGURED.  Note that the model must be configured before you
         * can query for any status other than the model's state.
         */
        Status(void);

        /**
         * \brief Sets the ammount of work we have.
         */
        void setWorkUnitsToProcess(unsigned long workUnitsToProcess);

        /**
         * \brief Adds additional work units to process
         */
        void addWorkUnitsToProcess(unsigned long workUnistsToProcess);

        /**
         * \brief Allows the model to update its state.
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
        bool newImageExists;
        QTime timer;
        QString errorMessage;
        int timeElapsedBeforePauseState;
};

#endif
