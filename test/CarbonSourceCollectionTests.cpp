#include "CarbonSourceCollectionTests.h"

void CarbonSourceCollectionTests::CSCTests()
{
    CarbonSourceCollection coll;
    coll.addSource(0,0,1.0);
    coll.addSource(0,1,2.0);
	coll.addSource(1,0,3.0);
    coll.addSource(1,1,4.0);
    coll.removeSourcesPercent(0.1);


    QVector<CarbonSource> sources = coll.getSources();

	QCOMPARE(sources[0].ammount, 0.9f);
	QCOMPARE(sources[1].ammount, 1.8f);
	QCOMPARE(sources[2].ammount, 2.7f);
	QCOMPARE(sources[3].ammount, 3.6f);

}