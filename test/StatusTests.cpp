#include "StatusTests.h"

void StatusTests::statusTest() {
    Status modelStatus;
	QCOMPARE(Status::ModelState::UNCONFIGURED,  modelStatus.getState());
}