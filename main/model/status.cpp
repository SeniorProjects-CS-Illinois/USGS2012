#include "status.h"

float Status::getProgress(void){
    return workUnitsProcessed / (float)workUnits;
}

Status::ModelState Status::getState(void){
    return currentState;
}

QString Status::getErrorMessage(void){
    return errorMessage;
}

int Status::getTimeElapsed(void){
    //Convert from milliseconds to seconds before we return.
    if(currentState == RUNNING) {
        return (timeElapsedBeforePauseState + timer.elapsed()) / 1000 ;
    } else {
        return timeElapsedBeforePauseState / 1000;
    }
}

int Status::getTimeRemaining(void){
    if( workUnitsProcessed == 0) 
    {
        return INT_MAX;
    }
    return (int)( (workUnits - workUnitsProcessed)/ (float)workUnitsProcessed ) * getTimeElapsed();
}

Status::Status(void){
    currentState = UNCONFIGURED;
    timeElapsedBeforePauseState = 0;
    workUnitsProcessed = 0;
}

void Status::setWorkUnitsToProcess(unsigned long workUnitsToProcess){
    if(workUnitsToProcess > 0){
        workUnits = workUnitsToProcess;
    }
}

void Status::setState(ModelState newState){
    //Perform sanity checks for state changes.

    if(currentState == UNCONFIGURED && newState == READY){
        currentState = newState;
        return;
    }

    if(currentState == READY && newState == RUNNING){
        currentState = newState;
        timer.start();
        return;
    }

    if(currentState == RUNNING && newState == PAUSED){
        currentState = newState;
        timeElapsedBeforePauseState += timer.elapsed();
        return;
    }

    if(currentState == RUNNING && newState == COMPLETE){
        currentState = newState;
        return;
    }

    if(currentState == PAUSED && newState == RUNNING){
        currentState = newState;
        timer.restart();
        return;
    }

    if(newState == ERROR){
        currentState = newState;
        return;
    }

    //TODO: If none of the above state transitions are found, trip an assertion.
}

void Status::updateProgress(void){
    updateProgress(1);
}

void Status::updateProgress(unsigned long workUnitsCompleted){
    workUnitsProcessed += workUnitsCompleted;
}

void Status::setErrorMessage(QString newErrorMessage){
    setState(ERROR);
    errorMessage = newErrorMessage;
}
