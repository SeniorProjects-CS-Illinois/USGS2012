#include "carbonflowmap.h"

using std::swap;

CarbonFlowMap::CarbonFlowMap(HydroFile * newHydroFile, int numIterations) {
    hydroFile = newHydroFile;
    iterations = numIterations;

    Grid<CarbonSourceCollection> * source = new Grid<CarbonSourceCollection>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    Grid<CarbonSourceCollection> * dest = new Grid<CarbonSourceCollection>(hydroFile->getMapWidth(), hydroFile->getMapHeight());

    initializeCarbonCollection(*source);
    initializeCarbonCollection(*dest);

    for(int i = 0; i < iterations; i++){
        swap(source, dest);
        pushCarbon(*source, *dest);
    }



    /*
     * TODO: After pushing the carbon, store it all efficicently and
     * get rid of temp data.
     */

    delete source;
    carbonSourceMapGrid = dest;
    //delete dest;
}


CarbonSourceCollection CarbonFlowMap::getPatchSources(int x, int y) const {
    return carbonSourceMapGrid->get(x,y);
}

void CarbonFlowMap::initializeCarbonCollection(Grid<CarbonSourceCollection> & sources){
    for(int i = 0; i < hydroFile->getMapWidth(); i++){
        for( int j = 0; j < hydroFile->getMapHeight(); j++){
            sources(i,j).initializeSource(i,j);
        }
    }
}

void CarbonFlowMap::pushCarbon(
    Grid<CarbonSourceCollection> & source,
    Grid<CarbonSourceCollection> & dest)
{
    for( int i = 0; i < hydroFile->getMapWidth(); i++) {
        for( int j = 0; j < hydroFile->getMapHeight(); j++) {
            if(hydroFile->patchExists(i,j)) {
                QVector<CarbonSource> * targets = getFlowTargets(i,j);
                float carbonLost = 0.0;
                for(int targetIndex = 0; targetIndex < targets->size(); targetIndex++){
                    CarbonSource carbonTarget = targets->at(targetIndex);
                    carbonLost += carbonTarget.ammount;
                    QVector<CarbonSource> carbonPushed = source(i,j).getSourcesPercentage(carbonTarget.ammount);
                    dest(carbonTarget.x, carbonTarget.y).addSources(carbonPushed);
                }

                delete targets;
                dest(i,j).removeSourcesPercent(carbonLost);
            }
        }
    }
}

QVector<CarbonSource> * CarbonFlowMap::getFlowTargets(int i, int j){
    QVector<CarbonSource> * targets = new QVector<CarbonSource>();
    QVector2D flowVector = hydroFile->getVector(i,j);

    int width = PATCH_LENGTH;;
    int height = PATCH_LENGTH;
    double cellArea = (double)(width*height);

    int x = i * width;
    int y = j * height;

    //One cell can flow into at most four others
    //Percents are calculated by target's area over area of a cell
    double newX = x + flowVector.x();
    double newY = y + flowVector.y();

    //Target A
    int iA = floor(newX/((double)width));
    int jA = floor(newY/((double)height));
    if(i != iA && j != jA) {
        if(hydroFile->patchExists(iA, jA)) {
            double targetWidthA = (double)((iA+1)*width) - newX;
            double targetHeightA = (double)((jA+1)*height)-newY;
            double targetAreaA = targetWidthA*targetHeightA;
            float percentA = targetAreaA/cellArea;
            CarbonSource targetA(iA, jA, percentA);
            targets->append(targetA);
        }
    }

    //Target B
    int iB = iA + 1;
    int jB = jA;
    if((i != iB && j != jB)){
        if(hydroFile->patchExists(iB, jB)) {
            double targetWidthB = (newX+width) - (double)((iA+1)*width);
            double targetHeightB = (double)((jA+1)*height) - newY;
            double targetAreaB = targetWidthB*targetHeightB;
            float percentB = targetAreaB/cellArea;
            CarbonSource targetB(iB, jB, percentB);
            targets->append(targetB);
        }
    }

    //Target C
    int iC = iA;
    int jC = jA + 1;
    if((i != iC && j != jC)){
        if(hydroFile->patchExists(iC, jC)) {
            double targetWidthC = (double)((iA+1)*width)-newX;
            double targetHeightC = (newY+height) - (double)((jA+1)*height);
            double targetAreaC = targetWidthC*targetHeightC;
            float percentC = targetAreaC/cellArea;
            CarbonSource targetC(iC, jC, percentC);
            targets->append(targetC);
        }
    }

    //Target D
    int iD = iA + 1;
    int jD = jA + 1;
    if((i != iD && j != jD)){
        if(hydroFile->patchExists(iD, jD)) {
            double targetWidthD = (newX+width) - (double)((iA+1)*width);
            double targetHeightD = (newY+height) - (double)((jA+1)*height);
            double targetAreaD = targetWidthD*targetHeightD;
            float percentD = targetAreaD/cellArea;
            CarbonSource targetD(iD, jD, percentD);
            targets->append(targetD);
        }
    }
    return targets;
}
