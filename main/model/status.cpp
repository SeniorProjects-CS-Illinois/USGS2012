#include "status.h"

float Status::getProgress(void) const {
    return workUnitsProcessed / (float)workUnits;
}

Status::ModelState Status::getState(void) const {
    return currentState;
}

QString Status::getErrorMessage(void) const {
    return errorMessage;
}

QString Status::getMessage(void) const {
    return message;
}

void Status::setMessage(QString message) {
    this->message = message;
}

int Status::getTimeElapsed(void) const {
    //Convert from milliseconds to seconds before we return.
    if(currentState == RUNNING) {
        return (timeElapsedBeforePauseState + timer.elapsed()) / 1000 ;
    } else {
        return timeElapsedBeforePauseState / 1000;
    }
}

int Status::getTimeRemaining(void) const {
    if( workUnitsProcessed == 0) {
        return INT_MAX;
    }
    return (int)(( (workUnits - workUnitsProcessed) * getTimeElapsed() )/ (float)workUnitsProcessed);
}

bool Status::hasNewImage(void) const {
    return newImageExists;
}

void Status::hasNewImage(bool newImageStatus){
    newImageExists = newImageStatus;
}

void Status::reset()
{
    currentState = UNCONFIGURED;
    timeElapsedBeforePauseState = 0;
    workUnitsProcessed = 0;
    workUnits = 0;
    newImageExists = false;
}

Status::Status(void){
    reset();
}

void Status::setWorkUnitsToProcess(unsigned long workUnitsToProcess){
    workUnits = 0;
    addWorkUnitsToProcess(workUnitsToProcess);
}

void Status::addWorkUnitsToProcess(unsigned long workUnitsToProcess){
    if(workUnitsToProcess > 0){
        workUnits += workUnitsToProcess;
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

    if(newState == ERR){
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
    setState(ERR);
    errorMessage = newErrorMessage;
}
