#include "CarbonSourceCollectionTests.h"

void CarbonSourceCollectionTests::CSCTests()
{
    CarbonSourceCollection coll;
    coll.addSource(0,0,1.0);
    coll.addSource(0,1,2.0);
    coll.addSource(1,0,3.0);
    coll.addSource(1,1,4.0);
    coll.addSource(0,2,1.0);
    coll.addSource(0,2,2.0);
    coll.removeSourcesPercent(0.1);

    QVector<CarbonSource> sources = coll.getSources();

    //Test that correct percentage is removed
    QCOMPARE(sources[0].amount, 0.9f);
    QCOMPARE(sources[1].amount, 1.8f);
    QCOMPARE(sources[2].amount, 2.7f);
    QCOMPARE(sources[3].amount, 3.6f);

    //Test that cells merge properly
    QCOMPARE(sources[4].amount, 2.7f);

}
