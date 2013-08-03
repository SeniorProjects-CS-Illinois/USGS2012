#include "RiverIOFileTests.h"
#include <iostream>
using std::cout;
using std::endl;

void RiverIOFileTests::RiverIOFileTest(){
    RiverIOFile file("../data/testData/ioTestData.txt"); 

    // Check that values are correctly stored in the file
    QVERIFY(file.inputs.contains(QPoint(0,0)));
    QVERIFY(file.inputs.contains(QPoint(1,1)));
    QVERIFY(file.inputs.contains(QPoint(2,3)));
    QVERIFY(file.inputs.contains(QPoint(4,5)));
    QVERIFY(file.inputs.contains(QPoint(7,6)));

    QVERIFY(file.outputs.contains(QPoint(10,10)));
    QVERIFY(file.outputs.contains(QPoint(11,11)));
    QVERIFY(file.outputs.contains(QPoint(12,13)));
    QVERIFY(file.outputs.contains(QPoint(14,15)));
    QVERIFY(file.outputs.contains(QPoint(17,16)));

    // Check that no inputs are outputs and vice versa
    QVERIFY(!file.outputs.contains(QPoint(0,0)));
    QVERIFY(!file.outputs.contains(QPoint(1,1)));
    QVERIFY(!file.outputs.contains(QPoint(2,3)));
    QVERIFY(!file.outputs.contains(QPoint(4,5)));
    QVERIFY(!file.outputs.contains(QPoint(7,6)));

    QVERIFY(!file.inputs.contains(QPoint(10,10)));
    QVERIFY(!file.inputs.contains(QPoint(11,11)));
    QVERIFY(!file.inputs.contains(QPoint(12,13)));
    QVERIFY(!file.inputs.contains(QPoint(14,15)));
    QVERIFY(!file.inputs.contains(QPoint(17,16)));

    // Check values around inputs and outputs aren't included (corner cases)
    QVERIFY(!file.inputs.contains(QPoint(0,1)));
    QVERIFY(!file.inputs.contains(QPoint(1,0)));
    QVERIFY(!file.inputs.contains(QPoint(2,2)));
    QVERIFY(!file.inputs.contains(QPoint(1,2)));
    QVERIFY(!file.inputs.contains(QPoint(2,4)));

    QVERIFY(!file.outputs.contains(QPoint(9,10)));
    QVERIFY(!file.outputs.contains(QPoint(10,9)));
    QVERIFY(!file.outputs.contains(QPoint(11,10)));
    QVERIFY(!file.outputs.contains(QPoint(10,11)));
}

void RiverIOFileTests::testEmptyFile()
{
    RiverIOFile file("../data/testData/emptyIOTestData.txt"); 
    QVERIFY(!file.inputs.contains(QPoint(0,0)));
    QVERIFY(!file.inputs.contains(QPoint(0,1)));
    QVERIFY(!file.inputs.contains(QPoint(1,0)));
    QVERIFY(!file.inputs.contains(QPoint(1,1)));

    QVERIFY(!file.outputs.contains(QPoint(0,0)));
    QVERIFY(!file.outputs.contains(QPoint(0,1)));
    QVERIFY(!file.outputs.contains(QPoint(1,0)));
    QVERIFY(!file.outputs.contains(QPoint(1,1)));
}