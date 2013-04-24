#include "StatusTests.h"
#include <iostream>

using std::cout;
using std::endl;

void StatusTests::initStatusTest() {
    Status modelStatus;
	QCOMPARE(Status::UNCONFIGURED, modelStatus.getState());
}

void StatusTests::setStatusTest() {
    Status modelStatus;
    QCOMPARE(modelStatus.getState(), Status::UNCONFIGURED);
    modelStatus.setState(Status::COMPLETE);    
    QCOMPARE(modelStatus.getState(), Status::UNCONFIGURED);
}

void StatusTests::timeTest() {
    Status modelStatus;
	modelStatus.addWorkUnitsToProcess(1);
    QCOMPARE(modelStatus.getTimeElapsed(), 0);
    modelStatus.setState(Status::READY);
    modelStatus.setState(Status::RUNNING);
	QEXPECT_FAIL("", "FIXME: Need to fix this", Continue);
    modelStatus.updateProgress();
    QVERIFY(modelStatus.getTimeElapsed() > 0);
    modelStatus.setState(Status::COMPLETE);
    int timeElapsed = modelStatus.getTimeElapsed();
    QCOMPARE(modelStatus.getTimeElapsed(), timeElapsed);
    QCOMPARE(modelStatus.getTimeElapsed(), timeElapsed);
}

void StatusTests::hasImageTest() {
    Status modelStatus;
    QCOMPARE(modelStatus.hasNewImage(), false);
    modelStatus.hasNewImage(true);
    QCOMPARE(modelStatus.hasNewImage(), true);
    modelStatus.hasNewImage(false);
    QCOMPARE(modelStatus.hasNewImage(), false);
}

void StatusTests::progressTest() {
    Status modelStatus;
    modelStatus.setWorkUnitsToProcess(1);
    QCOMPARE(modelStatus.getProgress(), 0.0f);
    modelStatus.updateProgress();
    QCOMPARE(modelStatus.getProgress(), 1.0f);
    modelStatus.setWorkUnitsToProcess(2);
    QCOMPARE(modelStatus.getProgress(), 0.5f);
	modelStatus.addWorkUnitsToProcess(2);
    QCOMPARE(modelStatus.getProgress(), 0.25f);
    modelStatus.updateProgress(3);
    QCOMPARE(modelStatus.getProgress(), 1.0f);
    qDebug("This should probably cause an exception");
    modelStatus.updateProgress();
	QEXPECT_FAIL("", "FIXME: Need to fix this", Continue);
    QCOMPARE(modelStatus.getProgress(), 1.0f);
}