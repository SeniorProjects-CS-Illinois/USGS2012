#include <QtTest/QtTest>
#include "grid.h"
#include "reducedgrid.h"
#include "configuration.h"
#include <iostream>

using std::cout;
using std::endl;

class TestClass : public QObject
{
    Q_OBJECT
    private slots:
    void gridTest();
    void reducedGridTest();
    void configTest();
};

void TestClass::gridTest()
{
    Grid<int> intGrid(2,2);
    QCOMPARE(intGrid.getWidth(), (size_t)2);
    QCOMPARE(intGrid.getHeight(), (size_t)2);
    intGrid(0,0) = 1;
    intGrid(0,1) = 2;
    intGrid(1,0) = 3;
    intGrid(1,1) = 4;

    QCOMPARE(intGrid(0,0), 1);
    QCOMPARE(intGrid(0,1), 2);
    QCOMPARE(intGrid(1,0), 3);
    QCOMPARE(intGrid(1,1), 4);
    
    QCOMPARE(intGrid.getArraySize(), (size_t)4);
    QCOMPARE(intGrid(0), 1);
    QCOMPARE(intGrid(1), 2);
    QCOMPARE(intGrid(2), 3);
    QCOMPARE(intGrid(3), 4);

}

void TestClass::reducedGridTest()
{
	qDebug("Creating Reduced grid");
    ReducedGrid<int> grid(2,2);
	qDebug("Checking for a location that shouldn't be there");
    QVERIFY(!grid.locationExists(1,1));
	qDebug("Adding items");
    grid.addItem(1, 0,0);
	grid.addItem(4, 1,1);
    
	qDebug("Compressing");
	grid.compress();
    
    QVERIFY(grid.locationExists(0,0));
    QVERIFY(grid.locationExists(1,1));
    
    QVERIFY(!grid.locationExists(0,1));
    QVERIFY(!grid.locationExists(1,0));

    QCOMPARE(grid.get(0), 1);
    QCOMPARE(grid.get(1), 4);

    QCOMPARE(grid.get(0,0), 1);
    QCOMPARE(grid.get(1,1), 4);
}

void TestClass::configTest()
{
    qDebug("Setup first config");
    Configuration config;
    config.adjacent = false;
//    config.numStocks = 1;
    config.numHydroMaps = 2;
    config.hydroMaps.append("10k.txt");
    config.hydroMaps.append("20k.txt");
	config.daysToRun.append(10);
    config.daysToRun.append(20);
    config.outputFreq = 3;
    config.timestep = 4;
    config.tss = 4.0;
    config.kPhyto = 5.0;
    config.kMacro = 6.0;
//    config.whichStock = "Poc";
    config.macro = 7.0;
    config.phyto = 9.0;
    config.consumer = 10.0;
    config.decomp = 11.0;
    config.sedconsumer = 12.0;
    config.seddecomp = 13.0;
    config.herbivore = 14.0;
    config.detritus = 15.0;
    config.poc = 16.0;
    config.doc = 17.0;
    config.phytoSenescence = 18.0;
    config.phytoRespiration = 19.0;
    config.phytoExcretion = 20.0;
    config.phytoAj = 21.0;
    config.phytoGj = 22.0;
    config.herbivoreAiPhyto = 23.0;
    config.herbivoreGiPhyto = 24.0;
    config.herbivorePrefPhyto = 25.0;
    config.herbivoreAiPeri = 26.0;
    config.herbivoreGiPeri = 27.0;
    config.herbivorePrefPeri = 28.0;
    config.herbivoreAiWaterdecomp = 29.0;
    config.herbivoreGiWaterdecomp = 30.0;
    config.herbivorePrefWaterdecomp = 31.0;
    config.herbivoreAj = 32.0;
    config.herbivoreGj = 33.0;
    config.herbivoreRespiration = 34.0;
    config.herbivoreExcretion = 35.0;
    config.herbivoreEgestion = 36.0;
    config.herbivoreSenescence = 37.0;
    config.herbivoreMax = 38.0;
    config.waterdecompAiDoc = 39.0;
    config.waterdecompGiDoc = 40.0;
    config.waterdecompPrefDoc = 41.0;
    config.waterdecompAiPoc = 42.0;
    config.waterdecompGiPoc = 43.0;
    config.waterdecompPrefPoc = 44.0;
    config.waterdecompAj = 45.0;
    config.waterdecompGj = 46.0;
    config.waterdecompRespiration = 47.0;
    config.waterdecompExcretion = 48.0;
    config.waterdecompSenescence = 49.0;
    config.waterdecompMax = 50.0;
    config.seddecompAiDetritus = 51.0;
    config.seddecompGiDetritus = 52.0;
    config.seddecompPrefDetritus = 53.0;
    config.seddecompAj = 53.0;
    config.seddecompGj = 54.0;
    config.seddecompRespiration = 55.0;
    config.seddecompExcretion = 56.0;
    config.seddecompSenescence = 57.0;
    config.seddecompMax = 58.0;
    config.consumerAiHerbivore = 59.0;
    config.consumerGiHerbivore = 60.0;
    config.consumerPrefHerbivore = 61.0;
    config.consumerAiSedconsumer = 62.0;
    config.consumerGiSedconsumer = 63.0;
    config.consumerPrefSedconsumer = 64.0;
    config.consumerAj = 65.0;
    config.consumerGj = 66.0;
    config.consumerRespiration = 67.0;
    config.consumerExcretion = 68.0;
    config.consumerSenescence = 69.0;
    config.consumerEgestion = 70.0;
    config.consumerMax = 71.0;
    config.macroSenescence = 72.0;
    config.macroRespiration = 73.0;
    config.macroExcretion = 74.0;
    config.macroTemp = 75.0;
    config.macroGross = 76.0;
    config.macroMassMax = 77.0;
    config.macroVelocityMax = 78.0;
    config.sedconsumerAiDetritus = 79.0;
    config.sedconsumerGiDetritus = 80.0;
    config.sedconsumerPrefDetritus = 81.0;
    config.sedconsumerAiSeddecomp = 82.0;
    config.sedconsumerGiSeddecomp = 83.0;
    config.sedconsumerPrefSeddecomp = 84.0;
    config.sedconsumerAiPeri = 85.0;
    config.sedconsumerGiPeri = 86.0;
    config.sedconsumerPrefPeri = 87.0;
    config.sedconsumerEgestionSeddecomp = 88.0;
    config.sedconsumerEgestionDetritus = 89.0;
    config.sedconsumerAj = 90.0;
    config.sedconsumerGj = 91.0;
    config.sedconsumerRespiration = 92.0;
    config.sedconsumerExcretion = 93.0;
    config.sedconsumerSenescence = 94.0;
    config.sedconsumerMax = 95.0;
    config.periAj = 96.0;
    config.periGj = 97.0;

    qDebug("First config write");
    config.write("testconfig.txt");

    Configuration config2;
    qDebug("Load config");
    config2.read("testconfig.txt");
    QCOMPARE(config2.adjacent, false);
//    QCOMPARE(config2.numStocks, 1);

    QCOMPARE(config2.numHydroMaps, (uint16_t)2);
    QCOMPARE(config2.hydroMaps.size(), 2);
    QCOMPARE(config2.hydroMaps[0], QString("10k.txt"));
	QCOMPARE(config2.hydroMaps[1], QString("20k.txt"));
    QCOMPARE(config2.daysToRun.size(), 2);
    QCOMPARE(config2.daysToRun[0], (uint16_t)10);
	QCOMPARE(config2.daysToRun[1], (uint16_t)20);

    QCOMPARE(config2.outputFreq, (uint8_t)3);
    QCOMPARE(config2.timestep, (uint8_t)4);
    QCOMPARE(config2.tss, 4.0);
    QCOMPARE(config2.kPhyto, 5.0);
    QCOMPARE(config2.kMacro, 6.0);
//    QCOMPARE(config2.whichStock, "Poc");
    QCOMPARE(config2.macro, 7.0);
    QCOMPARE(config2.phyto, 9.0);
    QCOMPARE(config2.consumer, 10.0);
    QCOMPARE(config2.decomp, 11.0);
    QCOMPARE(config2.sedconsumer, 12.0);
    QCOMPARE(config2.seddecomp, 13.0);
    QCOMPARE(config2.herbivore, 14.0);
    QCOMPARE(config2.detritus, 15.0);
    QCOMPARE(config2.poc, 16.0);
    QCOMPARE(config2.doc, 17.0);
    QCOMPARE(config2.phytoSenescence, 18.0);
    QCOMPARE(config2.phytoRespiration, 19.0);
    QCOMPARE(config2.phytoExcretion, 20.0);
    QCOMPARE(config2.phytoAj, 21.0);
    QCOMPARE(config2.phytoGj, 22.0);
    QCOMPARE(config2.herbivoreAiPhyto, 23.0);
    QCOMPARE(config2.herbivoreGiPhyto, 24.0);
    QCOMPARE(config2.herbivorePrefPhyto, 25.0);
    QCOMPARE(config2.herbivoreAiPeri, 26.0);
    QCOMPARE(config2.herbivoreGiPeri, 27.0);
    QCOMPARE(config2.herbivorePrefPeri, 28.0);
    QCOMPARE(config2.herbivoreAiWaterdecomp, 29.0);
    QCOMPARE(config2.herbivoreGiWaterdecomp, 30.0);
    QCOMPARE(config2.herbivorePrefWaterdecomp, 31.0);
    QCOMPARE(config2.herbivoreAj, 32.0);
    QCOMPARE(config2.herbivoreGj, 33.0);
    QCOMPARE(config2.herbivoreRespiration, 34.0);
    QCOMPARE(config2.herbivoreExcretion, 35.0);
    QCOMPARE(config2.herbivoreEgestion, 36.0);
    QCOMPARE(config2.herbivoreSenescence, 37.0);
    QCOMPARE(config2.herbivoreMax, 38.0);
    QCOMPARE(config2.waterdecompAiDoc, 39.0);
    QCOMPARE(config2.waterdecompGiDoc, 40.0);
    QCOMPARE(config2.waterdecompPrefDoc, 41.0);
    QCOMPARE(config2.waterdecompAiPoc, 42.0);
    QCOMPARE(config2.waterdecompGiPoc, 43.0);
    QCOMPARE(config2.waterdecompPrefPoc, 44.0);
    QCOMPARE(config2.waterdecompAj, 45.0);
    QCOMPARE(config2.waterdecompGj, 46.0);
    QCOMPARE(config2.waterdecompRespiration, 47.0);
    QCOMPARE(config2.waterdecompExcretion, 48.0);
    QCOMPARE(config2.waterdecompSenescence, 49.0);
    QCOMPARE(config2.waterdecompMax, 50.0);
    QCOMPARE(config2.seddecompAiDetritus, 51.0);
    QCOMPARE(config2.seddecompGiDetritus, 52.0);
    QCOMPARE(config2.seddecompPrefDetritus, 53.0);
    QCOMPARE(config2.seddecompAj, 53.0);
    QCOMPARE(config2.seddecompGj, 54.0);
    QCOMPARE(config2.seddecompRespiration, 55.0);
    QCOMPARE(config2.seddecompExcretion, 56.0);
    QCOMPARE(config2.seddecompSenescence, 57.0);
    QCOMPARE(config2.seddecompMax, 58.0);
    QCOMPARE(config2.consumerAiHerbivore, 59.0);
    QCOMPARE(config2.consumerGiHerbivore, 60.0);
    QCOMPARE(config2.consumerPrefHerbivore, 61.0);
    QCOMPARE(config2.consumerAiSedconsumer, 62.0);
    QCOMPARE(config2.consumerGiSedconsumer, 63.0);
    QCOMPARE(config2.consumerPrefSedconsumer, 64.0);
    QCOMPARE(config2.consumerAj, 65.0);
    QCOMPARE(config2.consumerGj, 66.0);
    QCOMPARE(config2.consumerRespiration, 67.0);
    QCOMPARE(config2.consumerExcretion, 68.0);
    QCOMPARE(config2.consumerSenescence, 69.0);
    QCOMPARE(config2.consumerEgestion, 70.0);
    QCOMPARE(config2.consumerMax, 71.0);
    QCOMPARE(config2.macroSenescence, 72.0);
    QCOMPARE(config2.macroRespiration, 73.0);
    QCOMPARE(config2.macroExcretion, 74.0);
    QCOMPARE(config2.macroTemp, 75.0);
    QCOMPARE(config2.macroGross, 76.0);
    QCOMPARE(config2.macroMassMax, 77.0);
    QCOMPARE(config2.macroVelocityMax, 78.0);
    QCOMPARE(config2.sedconsumerAiDetritus, 79.0);
    QCOMPARE(config2.sedconsumerGiDetritus, 80.0);
    QCOMPARE(config2.sedconsumerPrefDetritus, 81.0);
    QCOMPARE(config2.sedconsumerAiSeddecomp, 82.0);
    QCOMPARE(config2.sedconsumerGiSeddecomp, 83.0);
    QCOMPARE(config2.sedconsumerPrefSeddecomp, 84.0);
    QCOMPARE(config2.sedconsumerAiPeri, 85.0);
    QCOMPARE(config2.sedconsumerGiPeri, 86.0);
    QCOMPARE(config2.sedconsumerPrefPeri, 87.0);
    QCOMPARE(config2.sedconsumerEgestionSeddecomp, 88.0);
    QCOMPARE(config2.sedconsumerEgestionDetritus, 89.0);
    QCOMPARE(config2.sedconsumerAj, 90.0);
    QCOMPARE(config2.sedconsumerGj, 91.0);
    QCOMPARE(config2.sedconsumerRespiration, 92.0);
    QCOMPARE(config2.sedconsumerExcretion, 93.0);
    QCOMPARE(config2.sedconsumerSenescence, 94.0);
    QCOMPARE(config2.sedconsumerMax, 95.0);
    QCOMPARE(config2.periAj, 96.0);
    QCOMPARE(config2.periGj, 97.0);
}

QTEST_MAIN(TestClass)
#include "TestClass.moc"
