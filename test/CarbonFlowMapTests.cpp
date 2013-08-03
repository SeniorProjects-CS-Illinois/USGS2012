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
void CarbonFlowMapTests::testFullFlow()
{
    int sourcesOffset;
    int sourcesSize;

    RiverIOFile riverIO("../data/testData/emptyIOTestData.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile.txt", riverIO);
    CarbonFlowMap carbonMap(&file, 1);
    SourceArrays sourceData = carbonMap.getSourceArrays();


    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalA, 1.0);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);

    //Did carbon go from 1,1 to 0,1?
    double totalC = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
}

void CarbonFlowMapTests::testFullFlow2iter()
{
    int sourcesOffset;
    int sourcesSize;

    RiverIOFile riverIO("../data/testData/emptyIOTestData.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile.txt", riverIO);
    CarbonFlowMap carbonMap(&file,2);
    SourceArrays sourceData = carbonMap.getSourceArrays();


    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalA, 1.0);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);

    double totalC = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
}

void CarbonFlowMapTests::testPartialFlow()
{
    RiverIOFile riverIO("../data/testData/emptyIOTestData.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile2.txt", riverIO);
    CarbonFlowMap carbonMap(&file, 1);

    SourceArrays sourceData = carbonMap.getSourceArrays();

    int sourcesOffset;
    int sourcesSize;

    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 0.25);
        }
    }
    QCOMPARE(totalA, 0.25);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 0.25);
        }
    }
    QCOMPARE(totalB, 1.25);

    //Did carbon go from 1,1 to 0,1?
    double totalC = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 0.25);
        }
    }
    QCOMPARE(totalC, 1.25);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 0.25);
        }
    }
    QCOMPARE(totalD, 1.25);
}

void CarbonFlowMapTests::testPartialFlow2iter()
{
    RiverIOFile riverIO("../data/testData/emptyIOTestData.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile2.txt", riverIO);
    CarbonFlowMap carbonMap(&file, 2);

    SourceArrays sourceData = carbonMap.getSourceArrays();

    int sourcesOffset;
    int sourcesSize;

    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
    }
    QCOMPARE(totalA, 0.0625);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    double totalFromA = 0.0;
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            totalFromA += sourceData.amount[sourcesOffset + i];
        }
    }
    QCOMPARE(totalFromA, 0.3125);
    QCOMPARE(totalB, 1.3125);

    //Did carbon go from 1,1 to 0,1?
    double totalC = 0.0;
    totalFromA = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            totalFromA += sourceData.amount[sourcesOffset + i];
        }
    }
    QCOMPARE(totalFromA, 0.3125);
    QCOMPARE(totalC, 1.3125);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    totalFromA = 0.0;
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            totalFromA += sourceData.amount[sourcesOffset + i];
        }
    }
    QCOMPARE(totalFromA, 0.3125);
    QCOMPARE(totalD, 1.3125);
}


void CarbonFlowMapTests::testLandFlow()
{
    RiverIOFile riverIO("../data/testData/emptyIOTestData.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile3.txt", riverIO);
    CarbonFlowMap carbonMap(&file, 1);

    SourceArrays sourceData = carbonMap.getSourceArrays();

    int sourcesOffset;
    int sourcesSize;

    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalA, 1.0);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);

    //Did carbon go from 1,1 to 0,1?
    double totalC = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
}

void CarbonFlowMapTests::testLandFlow2iter()
{
    RiverIOFile riverIO("../data/testData/ioTestData3.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile3.txt", riverIO);
    CarbonFlowMap carbonMap(&file, 2);

    SourceArrays sourceData = carbonMap.getSourceArrays();

    int sourcesOffset;
    int sourcesSize;

    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalA, 1.0);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);

    //Did carbon go from 1,1 to 0,1?
    double totalC = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
}

void CarbonFlowMapTests::testRiverIO()
{
    int sourcesOffset;
    int sourcesSize;

    RiverIOFile riverIO("../data/testData/ioTestData3.txt");
    HydroFile file("../data/testData/carbonFlowHydroFile.txt", riverIO);
    CarbonFlowMap carbonMap(&file, 1);
    SourceArrays sourceData = carbonMap.getSourceArrays();


    //Did carbon go from 0,1 to 0,0?
    double totalA = 0.0;
    sourcesOffset = sourceData.getOffset(0,0);
    sourcesSize = sourceData.getSize(0,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalA += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
		}
    }
    QCOMPARE(totalA, 2.0);

    //Did carbon go from 0,0 to 1,0?
    double totalB = 0.0;
    sourcesOffset = sourceData.getOffset(1,0);
    sourcesSize = sourceData.getSize(1,0);
    for(int i = 0; i < sourcesSize; i++) {
        totalB += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 0 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalB, 1.0);

    //Did carbon go from 1,1 to 0,1?
    double totalC = 0.0;
    sourcesOffset = sourceData.getOffset(0,1);
    sourcesSize = sourceData.getSize(0,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalC += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 1){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalC, 1.0);

    //Did carbon go from 1,0 to 1,1?
    double totalD = 0.0;
    sourcesOffset = sourceData.getOffset(1,1);
    sourcesSize = sourceData.getSize(1,1);
    for(int i = 0; i < sourcesSize; i++) {
        totalD += sourceData.amount[sourcesOffset + i];
        if(sourceData.x[sourcesOffset + i] == 1 && sourceData.y[sourcesOffset + i] == 0){
            QCOMPARE(sourceData.amount[sourcesOffset + i], 1.0);
        }
    }
    QCOMPARE(totalD, 1.0);
}