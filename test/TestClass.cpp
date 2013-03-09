#include <QtTest/QtTest>
#include "grid.h"

class TestClass : public QObject
{
    Q_OBJECT
    private slots:
    void gridTest();
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

QTEST_MAIN(TestClass)
#include "TestClass.moc"
