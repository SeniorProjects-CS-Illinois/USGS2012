#include "StatusTests.h"

void StatusTests::statusTest() {
    Status modelStatus;
	QCOMPARE(Status::UNCONFIGURED,  modelStatus.getState());
}