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
    QVERIFY(intGrid.getWidth() == 2);
    QVERIFY(intGrid.getHeight() == 2);
    intGrid(0,0) = 1;
    intGrid(0,1) = 2;
    intGrid(1,0) = 3;
    intGrid(1,1) = 4;

    QVERIFY(intGrid(0,0) == 1);
    QVERIFY(intGrid(0,1) == 2);
    QVERIFY(intGrid(1,0) == 3);
    QVERIFY(intGrid(1,1) == 4);
    
    QVERIFY(intGrid.getArraySize() == 4);
    QVERIFY(intGrid(0) == 1);
    QVERIFY(intGrid(1) == 2);
    QVERIFY(intGrid(2) == 3);
    QVERIFY(intGrid(3) == 4);

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

    QVERIFY(1 == grid.get(0));
    QVERIFY(4 == grid.get(1));

    QVERIFY(1 == grid.get(0,0));
    QVERIFY(4 == grid.get(1,1));
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
    QVERIFY(config2.adjacent == false);
//    QVERIFY(config2.numStocks == 1);

    QVERIFY(config2.numHydroMaps == 2);
    QVERIFY(config2.hydroMaps.size() == 2);
    QVERIFY(config2.hydroMaps[0].compare("10k.txt") == 0);
	QVERIFY(config2.hydroMaps[1].compare("20k.txt") == 0);
    QVERIFY(config2.daysToRun.size() == 2);
    QVERIFY(config2.daysToRun[0] == 10);
	QVERIFY(config2.daysToRun[1] == 20);

    QVERIFY(config2.outputFreq == 3);
    QVERIFY(config2.timestep == 4);
    QVERIFY(config2.tss == 4.0);
    QVERIFY(config2.kPhyto == 5.0);
    QVERIFY(config2.kMacro == 6.0);
//    QVERIFY(config2.whichStock == "Poc");
    QVERIFY(config2.macro == 7.0);
    QVERIFY(config2.phyto == 9.0);
    QVERIFY(config2.consumer == 10.0);
    QVERIFY(config2.decomp == 11.0);
    QVERIFY(config2.sedconsumer == 12.0);
    QVERIFY(config2.seddecomp == 13.0);
    QVERIFY(config2.herbivore == 14.0);
    QVERIFY(config2.detritus == 15.0);
    QVERIFY(config2.poc == 16.0);
    QVERIFY(config2.doc == 17.0);
    QVERIFY(config2.phytoSenescence == 18.0);
    QVERIFY(config2.phytoRespiration == 19.0);
    QVERIFY(config2.phytoExcretion == 20.0);
    QVERIFY(config2.phytoAj == 21.0);
    QVERIFY(config2.phytoGj == 22.0);
    QVERIFY(config2.herbivoreAiPhyto == 23.0);
    QVERIFY(config2.herbivoreGiPhyto == 24.0);
    QVERIFY(config2.herbivorePrefPhyto == 25.0);
    QVERIFY(config2.herbivoreAiPeri == 26.0);
    QVERIFY(config2.herbivoreGiPeri == 27.0);
    QVERIFY(config2.herbivorePrefPeri == 28.0);
    QVERIFY(config2.herbivoreAiWaterdecomp == 29.0);
    QVERIFY(config2.herbivoreGiWaterdecomp == 30.0);
    QVERIFY(config2.herbivorePrefWaterdecomp == 31.0);
    QVERIFY(config2.herbivoreAj == 32.0);
    QVERIFY(config2.herbivoreGj == 33.0);
    QVERIFY(config2.herbivoreRespiration == 34.0);
    QVERIFY(config2.herbivoreExcretion == 35.0);
    QVERIFY(config2.herbivoreEgestion == 36.0);
    QVERIFY(config2.herbivoreSenescence == 37.0);
    QVERIFY(config2.herbivoreMax == 38.0);
    QVERIFY(config2.waterdecompAiDoc == 39.0);
    QVERIFY(config2.waterdecompGiDoc == 40.0);
    QVERIFY(config2.waterdecompPrefDoc == 41.0);
    QVERIFY(config2.waterdecompAiPoc == 42.0);
    QVERIFY(config2.waterdecompGiPoc == 43.0);
    QVERIFY(config2.waterdecompPrefPoc == 44.0);
    QVERIFY(config2.waterdecompAj == 45.0);
    QVERIFY(config2.waterdecompGj == 46.0);
    QVERIFY(config2.waterdecompRespiration == 47.0);
    QVERIFY(config2.waterdecompExcretion == 48.0);
    QVERIFY(config2.waterdecompSenescence == 49.0);
    QVERIFY(config2.waterdecompMax == 50.0);
    QVERIFY(config2.seddecompAiDetritus == 51.0);
    QVERIFY(config2.seddecompGiDetritus == 52.0);
    QVERIFY(config2.seddecompPrefDetritus == 53.0);
    QVERIFY(config2.seddecompAj == 53.0);
    QVERIFY(config2.seddecompGj == 54.0);
    QVERIFY(config2.seddecompRespiration == 55.0);
    QVERIFY(config2.seddecompExcretion == 56.0);
    QVERIFY(config2.seddecompSenescence == 57.0);
    QVERIFY(config2.seddecompMax == 58.0);
    QVERIFY(config2.consumerAiHerbivore == 59.0);
    QVERIFY(config2.consumerGiHerbivore == 60.0);
    QVERIFY(config2.consumerPrefHerbivore == 61.0);
    QVERIFY(config2.consumerAiSedconsumer == 62.0);
    QVERIFY(config2.consumerGiSedconsumer == 63.0);
    QVERIFY(config2.consumerPrefSedconsumer == 64.0);
    QVERIFY(config2.consumerAj == 65.0);
    QVERIFY(config2.consumerGj == 66.0);
    QVERIFY(config2.consumerRespiration == 67.0);
    QVERIFY(config2.consumerExcretion == 68.0);
    QVERIFY(config2.consumerSenescence == 69.0);
    QVERIFY(config2.consumerEgestion == 70.0);
    QVERIFY(config2.consumerMax == 71.0);
    QVERIFY(config2.macroSenescence == 72.0);
    QVERIFY(config2.macroRespiration == 73.0);
    QVERIFY(config2.macroExcretion == 74.0);
    QVERIFY(config2.macroTemp == 75.0);
    QVERIFY(config2.macroGross == 76.0);
    QVERIFY(config2.macroMassMax == 77.0);
    QVERIFY(config2.macroVelocityMax == 78.0);
    QVERIFY(config2.sedconsumerAiDetritus == 79.0);
    QVERIFY(config2.sedconsumerGiDetritus == 80.0);
    QVERIFY(config2.sedconsumerPrefDetritus == 81.0);
    QVERIFY(config2.sedconsumerAiSeddecomp == 82.0);
    QVERIFY(config2.sedconsumerGiSeddecomp == 83.0);
    QVERIFY(config2.sedconsumerPrefSeddecomp == 84.0);
    QVERIFY(config2.sedconsumerAiPeri == 85.0);
    QVERIFY(config2.sedconsumerGiPeri == 86.0);
    QVERIFY(config2.sedconsumerPrefPeri == 87.0);
    QVERIFY(config2.sedconsumerEgestionSeddecomp == 88.0);
    QVERIFY(config2.sedconsumerEgestionDetritus == 89.0);
    QVERIFY(config2.sedconsumerAj == 90.0);
    QVERIFY(config2.sedconsumerGj == 91.0);
    QVERIFY(config2.sedconsumerRespiration == 92.0);
    QVERIFY(config2.sedconsumerExcretion == 93.0);
    QVERIFY(config2.sedconsumerSenescence == 94.0);
    QVERIFY(config2.sedconsumerMax == 95.0);
    QVERIFY(config2.periAj == 96.0);
    QVERIFY(config2.periGj == 97.0);
}

QTEST_MAIN(TestClass)
#include "TestClass.moc"
