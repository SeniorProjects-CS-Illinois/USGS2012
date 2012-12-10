#include "hydrofile.h"

HydroFile::HydroFile(QString filename) {

    hydroMapFileName = filename;

    QFile hydroFile( filename );
    if( !hydroFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        printf("Failed to open the hydromap");
        exit(1);
    }

    int covered_cells = 0;
    int uncovered_cells = 0;

    QString hydroFileText = hydroFile.readAll();
    QStringList hydroFileData = hydroFileText.split(" ");

    setMapSize(hydroFileData);
    Grid<HydroData> hydroData(width, height);
    zeroHydroData(hydroData);


    for(int index = 6; index < hydroFileData.size(); index += 6) {

        int patch_x = hydroFileData[index].toInt();
        int patch_y = hydroFileData[index + 1].toInt();
        int hashKey = getHashKey(patch_x, patch_y);

        HydroData data;
        data.depth          = hydroFileData[index + 2].toDouble();
        data.flowVector.x   = hydroFileData[index + 3].toDouble();
        data.flowVector.y   = hydroFileData[index + 4].toDouble();

        hydroData(patch_x, patch_y) = data;
    }
    
    for(int x = 0; x < hydroData.getXDim(); x++) {
        for(int y = 0; y < hydroData.getYDim(); y++) {
            if(hydroData(x,y).depth != 0) {
                hydroDataSet.append(hydroData(x,y));
                int index = getHashKey(x,y);
                hydroDataSetIndices.insert(index,hydroDataSet.size()-1); 
            }
        }
    }

    hydroFile.close();
}

HydroFile::~HydroFile() {
    //TODO
}

HydroFile const & HydroFile::operator=( HydroFile const & other ) {
    //TODO
    return other;
}

CarbonFlowMap * HydroFile::getCarbonFlowMap(int iterations)
{
    return NULL;
}

bool HydroFile::patchExists(int x, int y) const {
    int hashKey = getHashKey(x,y);
    return hydroDataSetIndicies.contains(hashKey);
}

double HydroFile::getVector(int x, int y) const {
    return getData(x,y).flowVector;
}

double HydroFile::getDepth(int x, int y) const {
    return getData(x,y).depth;
}

void HydroFile::setMapSize(QStringList hydroFileData) {
    width = 0;
    height = 0;

    for(int index = 6; index < hydroFileData.size(); index += 6) {

        int patch_x = hydroFileData[index].toInt();
        int patch_y = hydroFileData[index + 1].toInt();

        if(patch_x > width) {
            width = patch_x;
        }
        if(patch_y > height) {
            height = patch_y;
        }
    }

    //TODO: Why is this here? Is there an out of bounds exception they tried to fix here?
    width++;
    height++;
}

int HydroFile::getHashKey(int x, int y) {
    return (y * width + x);
}

HydroData & getData(int x, int y) {
    int hashKey = getHashKey(x,y);
    int index = hydroDataSetIndicies[hashKey];
    return hydroDataSet[index];
}

void HydroFile::copy(HydroFile const & other) {
    //TODO
}
void HydroFile::clear() {
    //TODO
}

void zeroHydroData(Grid<HydroData> hydroData) {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            hydroData(x,y).depth = 0;
        }
    }
}
