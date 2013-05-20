#include "hydrofiledict.h"

#include <iostream>
using std::cout;
using std::endl;

HydroFileDict::HydroFileDict(QStringList newFilenames)
{
    newFilenames.removeDuplicates();
    filenames = newFilenames;

    //TODO Move IO data to hydrofiles or move file selection to GUI
    RiverIOFile riverIOFile(QDir::currentPath().append("/data/inputsoutputs.txt"));

#pragma omp parallel for
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename;
        #pragma omp critical
        {
            filename = filenames[i];
            cout << "Loading: " << filename.toStdString() << endl;
        }


        HydroData * newHydroData = new HydroData;
        newHydroData->hydroFile = HydroFile(filename, riverIOFile);


        #pragma omp critical
        cout << "Precomputing flows for: " << filename.toStdString() << endl;

        newHydroData->carbonFlowMap =
                CarbonFlowMap(&newHydroData->hydroFile, ITERATIONS_TO_PRECOMPUTE_FLOWS);

        #pragma omp critical
        dict.insert(filename, newHydroData);
    }

    maxWidth = computeMaxWidth();
    maxHeight = computeMaxHeight();

}

HydroFileDict::HydroFileDict(){

}

HydroFileDict::HydroFileDict(const HydroFileDict &other) {
    copy(other);
}

HydroFileDict & HydroFileDict::operator=(const HydroFileDict &rhs) {
    if(this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

HydroData * & HydroFileDict::operator[](const QString filename)
{
    return dict[filename];
}

const HydroData * HydroFileDict::operator[](const QString filename) const
{
    return dict[filename];
}

int HydroFileDict::computeMaxWidth() const
{
    int maxWidth = 0;
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapWidth = dict[filename]->hydroFile.getMapWidth();
        if(mapWidth > maxWidth)
        {
            maxWidth = mapWidth;
        }
    }

    return maxWidth;
}

int HydroFileDict::computeMaxHeight() const
{
    int maxHeight = 0;
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapHeight = dict[filename]->hydroFile.getMapHeight();
        if(mapHeight > maxHeight)
        {
            maxHeight = mapHeight;
        }
    }
    return maxHeight;
}

int HydroFileDict::getMaxWidth() const {
    return maxWidth;
}

int HydroFileDict::getMaxHeight() const {
    return maxHeight;
}

HydroFileDict::~HydroFileDict() {
    clear();
}

const Grid<bool> HydroFileDict::getPatchUsageGrid() const {
    int width = getMaxWidth();
    int height = getMaxHeight();

    Grid<bool> patchUsage(width, height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            patchUsage.set(x,y,false);
            for(int i = 0; i < filenames.size(); i++) {
                QString filename = filenames[i];
                if (dict[filename]->hydroFile.patchExists(x,y)) {
                    patchUsage.set(x,y,true);
                    continue;
                }
            }
        }
    }

    return patchUsage;
}

void HydroFileDict::clear() {
    for( QHash<QString, HydroData *>::iterator i = dict.begin(); i != dict.end(); i++){
        delete *i;
    }
}

void HydroFileDict::copy(const HydroFileDict &rhs) {
    filenames = QStringList(rhs.filenames);
    for(int i = 0; i < filenames.size(); i++) {
        QString filename = filenames[i];
        HydroData * hydroDataCopy = new HydroData();
        *hydroDataCopy = *(rhs.dict[filename]);

        dict.insert(filename, hydroDataCopy);
    }

    maxHeight = rhs.maxHeight;
    maxWidth = rhs.maxWidth;
}
