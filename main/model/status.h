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
         * @brief Returns a percent complete for the current run.
         */
        float getProgress(void) const ;

        /**
         * @brief Returns the state of the model.
         */
        ModelState getState(void) const;

        /**
         * @brief Returns an error message if an error occurred.
         */
        QString getErrorMessage(void) const;

        /**
         * @brief Retrieves the message the model wants displayed by the GUI
         * @return String to display
         */
        QString getMessage(void) const;

        /**
         * @brief Message to be displayed by gui
         * @param message String to display
         */
        void setMessage(QString message);

        /**
         * @brief Returns the time elapsed in seconds.
         */
        int getTimeElapsed(void) const;

        /**
         * @brief Returns the estimated time remaining in seconds.
         */
        int getTimeRemaining(void) const;

        /**
         * @brief Returns true if a new image exists.
         */
        bool hasNewImage(void) const;

        /**
         * @brief Sets image availability to boolean parameter
         */
        void hasNewImage(bool newImageStatus);

        /**
         * @brief clear out any information.
         */
        void reset();



        //-------------------------------
        //Functions relevant to the model

        /**
         * @brief Constructor.  Sets state to UNCONFIGURED.  Note that the model must be configured before you
         * can query for any status other than the model's state.
         */
        Status(void);

        /**
         * @brief Sets the ammount of work we have.
         */
        void setWorkUnitsToProcess(unsigned long workUnitsToProcess);

        /**
         * @brief Adds additional work units to process
         */
        void addWorkUnitsToProcess(unsigned long workUnistsToProcess);

        /**
         * @brief Allows the model to update its state.
         */
        void setState(ModelState newState);

        /**
         * @brief Updated workUnitsProcessed by 1
         */
        void updateProgress(void);

        /**
         * @brief Updated workUnitsProcessed by a defined value.
         */
        void updateProgress(unsigned long workUnitsCompleted);

        /**
         * @brief Sets model state to error and records a message.
         */
        void setErrorMessage(QString newErrorMessage);


    private:
        ModelState currentState;
        unsigned long workUnits;
        unsigned long workUnitsProcessed;
        bool newImageExists;
        QTime timer;
        QString errorMessage;
        QString message;
        int timeElapsedBeforePauseState;
};

#endif
