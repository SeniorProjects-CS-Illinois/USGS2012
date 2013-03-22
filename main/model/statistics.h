#ifndef STATISTICS_H
#define STATISTICS_H

struct Statistics {
    //Totals over entire map
    double totalMacro;
    double totalPhyto;
    double totalHerbivore;
    double totalWaterDecomp;
    double totalSedDecomp;
    double totalSedConsumer;
    double totalConsum;
    double totalDOC;
    double totalPOC;
    double totalDetritus;
    double totalCarbon;

    //Averages over entire map
    double avgMacro;
    double avgPhyto;
    double avgHerbivore;
    double avgWaterDecomp;
    double avgSedDecomp;
    double avgSedConsumer;
    double avgConsum;
    double avgDOC;
    double avgPOC;
    double avgDetritus;
    double avgCarbon;

    //Max of all patches
    double maxMacro;
    double maxPhyto;
    double maxHerbivore;
    double maxWaterDecomp;
    double maxSedDecomp;
    double maxSedConsumer;
    double maxConsum;
    double maxDOC;
    double maxPOC;
    double maxDetritus;
    double maxCarbon;

    int waterPatches;

    //Constructor that initializes all values to 0.
    Statistics() :
        totalMacro(0.0), totalPhyto(0.0), totalHerbivore(0.0), totalWaterDecomp(0.0),
        totalSedDecomp(0.0), totalSedConsumer(0.0), totalConsum(0.0), totalDOC(0.0),
        totalPOC(0.0), totalDetritus(0.0), totalCarbon(0.0),

        avgMacro(0.0), avgPhyto(0.0), avgHerbivore(0.0), avgWaterDecomp(0.0),
        avgSedDecomp(0.0), avgSedConsumer(0.0), avgConsum(0.0), avgDOC(0.0),
        avgPOC(0.0), avgDetritus(0.0), avgCarbon(0.0),

        maxMacro(0.0), maxPhyto(0.0), maxHerbivore(0.0), maxWaterDecomp(0.0),
        maxSedDecomp(0.0), maxSedConsumer(0.0), maxConsum(0.0), maxDOC(0.0),
        maxPOC(0.0), maxDetritus(0.0), maxCarbon(0.0),

        waterPatches(0) {}
};

#endif // STATISTICS_H
