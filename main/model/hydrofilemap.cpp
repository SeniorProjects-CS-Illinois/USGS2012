#include "hydrofilemap.h"

HydroFileMap::HydroFileMap(QStringList filenames)
{
    this.filenames = filenames;
    map = new QHash<QString, HydroFile>();

    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        map.insert(filename, HydroFile(filename));
    }
}

HydroFileMap::~HydroFileMap()
{
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        map[filename].~HydroFile();
    }
    delete map;
}

HydroFile & HydroFileMap::operator[](const Qstring filename)
{
    return map[filename];
}

const HydroFile & HydroFileMap::operator[](const Qstring filename) const
{
    return map[filename];
}

int HydroFileMap::getMaxWidth()
{
    int maxWidth = 0
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapWidth = map[filename].getMapWidth();
        if(mapWidth > maxWidth)
        {
            maxWidth = mapWidth;
        }
    }
    return maxWidth;
}

int HydroFileMap::getMaxHeight()
{
    int maxHeight = 0
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapHeight = map[filename].getMapHeight();
        if(mapHeight > maxHeight)
        {
            maxHeight = mapHeight;
        }
    }
    return maxWidth;
}
