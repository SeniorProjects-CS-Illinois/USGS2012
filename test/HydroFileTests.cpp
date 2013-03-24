#include "HydroFileTests.h"

void HydroFileTests::hydroFileTest()
{
    HydroFile hydroFile("../data/testData/testHydroFile.txt");
    QCOMPARE(hydroFile.getMapHeight(), 6);
    QCOMPARE(hydroFile.getMapWidth(), 6);
    QVERIFY(hydroFile.patchExists(1,1));
    QVERIFY(hydroFile.patchExists(2,2));
    QVERIFY(hydroFile.patchExists(3,3));
    QVERIFY(hydroFile.patchExists(4,4));
    QVERIFY(hydroFile.patchExists(5,5));

    QVERIFY(!hydroFile.patchExists(6,6));
    QVERIFY(!hydroFile.patchExists(0,0));

    QCOMPARE(1.0, hydroFile.getDepth(1,1));
    QCOMPARE(2.0, hydroFile.getDepth(2,2));
    QCOMPARE(3.0, hydroFile.getDepth(3,3));
    QCOMPARE(4.0, hydroFile.getDepth(4,4));
    QCOMPARE(5.0, hydroFile.getDepth(5,5));

    QVector2D vect = hydroFile.getVector(1,1);
    QCOMPARE(1.1f, vect.x());
    QCOMPARE(1.2f, vect.y());
    vect = hydroFile.getVector(2,2);
    QCOMPARE(2.1f, vect.x());
    QCOMPARE(2.2f, vect.y());
    vect = hydroFile.getVector(3,3);
    QCOMPARE(3.1f, vect.x());
    QCOMPARE(3.2f, vect.y());
    vect = hydroFile.getVector(4,4);
    QCOMPARE(4.1f, vect.x());
    QCOMPARE(4.2f, vect.y());
    vect = hydroFile.getVector(5,5);
    QCOMPARE(5.1f, vect.x());
    QCOMPARE(5.2f, vect.y());

    QCOMPARE(1.3, hydroFile.getFileVelocity(1,1));
    QCOMPARE(2.3, hydroFile.getFileVelocity(2,2));
    QCOMPARE(3.3, hydroFile.getFileVelocity(3,3));
    QCOMPARE(4.3, hydroFile.getFileVelocity(4,4));
    QCOMPARE(5.3, hydroFile.getFileVelocity(5,5));
    
}