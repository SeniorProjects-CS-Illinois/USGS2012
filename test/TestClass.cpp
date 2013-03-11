#include <QtTest/QtTest>
#include "grid.h"
#include "reducedgrid.h"

class TestClass : public QObject
{
    Q_OBJECT
    private slots:
    void gridTest();
    void reducedGridTest();
};

void TestClass::gridTest()
{
    Grid<int> intGrid(2,2);
    QVERIFY(intGrid.getWidth() == 2);
    QVERIFY(intGrid.getHeight() == 2);
    intGrid(0,0) = 1;
    intGrid(0,1) = 2;
    intGrid(1,0) = 3;
    intGrid(1,1) = 4;

    QVERIFY(intGrid(0,0) == 1);
    QVERIFY(intGrid(0,1) == 2);
    QVERIFY(intGrid(1,0) == 3);
    QVERIFY(intGrid(1,1) == 4);
    
    QVERIFY(intGrid.getArraySize() == 4);
    QVERIFY(intGrid(0) == 1);
    QVERIFY(intGrid(1) == 2);
    QVERIFY(intGrid(2) == 3);
    QVERIFY(intGrid(3) == 4);

}

void TestClass::reducedGridTest()
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

    QVERIFY(1 == grid.get(0));
    QVERIFY(4 == grid.get(1));

    QVERIFY(1 == grid.get(0,0));
    QVERIFY(4 == grid.get(1,1));
}

QTEST_MAIN(TestClass)
#include "TestClass.moc"
