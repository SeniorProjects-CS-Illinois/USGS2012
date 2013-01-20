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

int HydroFileDict::getMaxWidth()
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

int HydroFileDict::getMaxHeight()
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
