#include <QtTest/QtTest>
#include "GridTests.h"
#include "ReducedGridTests.h"
#include "ConfigTests.h"
#include "HydroFileTests.h"
#include "StatusTests.h"
#include "CarbonFlowMapTests.h"

int main(int argc, char *argv[])
{
    GridTests gt;
    ReducedGridTests rgt;
    ConfigTests ct;
    HydroFileTests hft;
    StatusTests st;
    CarbonFlowMapTests cft;
    return
        QTest::qExec(&gt, argc, argv) ||
        QTest::qExec(&rgt, argc, argv) ||
        QTest::qExec(&ct, argc, argv) ||
        QTest::qExec(&hft, argc, argv) ||
		QTest::qExec(&cft, argc, argv) ||
        QTest::qExec(&st, argc, argv)
		;
}
