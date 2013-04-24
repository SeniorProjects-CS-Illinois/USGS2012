#include "river.h"

River::River(Configuration & newConfig, HydroFileDict & hydroFileDict)
    : p(newConfig,hydroFileDict)
{
    growthRates << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0.07725 << 0.07725 << 0.07725 << 0.17 << 0.17 << 0.24 << 0.24 << 0.24 << 0.24 << 0.45 << 0.45 << 0.45 << 0.45
        << 0.67 << 0.67 << 0.67 << 0.67 << 0.81 << 0.81 << 0.81 << 0.81 << 1.0 << 1.0 << 1.0 << 1.0 << 0.89 << 0.89 << 0.84 << 0.84 << 0.78 << 0.78 << 0.73 << 0.73
        << 0.68;

    config = newConfig;

    currHydroData = NULL;
    currWaterTemp = -1.0;
    currPAR = -1;

    width = hydroFileDict.getMaxWidth();
    height = hydroFileDict.getMaxHeight();

}

//TODO This function is relatively slow because of many hashtable lookups
// in HydroFile class.  Consider pros and cons of using a grid instead.
void River::setCurrentHydroData(HydroData *newHydroData) {
    HydroFile * newHydroFile = &newHydroData->hydroFile;
    HydroFile * currHydroFile = NULL;
    if(currHydroData != NULL) {
        currHydroFile = &currHydroData->hydroFile;
    }

    for (int i = 0; i < p.getSize(); i++ ) {
        int x = p.pxcor[i];
        int y = p.pycor[i];

        if(newHydroFile->patchExists(x,y)){
            double depth = newHydroFile->getDepth(x,y);
            QVector2D flowVector = newHydroFile->getVector(x,y);
            double flowX = flowVector.x();
            double flowY = flowVector.y();

            //TODO Replace this line with flowVector.length() once we know if it is correct to do so.
            double flowMagnitude = newHydroFile->getFileVelocity(x,y);

            p.hasWater[i] = true;
            p.depth[i] = depth;
            p.flowX[i] = flowX;
            p.flowY[i] = flowY;
            p.flowMagnitude[i] = flowMagnitude;

        } else {
            p.hasWater[i] = false;
            p.depth[i] = 0.0;
            p.flowX[i] = 0.0;
            p.flowY[i] = 0.0;
            p.flowMagnitude[i] = 0.0;
        }

        // update miscellanous variables inside the patch

        double current_depth = 0.0;
        if(currHydroFile != NULL && currHydroFile->patchExists(x,y)){
            current_depth = currHydroFile->getDepth(x,y);
        }

        // Water -> Land
        if (current_depth > 0.0 && p.depth[i] == 0.0) {
            p.detritus[i] += p.DOC[i] + p.POC[i] + p.phyto[i] +
                    p.macro[i] + p.waterdecomp[i] +
                    p.seddecomp[i] + p.herbivore[i] + p.sedconsumer[i] + p.consumer[i];

            p.DOC[i] = 0.0;
            p.POC[i] = 0.0;
            p.phyto[i] = 0.0;
            p.macro[i] = 0.0;
            p.waterdecomp[i] = 0.0;
            p.seddecomp[i] = 0.0;
            p.herbivore[i] = 0.0;
            p.sedconsumer[i] = 0.0;
            p.consumer[i] = 0.0;
        }

        //TODO: Instead of handling this here, process detritus daily in land patches
        //    via processPatches and with a potentially diff percentage.
        // Land -> Water
        if (currHydroFile != NULL && current_depth == 0.0 && p.depth[i] > 0.0) {
            p.detritus[i] *= 0.5;
        }
    }

    currHydroData = newHydroData;
}

void River::setCurrentWaterTemperature(double newTemp) {

    currWaterTemp = newTemp;

    currGrowthRate = River::getNewGrowthRate(currWaterTemp);
}

void River::setCurrentPAR(int newPAR) {
    currPAR = newPAR;
}

int River::getNewGrowthRate(int temp) {
    if(temp < 0) {
        return 0;
    } else if (temp >= growthRates.length()) {
        return 0.68;
    }
    return growthRates[temp];
}

void River::flow(Grid<FlowData> * source, Grid<FlowData> * dest) {
    copyFlowData(*dest);
    copyFlowData(*source);

    for (int t = 0; t < ITERATIONS_TO_FLOW_RIVER; t++)
    {
        std::swap(source, dest);
        flowSingleTimestep(*source, *dest, config);
    }

    storeFlowData(*dest);
}

void River::copyFlowData(Grid<FlowData> & flowData) {
    for(int i = 0; i < p.getSize(); i++) {
        int x = p.pxcor[i];
        int y = p.pycor[i];

        flowData(x,y).hasWater    = p.hasWater[i];
        flowData(x,y).depth       = p.depth[i];
        flowData(x,y).velocity    = p.flowMagnitude[i];
        flowData(x,y).px_vector   = p.flowX[i];
        flowData(x,y).py_vector   = p.flowY[i];
        flowData(x,y).DOC         = p.DOC[i];
        flowData(x,y).POC         = p.POC[i];
        flowData(x,y).phyto       = p.phyto[i];
        flowData(x,y).waterdecomp = p.waterdecomp[i];

    }
}

void River::storeFlowData(Grid<FlowData> & flowData) {
    for(int i = 0; i < p.getSize(); i++) {
        int x = p.pxcor[i];
        int y = p.pycor[i];

        p.DOC[i]         = flowData(x,y).DOC;
        p.POC[i]         = flowData(x,y).POC;
        p.phyto[i]       = flowData(x,y).phyto;
        p.waterdecomp[i] = flowData(x,y).waterdecomp;
    }
}

void River::flowSingleTimestep(Grid<FlowData> &source, Grid<FlowData> &dest, Configuration &config) {
    CarbonFlowMap * carbonFlowMap = &currHydroData->carbonFlowMap;

    SourceArrays sourceData = carbonFlowMap->getSourceArrays();
    #pragma omp parallel for
    for(int i = 0; i < p.getSize(); i++) {
        if( !p.hasWater[i] ) {
            continue;
        }

        int x = p.pxcor[i];
        int y = p.pycor[i];

        double DOC = 0.0;
        double POC = 0.0;
        double waterdecomp = 0.0;
        double phyto = 0.0;


        int currOffset = sourceData.getOffset(x,y);
        int numSources = sourceData.getSize(x,y);
        for(int sourceIndex = 0; sourceIndex < numSources; sourceIndex++) {
            int sourceX = sourceData.x[currOffset + sourceIndex];
            int sourceY = sourceData.y[currOffset + sourceIndex];
            double sourceAmount = sourceData.amount[currOffset + sourceIndex];

            DOC += source(sourceX,sourceY).DOC * sourceAmount;
            POC += source(sourceX,sourceY).POC * sourceAmount;
            waterdecomp += source(sourceX,sourceY).waterdecomp * sourceAmount;
            phyto += source(sourceX,sourceY).phyto * sourceAmount;
        }

        dest(x,y).DOC = DOC;
        dest(x,y).POC = POC;
        dest(x,y).waterdecomp = waterdecomp;
        dest(x,y).phyto = phyto;
    }
}

bool River::is_valid_patch(int x, int y) {
    if (x <0 || y < 0) return false;
    if (x >= width || y >= height) return false;
    return true;
}

Statistics River::generateStatistics() {
    Statistics stats;

    for(int i = 0; i < p.getSize(); i++) {
        if(!p.hasWater[i]) {
            continue;
        }

        stats.waterPatches++;

        double carbon = 0.0;

        //Macro
        carbon += p.macro[i];
        stats.totalMacro += p.macro[i];
        stats.maxMacro = max(stats.maxMacro, p.macro[i]);

        //Phyto
        carbon += p.phyto[i];
        stats.totalPhyto += p.phyto[i];
        stats.maxPhyto = max(stats.maxPhyto, p.phyto[i]);

        //Herbivore
        carbon += p.herbivore[i];
        stats.totalHerbivore += p.herbivore[i];
        stats.maxHerbivore = max(stats.maxHerbivore, p.herbivore[i]);

        //WaterDecomp
        carbon += p.waterdecomp[i];
        stats.totalWaterDecomp += p.waterdecomp[i];
        stats.maxWaterDecomp = max(stats.maxWaterDecomp, p.waterdecomp[i]);

        //SedDecomp
        carbon += p.seddecomp[i];
        stats.totalSedDecomp += p.seddecomp[i];
        stats.maxSedDecomp = max(stats.maxSedDecomp, p.seddecomp[i]);

        //SedConsum
        carbon += p.sedconsumer[i];
        stats.totalSedConsumer += p.sedconsumer[i];
        stats.maxSedConsumer = max(stats.maxSedConsumer, p.sedconsumer[i]);

        //Consumer
        carbon += p.consumer[i];
        stats.totalConsum += p.consumer[i];
        stats.maxConsum = max(stats.maxConsum, p.consumer[i]);

        //DOC
        carbon += p.DOC[i];
        stats.totalDOC += p.DOC[i];
        stats.maxDOC = max(stats.maxDOC, p.DOC[i]);

        //POC
        carbon += p.POC[i];
        stats.totalPOC += p.POC[i];
        stats.maxPOC = max(stats.maxPOC, p.POC[i]);

        //Detritus
        carbon += p.detritus[i];
        stats.totalDetritus += p.detritus[i];
        stats.maxDetritus = max(stats.maxDetritus, p.detritus[i]);

        //Carbon
        stats.totalCarbon += carbon;
        stats.maxCarbon = max(stats.maxCarbon, carbon);
    }

    stats.avgMacro       = stats.totalMacro / stats.waterPatches;
    stats.avgPhyto       = stats.totalPhyto / stats.waterPatches;
    stats.avgHerbivore   = stats.totalHerbivore / stats.waterPatches;
    stats.avgWaterDecomp = stats.totalWaterDecomp / stats.waterPatches;
    stats.avgSedDecomp   = stats.totalSedDecomp / stats.waterPatches;
    stats.avgSedConsumer   = stats.totalSedConsumer / stats.waterPatches;
    stats.avgConsum      = stats.totalConsum / stats.waterPatches;
    stats.avgDOC         = stats.totalDOC / stats.waterPatches;
    stats.avgPOC         = stats.totalPOC / stats.waterPatches;
    stats.avgDetritus    = stats.totalDetritus / stats.waterPatches;
    stats.avgCarbon      = stats.totalCarbon / stats.waterPatches;

    return stats;
}

void River::saveCSV(QString displayedStock, int daysElapsed) const {
    /* We are using file descriptors and fprintf after discovering horrible performance on
     * Windows when using QFile or ofstream...
     *
     * Note: QFile is still prefered when NOT saving a file in the program's main loop.
     */

    QString dateAndTime = QDateTime::currentDateTime().toString("MMM_d_H_mm_ss");
    QString filename = "./results/data/map_data_" + dateAndTime + ".csv";

    FILE* f = fopen(filename.toStdString().c_str(), "w");
    if (f == NULL) {
        cout << "Failed to open the csv file for write." << endl;
        exit(1);
    }

    // GUI variables used
    fprintf(f,"%s\n","# timestep_factor,hydro_group,days_to_run,tss,k_phyto,k_macro,sen_macro_coef,resp_macro_coef,macro_base_temp,macro_mass_max,macro_vel_max,gross_macro_coef,which_stock");

    fprintf(f,"%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%s\n",
            config.timestep, daysElapsed, config.tss,
            config.kPhyto, config.kMacro, (config.macroSenescence/24),
            (config.macroRespiration/24), config.macroTemp, config.macroMassMax,
            config.macroVelocityMax, config.macroGross, displayedStock.toStdString().c_str());

    //TODO Print out the hydrofile used for this simulated day.

    fprintf(f,"%s\n","# pxcor,pycor,pcolor,px_vector,py_vector,depth,velocity,assimilation,detritus,DOC,POC,waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consumer");

    int pxcor, pycor, pcolor;
    double px_vector, py_vector;
    double depth;
    double velocity;
    double assimilation;
    double detritus, DOC, POC, waterdecomp, seddecomp, macro, phyto, herbivore, sedconsumer, peri, consumer;

    for(int i = 0; i < p.getSize(); i++) {
        //Skip if cell doesn't exist or is land
        if(!p.hasWater[i]) {
            continue;
        }


        depth = p.depth[i];
        velocity = p.flowMagnitude[i];
        pxcor = p.pxcor[i];
        pycor = p.pycor[i];
        pcolor = p.pcolor[i];
        px_vector = p.flowX[i];
        py_vector = p.flowY[i];
        assimilation = p.assimilation[i];
        detritus = p.detritus[i];
        DOC = p.DOC[i];
        POC = p.POC[i];
        waterdecomp = p.waterdecomp[i];
        seddecomp = p.seddecomp[i];
        macro = p.macro[i];
        phyto = p.phyto[i];
        herbivore = p.herbivore[i];
        sedconsumer = p.sedconsumer[i];
        peri = p.peri[i];
        consumer = p.consumer[i];


        fprintf(f,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",pxcor,pycor,pcolor,px_vector,py_vector,depth,
                  velocity,assimilation,detritus,DOC,POC,
                  waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consumer);

    }
    fclose(f);
}

void River::generateImages(QVector<QImage> &images, QVector<QString> & stockNames,
                           QMutex &imageMutex, Statistics & stats)
{
    imageMutex.lock();
    #pragma omp parallel
    {

     #pragma omp for
        for(int imageIndex = 0; imageIndex < NUM_IMAGES; imageIndex++){
            QColor color("black");
            images[imageIndex].fill(color.rgb());
        }

        #pragma omp for
        for(int i = 0; i < p.getSize(); i++){
            if(!p.hasWater[i]) {
                continue;
            }

            int x = p.pxcor[i];
            int y = p.pycor[i];

            QColor macroColor = getHeatMapColor(p.macro[i], stats.avgMacro, stats.maxMacro);
            QColor phytoColor = getHeatMapColor(p.phyto[i], stats.avgPhyto, stats.maxPhyto);
            QColor herbivoreColor = getHeatMapColor(p.herbivore[i], stats.avgHerbivore, stats.maxHerbivore);
            QColor waterDecompColor = getHeatMapColor(p.waterdecomp[i], stats.avgWaterDecomp, stats.maxWaterDecomp);
            QColor sedDecompColor = getHeatMapColor(p.seddecomp[i], stats.avgSedDecomp, stats.maxSedDecomp);
            QColor sedConsumerColor = getHeatMapColor(p.sedconsumer[i], stats.avgSedConsumer, stats.maxSedConsumer);
            QColor consumColor = getHeatMapColor(p.consumer[i], stats.avgConsum, stats.maxConsum);
            QColor DOCColor = getHeatMapColor(p.DOC[i], stats.avgDOC, stats.maxDOC);
            QColor POCColor = getHeatMapColor(p.POC[i], stats.avgPOC, stats.maxPOC);
            QColor detritusColor = getHeatMapColor(p.detritus[i], stats.avgDetritus, stats.maxDetritus);

            images[STOCK_MACRO].setPixel( x, y, macroColor.rgb());
            images[STOCK_PHYTO].setPixel(x, y, phytoColor.rgb());
            images[STOCK_HERBIVORE].setPixel(x, y, herbivoreColor.rgb());
            images[STOCK_WATERDECOMP].setPixel( x, y, waterDecompColor.rgb());
            images[STOCK_SEDDECOMP].setPixel(x, y, sedDecompColor.rgb());
            images[STOCK_SEDCONSUMER].setPixel(x, y, sedConsumerColor.rgb());
            images[STOCK_CONSUMER].setPixel(x, y, consumColor.rgb());
            images[STOCK_DOC].setPixel(x, y, DOCColor.rgb());
            images[STOCK_POC].setPixel(x, y, POCColor.rgb());
            images[STOCK_DETRITUS].setPixel(x, y, detritusColor.rgb());

            int patchCarbon = p.macro[i] + p.phyto[i] + p.herbivore[i] + p.waterdecomp[i] + p.seddecomp[i]
                    + p.sedconsumer[i] + p.consumer[i] + p.DOC[i] + p.POC[i] + p.detritus[i];
            QColor allCarbonColor = getHeatMapColor(patchCarbon, stats.avgCarbon, stats.maxCarbon);
            images[STOCK_ALL_CARBON].setPixel(x, y, allCarbonColor.rgb());
        }

        //Due to the layout of the hydrofiles, the river will appear upside down if we don't flip it.
        #pragma omp for
        for(int imageIndex = 0; imageIndex < NUM_IMAGES; imageIndex++){
            images[imageIndex] = images[imageIndex].mirrored(false,true);
        }
    }
    imageMutex.unlock();


    QImageWriter writer;
    writer.setFormat("png");
    for(int i = 0; i < NUM_IMAGES; i++){
        QString date_time_str = QDateTime::currentDateTime().toString("_MMM_d_H_mm_ss");
        QString fileName = "./results/images/" + stockNames[i] + date_time_str + ".png";
        writer.setFileName(fileName);
        writer.write(images[i]);
    }
}

/**
 * Scales the color of the patch from green to red.
 * @param value The value of the patch
 * @param maxVal the max value for a patch
 */
QColor River::getHeatMapColor(double carbonValue, double avgVal, double maxVal) {
    if( carbonValue <= 0.0 || maxVal <= 0.0 ) {
        return QColor("green");
    }

    if( carbonValue == avgVal) {
        return QColor("yellow");
    }

    if( carbonValue >= maxVal) {
        return QColor("red");
    }

    double distFromAverage = fabs(carbonValue - avgVal);

    if( carbonValue < avgVal) {
        double relativeValue = distFromAverage / avgVal;
        return QColor::fromHsv( 60 + (int)(60*relativeValue),255,255);
    } else {
        double relativeValue = distFromAverage / (maxVal - avgVal);
        return QColor::fromHsv( 60 - (int)(60*relativeValue),255,255);
    }
}

void River::processPatches() {
    #pragma omp parallel
    {
        PatchComputation::updatePatches(p, config, currPAR);
        PatchComputation::macro(p, config, currPAR, currWaterTemp, currGrowthRate);
        PatchComputation::phyto(p, config, currPAR, currWaterTemp);
        PatchComputation::herbivore(p, config);
        PatchComputation::waterDecomp(p, config);
        PatchComputation::sedDecomp(p, config);
        PatchComputation::sedConsumer(p, config);
        PatchComputation::consumer(p, config);
        PatchComputation::DOC(p, config);
        PatchComputation::POC(p);
        PatchComputation::detritus(p, config);

        #pragma omp for
        for(int i = 0; i < p.getSize(); i++) {
            //Only process patches if they currently contain water
            if(!p.hasWater[i]) {
                continue;
            }

            PatchComputation::predPhyto(p, i);
            PatchComputation::predHerbivore(p, i);
            PatchComputation::predSedDecomp(p, i);
            PatchComputation::predWaterDecomp(p, i);
            PatchComputation::predSedConsumer(p, i);
            PatchComputation::predDetritus(p, i);
            PatchComputation::predDOC(p, i);
            PatchComputation::predPOC(p, i);
            PatchComputation::predConsum(p, i);
        }
    }
}
