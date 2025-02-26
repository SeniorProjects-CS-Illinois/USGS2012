#include "hydrofile.h"
#include <iostream>
using std::cout;
using std::endl;


HydroFile::HydroFile(QString filename, RiverIOFile riverIOFile){
    hydroFileLoaded = false;
    loadFromFile(filename, riverIOFile);
}

HydroFile::HydroFile() {
    hydroFileLoaded = false;
}


void HydroFile::loadFromFile(QString filename, RiverIOFile riverIOFile) {

    /* Once loaded, a hydrofile represents only one hydromap. */
    if( hydroFileLoaded )
        return;

    setHydroIndex(filename);

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
        data.fileVelocity   = hydroFileData[index + 5].toDouble();
        data.isInput = false;
        data.isOutput = false;

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
     * cells   
     */
    for(unsigned int x = 0; x < hydroData.getWidth(); x++) {
        for(unsigned int y = 0; y < hydroData.getHeight(); y++) {
            if(hydroData(x,y).depth != 0) {
                hydroDataSet.append(hydroData(x,y));
                int index = getHashKey(x,y);
                hydroDataSetIndices.insert(index,hydroDataSet.size()-1); 
            }
        }
    }

    /*
     * We need to check if a patch exists because the riverIO file is for all hydroFiles
     * and not tailored to each individually (at least for now)
     */
    for(int i = 0; i < riverIOFile.inputs.size(); i++){
        QPoint point = riverIOFile.inputs[i];
        if(patchExists(point.x(), point.y()) ) {
            int hashKey = getHashKey(point.x(), point.y());
            int index = hydroDataSetIndices[hashKey];
            hydroDataSet[index].isInput = true;
        }
    }

    for(int i = 0; i < riverIOFile.outputs.size(); i++){
        QPoint point = riverIOFile.outputs[i];
        if(patchExists(point.x(), point.y()) ) {
            int hashKey = getHashKey(point.x(), point.y());
            int index = hydroDataSetIndices[hashKey];
            hydroDataSet[index].isOutput = true;
        }
    }

    hydroFile.close();
    hydroFileLoaded = true;
}

bool HydroFile::patchExists(int x, int y) const {
    if(x >= width || x < 0 || y >= height || y < 0)
        return false;
    int hashKey = getHashKey(x,y);
    return hydroDataSetIndices.contains(hashKey);
}

const QVector2D & HydroFile::getVector(int x, int y) {
    return getData(x,y).flowVector;
}

double HydroFile::getDepth(int x, int y) {
    return getData(x,y).depth;
}

double HydroFile::getFileVelocity(int x, int y) {
    return getData(x,y).fileVelocity;
}

int HydroFile::getMapHeight() const {
    return height;
}

int HydroFile::getMapWidth() const {
    return width;
}

int HydroFile::getHydroIndex() const {
    return hydroIndex;
}

bool HydroFile::isInput(int x, int y) {
    return getData(x,y).isInput;
}

bool HydroFile::isOutput(int x, int y) {
    return getData(x,y).isOutput;
}

void HydroFile::setMapSize(QStringList & hydroFileData) {
    int maxX = 0;
    int maxY = 0;

    for(int index = 6; index < hydroFileData.size(); index += 6) {

        int patch_x = hydroFileData[index].toInt();
        int patch_y = hydroFileData[index + 1].toInt();

        if(patch_x > maxX) {
            maxX = patch_x;
        }
        if(patch_y > maxY) {
            maxY = patch_y;
        }
    }

    width = maxX + 1;
    height = maxY + 1;
}

int HydroFile::getHashKey(int x, int y) const {
    return (y * width + x);
}

HydroFile::HydroData & HydroFile::getData(int x, int y) {
    if(!patchExists(x,y))
    {
        std::cerr << "Cannot return a location that doesn't exist, use patchExists() before calling getData()!";
        std::cerr << std::endl;
        abort();
    }
    int hashKey = getHashKey(x,y);
    int index = hydroDataSetIndices[hashKey];
    return hydroDataSet[index];
}

void HydroFile::setHydroIndex(QString filename) {
    //If you know a more elegant way of doing this, please implement it.
    if ( filename.contains("10k")) {
        hydroIndex = 0;
    } else if (filename.contains("20k")) {
        hydroIndex = 1;
    } else if (filename.contains("30k")) {
        hydroIndex = 2;
    } else if (filename.contains("40k")) {
        hydroIndex = 3;
    } else if (filename.contains("50k")) {
        hydroIndex = 4;
    } else if (filename.contains("60k")) {
        hydroIndex = 5;
    } else if (filename.contains("70k")) {
        hydroIndex = 6;
    } else if (filename.contains("80k")) {
        hydroIndex = 7;
    } else if (filename.contains("90k")) {
        hydroIndex = 8;
    } else if (filename.contains("100k")) {
        hydroIndex = 9;
    }
}

void HydroFile::zeroHydroData(Grid<HydroData> & hydroData) {

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
                int scaledValue = (int)(120*relativeDepth);
                if(scaledValue > 120){
                    scaledValue = 120;
                } else if (scaledValue < 0) {
                    scaledValue = 0;
                }

                QColor depthColor = QColor::fromHsv( 120 - scaledValue ,255,255);

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

                for(double t = 0.0; t < 1.0; t += 1.0/PATCH_LENGTH) {
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
                double dx = cellFlowVector.x()* (imageCellSize / PATCH_LENGTH)*60;
                double dy = cellFlowVector.y()* (imageCellSize / PATCH_LENGTH)*60;
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
