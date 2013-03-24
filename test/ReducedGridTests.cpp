#include "ReducedGridTests.h"

void ReducedGridTests::reducedGridTest()
{
	qDebug("Creating Reduced grid");
    ReducedGrid<int> grid(2,2);
	qDebug("Checking for a location that shouldn't be there");
    QVERIFY(!grid.locationExists(1,1));
	qDebug("Adding items");
    grid.addItem(1, 0,0);
	grid.addItem(4, 1,1);
    
	qDebug("Compressing");
	grid.compress();
    
    QVERIFY(grid.locationExists(0,0));
    QVERIFY(grid.locationExists(1,1));
    
    QVERIFY(!grid.locationExists(0,1));
    QVERIFY(!grid.locationExists(1,0));

    QCOMPARE(grid.get(0), 1);
    QCOMPARE(grid.get(1), 4);

    QCOMPARE(grid.get(0,0), 1);
    QCOMPARE(grid.get(1,1), 4);
}