#include "carbonflowmap.h"

#include <iostream>
using std::cout;
using std::endl;
using std::swap;

CarbonFlowMap::CarbonFlowMap() {
    initialized = false;
}

CarbonFlowMap::CarbonFlowMap(HydroFile * newHydroFile, int numIterations) {
    hydroFile = newHydroFile;
    iterations = numIterations;

    Grid<CarbonSourceCollection> * source = new Grid<CarbonSourceCollection>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    Grid<CarbonSourceCollection> * dest = new Grid<CarbonSourceCollection>(hydroFile->getMapWidth(), hydroFile->getMapHeight());

    //We initialize dest because it will become the source after the swap in for loop.
    initializeCarbonCollection(*dest);

    for(int i = 0; i < iterations; i++){
        swap(source, dest);
        //We need a blank destination grid
        for(unsigned int i = 0; i < dest->getArraySize(); i++){
            (*dest)(i) = CarbonSourceCollection();
        }
        pushCarbon(*source, *dest);
    }

    delete source;

    /*
     * At this point we have data on where each cell gets its carbon from in the specified
     * number of iterations.  Now we need to store it so that we optimize spacial locality
     * and so it could be eventually used with OpenCl
     */

    int totalSources = 0;
    for(unsigned int x = 0; x < dest->getWidth(); x++) {
        for(unsigned int y = 0; y < dest->getHeight(); y++) {
            if(hydroFile->patchExists(x,y)){
                (*dest)(x,y).trim(0.0001);
                totalSources += (*dest)(x,y).getSources()->size();
            }
        }
    }

    sourceData.totalSources = totalSources;
    sourceData.sizes = new Grid<int>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    sourceData.offsets = new Grid<int>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    sourceData.x = new int[totalSources];
    sourceData.y = new int[totalSources];
    sourceData.amount = new double[totalSources];



    int currOffset = 0;
    for(unsigned int x = 0; x < dest->getWidth(); x++) {
        for(unsigned int y = 0; y < dest->getHeight(); y++) {
            if(hydroFile->patchExists(x,y)){

                const QVector<CarbonSource> * sources = (*dest)(x,y).getSources();

                (*sourceData.offsets)(x,y) = currOffset;
                (*sourceData.sizes)(x,y) = sources->size();
                for(int i = 0; i < sources->size(); i++) {
                    CarbonSource source = (*sources)[i];
                    sourceData.x[currOffset + i] = source.x;
                    sourceData.y[currOffset + i] = source.y;
                    sourceData.amount[currOffset + i] = source.amount;
                }
                currOffset += sources->size();
            }
        }
    }

    delete dest;
    initialized = true;
}

CarbonFlowMap::CarbonFlowMap(const CarbonFlowMap &other) {
    copy(other);
}

CarbonFlowMap::~CarbonFlowMap() {
    clear();
}

CarbonFlowMap & CarbonFlowMap::operator=(const CarbonFlowMap & rhs) {
    if(this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}


const SourceArrays CarbonFlowMap::getSourceArrays() const {
    return sourceData;
}

void CarbonFlowMap::initializeCarbonCollection(Grid<CarbonSourceCollection> & sources){
    for(int i = 0; i < hydroFile->getMapWidth(); i++){
        for( int j = 0; j < hydroFile->getMapHeight(); j++){
            sources(i,j) = CarbonSourceCollection(i,j);
        }
    }
}

void CarbonFlowMap::pushCarbon(
    Grid<CarbonSourceCollection> & source,
    Grid<CarbonSourceCollection> & dest)
{

    for( int x = 0; x < hydroFile->getMapWidth(); x++) {
        for( int y = 0; y < hydroFile->getMapHeight(); y++) {
            if(hydroFile->patchExists(x,y)) {
                QVector<CarbonSource> * targets = getFlowTargets(x,y);
                double carbonPushedToOtherWaterPatches = 0.0;

                for(int i = 0; i < targets->size(); i++){
                    CarbonSource carbonTarget = (*targets)[i];
                    carbonPushedToOtherWaterPatches += carbonTarget.amount;
                    QVector<CarbonSource> carbonPushed = source(x,y).getSourcesPercentage(carbonTarget.amount);
                    dest(carbonTarget.x, carbonTarget.y).addSources(carbonPushed);
                }
                double percentStationaryCarbon = 1.0 - carbonPushedToOtherWaterPatches;
                dest(x,y).addSources( source(x,y).getSourcesPercentage(percentStationaryCarbon) );
                //TODO: Avoid new and deleting over and over...
                delete targets;
            }
        }
    }
}

QVector<CarbonSource> * CarbonFlowMap::getFlowTargets(int i, int j){
    QVector<CarbonSource> * targets = new QVector<CarbonSource>();
    QVector2D flowVector = hydroFile->getVector(i,j);

    int x = i * PATCH_LENGTH;
    int y = j * PATCH_LENGTH;

    //One cell can flow into at most four others
    //Percents are calculated by target's area over area of a cell
    double newX = x + flowVector.x() * 60;
    double newY = y + flowVector.y() * 60;

    /**
     * Note: HydroFiles have 0,0 in the bottom left
     *  _______
     * |   |   |
     * | C | D |
     * |___|___|
     * |   |   |
     * | A | B |
     * |___|___|
     *
     * i,j = Patch coordinates
     * x,y = meters from origin
     *
     */
    //Target Coordinates (unused commented out)
    int iA = floor(newX/((double)PATCH_LENGTH));
    int jA = floor(newY/((double)PATCH_LENGTH));
    //double xA = iA * PATCH_LENGTH;
    //double yA = jA * PATCH_LENGTH;

    int iB = iA + 1;
    int jB = jA;
    double xB = iB * PATCH_LENGTH;
    //double yB = jB * PATCH_LENGTH;

    int iC = iA;
    int jC = jA + 1;
    //double xC = iC * PATCH_LENGTH;
    double yC = jC * PATCH_LENGTH;

    int iD = iA + 1;
    int jD = jA + 1;
    double xD = iD * PATCH_LENGTH;
    double yD = jD * PATCH_LENGTH;

    //We need to find what percentage of water flowed to A,B,C and D

    //Target A
    if(hydroFile->patchExists(iA, jA)) {
        double targetWidthA = xB - newX;
        double targetHeightA = yC - newY;
        double targetAreaA = targetWidthA*targetHeightA;
        double percentA = targetAreaA/PATCH_AREA;
        CarbonSource targetA(iA, jA, percentA);
        targets->append(targetA);
    }

    //Target B
    if(hydroFile->patchExists(iB, jB)) {
        double targetWidthB = (newX+PATCH_LENGTH) - xB;
        double targetHeightB = yD - newY;
        double targetAreaB = targetWidthB*targetHeightB;
        double percentB = targetAreaB/PATCH_AREA;
        CarbonSource targetB(iB, jB, percentB);
        targets->append(targetB);
    }

    //Target C
    if(hydroFile->patchExists(iC, jC)) {
        double targetWidthC = xD-newX;
        double targetHeightC = (newY+PATCH_LENGTH) - yC;
        double targetAreaC = targetWidthC*targetHeightC;
        double percentC = targetAreaC/PATCH_AREA;
        CarbonSource targetC(iC, jC, percentC);
        targets->append(targetC);
    }

    //Target D
    if(hydroFile->patchExists(iD, jD)) {
        double targetWidthD = (newX+PATCH_LENGTH) - xD;
        double targetHeightD = (newY+PATCH_LENGTH) - yD;
        double targetAreaD = targetWidthD*targetHeightD;
        double percentD = targetAreaD/PATCH_AREA;
        CarbonSource targetD(iD, jD, percentD);
        targets->append(targetD);
    }

    return targets;
}

void CarbonFlowMap::copy(const CarbonFlowMap &other) {
    initialized = other.initialized;
    hydroFile = other.hydroFile;
    iterations = other.iterations;

    sourceData.totalSources = other.sourceData.totalSources;
    sourceData.offsets = new Grid<int>(*other.sourceData.offsets);
    sourceData.sizes = new Grid<int>(*other.sourceData.sizes);

    sourceData.x = new int[sourceData.totalSources];
    sourceData.y = new int[sourceData.totalSources];
    sourceData.amount = new double[sourceData.totalSources];

    for(int i = 0; i < sourceData.totalSources; i++) {
        sourceData.x[i] = other.sourceData.x[i];
        sourceData.y[i] = other.sourceData.y[i];
        sourceData.amount[i] = other.sourceData.amount[i];
    }
}

void CarbonFlowMap::clear() {
    /* Note: We do not delete hydroFile as that is created/deleted
     * elsewhere and we only point to it.
     */
    if(initialized) {
        delete [] sourceData.x;
        delete [] sourceData.y;
        delete [] sourceData.amount;
        delete sourceData.offsets;
        delete sourceData.sizes;
    }
}

void CarbonFlowMap::printDebug(){
    //Debugging info
    for(unsigned int x = 0; x < sourceData.offsets->getWidth(); x++){
        for(unsigned int y = 0; y < sourceData.offsets->getHeight(); y++) {
            int currOffset = (*sourceData.offsets)(x,y);
            int numSources = (*sourceData.sizes)(x,y);
            for(int i = 0; i < numSources; i++) {

                cout << "(" << x << "," << y << ") receives ";
                cout << sourceData.amount[currOffset + i] * 100.0 << "% from (";
                cout << sourceData.x[currOffset + i] << "," << sourceData.y[currOffset + i] << ")" << endl;

            }
        }
    }
}
