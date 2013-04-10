#ifndef FILES_H
#define FILES_H

#include <QtCore>

namespace Files
{
    /**
     * Strips off all path info except file name.
     */
    QString stripFile(const QString &path);

    /**
     * Used to make file selection faster.
    */
    QString defaultFileLocation();
}

#endif // FILES_H
