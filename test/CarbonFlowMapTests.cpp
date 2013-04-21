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
    int sourcesOffset;
    int sourcesSize;

    HydroFile file("../data/testData/carbonFlowHydroFile.txt");
    CarbonFlowMap carbonMap(&file, 1);
    SourceArrays sourceData = carbonMap.getSourceArrays();


    //Did carbon go from 0,1 to 0,0?
    bool sourceOfAFound = false;
    double totalA = 0.0;
    sourcesOffset = (*sourceData.offsets)(0,0);
    sourcesSize = (*sourceData.sizes)(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            sourceOfAFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalA, 1.0);
    QCOMPARE(sourceOfAFound, true);

    //Did carbon go from 0,0 to 1,0?
    bool sourceOfBFound = false;
    double totalB = 0.0;
    sourcesOffset = (*sourceData.offsets)(1,0);
    sourcesSize = (*sourceData.sizes)(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            sourceOfBFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);
    QCOMPARE(sourceOfBFound, true);

    //Did carbon go from 1,1 to 0,1?
    bool sourceOfCFound = false;
    double totalC = 0.0;
    sourcesOffset = (*sourceData.offsets)(0,1);
    sourcesSize = (*sourceData.sizes)(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            sourceOfCFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);
    QCOMPARE(sourceOfCFound, true);

    //Did carbon go from 1,0 to 1,1?
    bool sourceOfDFound = false;
    double totalD = 0.0;
    sourcesOffset = (*sourceData.offsets)(1,1);
    sourcesSize = (*sourceData.sizes)(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            sourceOfDFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
    QCOMPARE(sourceOfDFound, true);

}

void CarbonFlowMapTests::carbonFlowMapTest2()
{
    HydroFile file("../data/testData/carbonFlowHydroFile2.txt");
    CarbonFlowMap carbonMap(&file, 1);

    SourceArrays sourceData = carbonMap.getSourceArrays();

    int sourcesOffset;
    int sourcesSize;

    //Did carbon go from 0,1 to 0,0?
    bool sourceOfAFound = false;
    double totalA = 0.0;
    sourcesOffset = (*sourceData.offsets)(0,0);
    sourcesSize = (*sourceData.sizes)(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            sourceOfAFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalA, 1.25);
    QCOMPARE(sourceOfAFound, true);

    //Did carbon go from 0,0 to 1,0?
    bool sourceOfBFound = false;
    double totalB = 0.0;
    sourcesOffset = (*sourceData.offsets)(1,0);
    sourcesSize = (*sourceData.sizes)(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            sourceOfBFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 0.25);
        }
    }
    QCOMPARE(totalB, 0.25);
    QCOMPARE(sourceOfBFound, true);

    //Did carbon go from 1,1 to 0,1?
    bool sourceOfCFound = false;
    double totalC = 0.0;
    sourcesOffset = (*sourceData.offsets)(0,1);
    sourcesSize = (*sourceData.sizes)(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            sourceOfCFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.25);
    QCOMPARE(sourceOfCFound, true);

    //Did carbon go from 1,0 to 1,1?
    bool sourceOfDFound = false;
    double totalD = 0.0;
    sourcesOffset = (*sourceData.offsets)(1,1);
    sourcesSize = (*sourceData.sizes)(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            sourceOfDFound = true;
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.25);
    QCOMPARE(sourceOfDFound, true);
}
