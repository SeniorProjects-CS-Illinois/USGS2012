#include <iostream>
#include "CarbonFlowMapTests.h"
#include "carbonsources.h"
#include "carbonflowmap.h"

using std::cout;
using std::endl;

/**
 *  _______
 * |   |   |   
 * | C | D |
 * |___|___|
 * |   |   |  
 * | A | B |
 * |___|___|
 * 
 */
void CarbonFlowMapTests::carbonFlowMapTest()
{
    HydroFile file("../data/testData/carbonFlowHydroFile.txt");
    CarbonFlowMap carbonMap(&file, 1);
    CarbonSourceCollection sourceA = carbonMap.getPatchSources(0,0);
    CarbonSourceCollection sourceB = carbonMap.getPatchSources(1,0);
    CarbonSourceCollection sourceC = carbonMap.getPatchSources(0,1);
    CarbonSourceCollection sourceD = carbonMap.getPatchSources(1,1);

    const QVector<CarbonSource> * sourcesFromA = sourceA.getSources();
    const QVector<CarbonSource> * sourcesFromB = sourceB.getSources();
    const QVector<CarbonSource> * sourcesFromC = sourceC.getSources();
    const QVector<CarbonSource> * sourcesFromD = sourceD.getSources();

    bool sourceOfAFound = false;
    double totalA = 0.0;
    for(int i = 0; i < (*sourcesFromA).size(); i++) {
        totalA += (*sourcesFromA)[i].amount;
        if((*sourcesFromA)[i].x == 0 && (*sourcesFromA)[i].y == 1){
            sourceOfAFound = true;
            QCOMPARE((*sourcesFromA)[i].amount, 1.0);
        }
    }
    QCOMPARE(totalA, 1.0);
    QCOMPARE(sourceOfAFound, true);

    bool sourceOfBFound = false;
    double totalB = 0.0;
    for(int i = 0; i < (*sourcesFromB).size(); i++) {
        totalB += (*sourcesFromB)[i].amount;
        if((*sourcesFromB)[i].x == 0 && (*sourcesFromB)[i].y == 0){
            sourceOfBFound = true;
            QCOMPARE((*sourcesFromB)[i].amount, 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);
    QCOMPARE(sourceOfBFound, true);

    bool sourceOfCFound = false;
    double totalC = 0.0;
    for(int i = 0; i < (*sourcesFromC).size(); i++) {
        totalC += (*sourcesFromC)[i].amount;
        if((*sourcesFromC)[i].x == 1 && (*sourcesFromC)[i].y == 1){
            sourceOfCFound = true;
            QCOMPARE((*sourcesFromC)[i].amount, 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);
    QCOMPARE(sourceOfCFound, true);

    bool sourceOfDFound = false;
    double totalD = 0.0;
    for(int i = 0; i < (*sourcesFromD).size(); i++) {
        totalD += (*sourcesFromD)[i].amount;
        if((*sourcesFromD)[i].x == 1 && (*sourcesFromD)[i].y == 0){
            sourceOfDFound = true;
            QCOMPARE((*sourcesFromD)[i].amount, 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
    QCOMPARE(sourceOfDFound, true);
}
