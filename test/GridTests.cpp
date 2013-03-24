#include "GridTests.h"

void GridTests::gridTest()
{
    Grid<int> intGrid(2,2);
    QCOMPARE(intGrid.getWidth(), (size_t)2);
    QCOMPARE(intGrid.getHeight(), (size_t)2);
    intGrid(0,0) = 1;
    intGrid(0,1) = 2;
    intGrid(1,0) = 3;
    intGrid(1,1) = 4;

    QCOMPARE(intGrid(0,0), 1);
    QCOMPARE(intGrid(0,1), 2);
    QCOMPARE(intGrid(1,0), 3);
    QCOMPARE(intGrid(1,1), 4);
    
    QCOMPARE(intGrid.getArraySize(), (size_t)4);
    QCOMPARE(intGrid(0), 1);
    QCOMPARE(intGrid(1), 2);
    QCOMPARE(intGrid(2), 3);
    QCOMPARE(intGrid(3), 4);
}