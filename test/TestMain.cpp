#include <QtTest/QtTest>
#include "GridTests.h"
#include "ReducedGridTests.h"
#include "ConfigTests.h"

int main(int argc, char *argv[])
{
    GridTests gt;
    ReducedGridTests rgt;
    ConfigTests ct;
    return
        QTest::qExec(&gt, argc, argv) ||
        QTest::qExec(&rgt, argc, argv) ||
        QTest::qExec(&ct, argc, argv);
}
