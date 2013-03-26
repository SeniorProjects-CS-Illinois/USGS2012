#include "HydroFileTests.h"

void HydroFileTests::initTestCase() {
    hydroFile_.loadFromFile("../data/testData/testHydroFile.txt");
}

void HydroFileTests::dimensionsTest() {
    QCOMPARE(hydroFile_.getMapHeight(), 6);
    QCOMPARE(hydroFile_.getMapWidth(), 6);
}

void HydroFileTests::patchExistTest() {
    QVERIFY(hydroFile_.patchExists(1,1));
    QVERIFY(hydroFile_.patchExists(2,2));
    QVERIFY(hydroFile_.patchExists(3,3));
    QVERIFY(hydroFile_.patchExists(4,4));
    QVERIFY(hydroFile_.patchExists(5,5));
}

void HydroFileTests::patchNotExhistTest() {
    QVERIFY(!hydroFile_.patchExists(6,6));
    QVERIFY(!hydroFile_.patchExists(0,0));
}

void HydroFileTests::depthTest() {
    QCOMPARE(1.0, hydroFile_.getDepth(1,1));
    QCOMPARE(2.0, hydroFile_.getDepth(2,2));
    QCOMPARE(3.0, hydroFile_.getDepth(3,3));
    QCOMPARE(4.0, hydroFile_.getDepth(4,4));
    QCOMPARE(5.0, hydroFile_.getDepth(5,5));
}

void HydroFileTests::vectorTest() {
    QVector2D vect = hydroFile_.getVector(1,1);
    QCOMPARE(1.1f, vect.x());
    QCOMPARE(1.2f, vect.y());
    vect = hydroFile_.getVector(2,2);
    QCOMPARE(2.1f, vect.x());
    QCOMPARE(2.2f, vect.y());
    vect = hydroFile_.getVector(3,3);
    QCOMPARE(3.1f, vect.x());
    QCOMPARE(3.2f, vect.y());
    vect = hydroFile_.getVector(4,4);
    QCOMPARE(4.1f, vect.x());
    QCOMPARE(4.2f, vect.y());
    vect = hydroFile_.getVector(5,5);
    QCOMPARE(5.1f, vect.x());
    QCOMPARE(5.2f, vect.y());
}

void HydroFileTests::velocityTest() {
    QCOMPARE(1.3, hydroFile_.getFileVelocity(1,1));
    QCOMPARE(2.3, hydroFile_.getFileVelocity(2,2));
    QCOMPARE(3.3, hydroFile_.getFileVelocity(3,3));
    QCOMPARE(4.3, hydroFile_.getFileVelocity(4,4));
    QCOMPARE(5.3, hydroFile_.getFileVelocity(5,5));
}