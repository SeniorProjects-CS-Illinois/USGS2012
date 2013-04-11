#include "CarbonFlowMapTests.h"
#include "carbonsources.h"
#include "carbonflowmap.h"

/**
 *  _______
 * |   |   |   
 * | A | B |
 * |___|___|
 * |   |   |  
 * | C | D |
 * |___|___|
 * 
 */
void CarbonFlowMapTests::carbonFlowMapTest()
{
    HydroFile file("../data/testData/carbonFlowHydroFile.txt");
    CarbonFlowMap carbonMap(&file, 1);
    CarbonSourceCollection sourceA = carbonMap.getPatchSources(0,0);
    CarbonSourceCollection sourceB = carbonMap.getPatchSources(1,0);
    CarbonSourceCollection sourceC = carbonMap.getPatchSources(1,1);
    CarbonSourceCollection sourceD = carbonMap.getPatchSources(0,1);

    QVector<CarbonSource> sourcesFromA = sourceA.getSources();
    QVector<CarbonSource> sourcesFromB = sourceB.getSources();
    QVector<CarbonSource> sourcesFromC = sourceC.getSources();
    QVector<CarbonSource> sourcesFromD = sourceD.getSources();

    QCOMPARE(sourcesFromA.size(), 1);
    QCOMPARE(sourcesFromA[0].amount, 1.0);
	QCOMPARE(sourcesFromA[0].x, 0);
    QCOMPARE(sourcesFromA[0].y, 1);

    QCOMPARE(sourcesFromB.size(), 1);
    QCOMPARE(sourcesFromB[0].amount, 1.0);
	QCOMPARE(sourcesFromB[0].x, 0);
    QCOMPARE(sourcesFromB[0].y, 0);
   
    QCOMPARE(sourcesFromC.size(), 1);
    QCOMPARE(sourcesFromC[0].amount, 1.0);
	QCOMPARE(sourcesFromC[0].x, 1);
    QCOMPARE(sourcesFromC[0].y, 0);

    QCOMPARE(sourcesFromD.size(), 1);
    QCOMPARE(sourcesFromD[0].amount, 1.0);
	QCOMPARE(sourcesFromD[0].x, 1);
    QCOMPARE(sourcesFromD[0].y, 1);
}
