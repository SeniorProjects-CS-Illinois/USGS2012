#include "hydrofile.h"
#include "carbonflowmap.h"
#include <iostream>
using std::cout;
using std::endl;


HydroFile::HydroFile(QString filename){
    hydroFileLoaded = false;
    loadFromFile(filename);
}

HydroFile::HydroFile() {
    hydroFileLoaded = false;
}


void HydroFile::loadFromFile(QString filename) {

    /* Once loaded, a hydrofile represents only one hydromap. */
    if( hydroFileLoaded )
        return;

    hydroMapFileName = filename;

    QFile hydroFile( filename );
    if( !hydroFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        printf("Failed to open the hydromap");
        exit(1);
    }

    waterCellCount = 0;
    maxDepth = 0.0;
    maxFlow = 0.0;

    QString hydroFileText = hydroFile.readAll();
    QStringList hydroFileData = hydroFileText.split(" ");

    //Determine dimensions of map and setup a blank grid
    setMapSize(hydroFileData);
    Grid<HydroData> hydroData(width, height);
    zeroHydroData(hydroData);


    /* The data in the file is not in order so we first organize it in a grid
     * before moving it to a vector.  While we are at it we record some
     * information about the map.  Note that every six elements are related
     * to a cell.  The first six are skipped since are they names for the columns.
     */
    for(int index = 6; index < hydroFileData.size(); index += 6) {
        HydroData data;

        int patch_x = hydroFileData[index].toInt();
        int patch_y = hydroFileData[index + 1].toInt();

        data.depth          = hydroFileData[index + 2].toDouble();
        data.flowVector.setX( hydroFileData[index + 3].toDouble() );
        data.flowVector.setY( hydroFileData[index + 4].toDouble() );

        hydroData(patch_x, patch_y) = data;

        if(data.depth > 0){
            waterCellCount++;
            if(data.depth > maxDepth) {
                maxDepth = data.depth;
            }
            if(data.flowVector.length() > maxFlow) {
                maxFlow = data.flowVector.length();
            }
        }
    }

    /* Now we move the data from the grid and place it in a vector whose
     * element indices are hashed using the x,y coordinates of corresponding
     * cells   */
    for(unsigned int x = 0; x < hydroData.getWidth(); x++) {
        for(unsigned int y = 0; y < hydroData.getHeight(); y++) {
            if(hydroData(x,y).depth != 0) {
                hydroDataSet.append(hydroData(x,y));
                int index = getHashKey(x,y);
                hydroDataSetIndices.insert(index,hydroDataSet.size()-1); 
            }
        }
    }

    hydroFile.close();
    hydroFileLoaded = true;
}

/*
HydroFile::~HydroFile() {
    //TODO Once the carbon flow map is implemented
}

HydroFile const & HydroFile::operator=( HydroFile const & other ) {
    //TODO Once the carbon flow map is implemented
    return other;
}

CarbonFlowMap * HydroFile::getCarbonFlowMap(int iterations)
{
    //TODO Build and memoize the carbonflowmap for the given number of iterations
    return NULL;
}
*/

bool HydroFile::patchExists(int x, int y) const {
    int hashKey = getHashKey(x,y);
    return hydroDataSetIndices.contains(hashKey);
}

QVector2D HydroFile::getVector(int x, int y) {
    return getData(x,y).flowVector;
}

double HydroFile::getDepth(int x, int y) {
    return getData(x,y).depth;
}

int HydroFile::getMapHeight() const {
    return height;
}

int HydroFile::getMapWidth() const {
    return width;
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

int HydroFile::getHashKey(int x, int y) const {
    return (y * width + x);
}

HydroFile::HydroData & HydroFile::getData(int x, int y) {
    int hashKey = getHashKey(x,y);
    int index = hydroDataSetIndices[hashKey];
    return hydroDataSet[index];
}

/*
void HydroFile::copy(HydroFile const & other) {
    //TODO
}
void HydroFile::clear() {
    //TODO
}
*/

void HydroFile::zeroHydroData(Grid<HydroData> hydroData) {

    for(unsigned int x = 0; x < hydroData.getWidth(); x++) {
        for(unsigned int y = 0; y < hydroData.getHeight(); y++) {
            hydroData(x,y).depth = 0;
        }
    }
}

QImage HydroFile::generateVisualization(int imageCellSize){
    int offset = 50;
    int imageHeight = height*imageCellSize + offset * 2;
    int imageWidth = width*imageCellSize + offset * 2;

    QImage image( imageWidth, imageHeight, QImage::Format_ARGB32 );
    image.fill(qRgb(32,32,32));

    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(patchExists(x,y) && getDepth(x,y) > 0) {
                double cellDepth = getDepth(x,y);
                double relativeDepth = cellDepth / maxDepth;
                QColor depthColor = QColor::fromHsv( 120 - (int)(120*relativeDepth)+1 ,255,255);

                for(int i = x * imageCellSize; i < (x + 1)*imageCellSize; i++) {
                    for(int j = y * imageCellSize; j < (y +1)*imageCellSize; j++) {
                        if(i < imageWidth && j < imageHeight) {
                            image.setPixel(i+offset, j+offset, depthColor.rgb());
                        }
                    }
                }
            }
        }
    }
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(patchExists(x,y) && getDepth(x,y) > 0) {
                double cellI = x*imageCellSize;
                double cellJ = y*imageCellSize;

                double startLineI = (cellI);
                double startLineJ = (cellJ);
                double endLineI   = (startLineI + imageCellSize);
                double endLineJ   = (startLineJ + imageCellSize);

                for(double t = 0.0; t < 1.0; t += 1.0/30.0) {
                    int i = (1.0 - t)*startLineI + t*endLineI;
                    int j = (1.0 - t)*startLineJ + t*endLineJ;

                    if(i >= 0 && y >= 0 && i < imageWidth && j < imageHeight && cellJ + imageCellSize < imageHeight && cellI + imageCellSize < imageWidth) {
                        image.setPixel(i + offset, (int)(cellJ) + offset, qRgb(0,0,0));
                        image.setPixel(i + offset, (int)(cellJ + imageCellSize) + offset, qRgb(0,0,0));
                        image.setPixel((int)(cellI) + offset, j + offset, qRgb(0,0,0));
                        image.setPixel((int)(cellI + imageCellSize) + offset, j + offset, qRgb(0,0,0));

                    }
                }
            }
        }
    }
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(patchExists(x,y) && getDepth(x,y) > 0) {
                QVector2D cellFlowVector = getVector(x,y);
                double dx = cellFlowVector.x()* (imageCellSize / 30.0)*60;
                double dy = cellFlowVector.y()* (imageCellSize / 30.0)*60;
                double cellI = x*imageCellSize;
                double cellJ = y*imageCellSize;

                double startLineI = (cellI + imageCellSize/2.0);
                double startLineJ = (cellJ + imageCellSize/2.0);
                double endLineI   = (startLineI + dx);
                double endLineJ   = (startLineJ + dy);

                for(double t = 0.0; t < 1.0; t += 1.0/100.0) {
                    int i = (1.0 - t)*startLineI + t*endLineI;
                    int j = (1.0 - t)*startLineJ + t*endLineJ;

                    int cellHorizontal = (1.0 - t)*(cellI + dx) + t*(cellI+imageCellSize + dx);
                    int cellVertical = (1.0 - t)*(cellJ + dy) + t*(cellJ + imageCellSize + dy);

                    if( i >= 0 && y >= 0 && i < imageWidth && j < imageHeight) {
                        image.setPixel(i + offset, j + offset, qRgb(0,0,255));
                        image.setPixel(cellHorizontal + offset, (int)(cellJ + dy) + offset, qRgba(255,0,255,50));
                        image.setPixel(cellHorizontal + offset, (int)(cellJ + imageCellSize + dy) + offset, qRgba(255,0,255,50));
                        image.setPixel((int)(cellI + dx) + offset, cellVertical + offset, qRgba(255,0,255,50));
                        image.setPixel((int)(cellI + imageCellSize + dx) + offset, cellVertical + offset, qRgba(255,0,255,50));
                    }
                }
                if(endLineI+offset >= 0 && endLineJ+offset >= 0 && endLineI+offset < imageWidth && endLineJ+offset < imageHeight){
                    image.setPixel(endLineI + offset, endLineJ + offset, qRgb(255,0,0));
                }
            }
        }
    }

    return image.mirrored(false,true);
}
