#include "files.h"

QString Files::stripFile(QString path)
{
    int lastSlashIndex = path.lastIndexOf("/");
    return path.mid(lastSlashIndex + 1);
}

QString Files::defaultFileLocation()
{
    // change output to wherever data dir is
    return  QDir::currentPath().append("/data");
}
