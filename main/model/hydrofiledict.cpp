#include "hydrofiledict.h"

HydroFileDict::HydroFileDict(QStringList newFilenames)
{
    filenames = newFilenames;

    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        if( !dict.contains(filename) ) {
            HydroFile * newHydroFile = new HydroFile(filename);
            dict.insert(filename, newHydroFile);
        }
    }
}

HydroFileDict::HydroFileDict(){

}

HydroFile * & HydroFileDict::operator[](const QString filename)
{
    return dict[filename];
}

const HydroFile * HydroFileDict::operator[](const QString filename) const
{
    return dict[filename];
}

//TODO Keep track of max width when adding hydrofiles and store in member variable
int HydroFileDict::getMaxWidth() const
{
    int maxWidth = 0;
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapWidth = dict[filename]->getMapWidth();
        if(mapWidth > maxWidth)
        {
            maxWidth = mapWidth;
        }
    }
    return maxWidth;
}

//TODO Keep track of max height when adding hydrofiles and store in member variable
int HydroFileDict::getMaxHeight() const
{
    int maxHeight = 0;
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapHeight = dict[filename]->getMapHeight();
        if(mapHeight > maxHeight)
        {
            maxHeight = mapHeight;
        }
    }
    return maxHeight;
}

HydroFileDict::~HydroFileDict() {
    for( QHash<QString, HydroFile *>::iterator i = dict.begin(); i != dict.end(); i++){
        delete *i;
    }
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
                if (dict[filename]->patchExists(x,y)) {
                    patchUsage.set(x,y,true);
                    continue;
                }
            }
        }
    }

    return patchUsage;
}
