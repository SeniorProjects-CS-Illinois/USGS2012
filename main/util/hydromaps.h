#ifndef HYDROMAPS_H
#define HYDROMAPS_H

#include <QListWidgetItem>
#include <QDir>
#include <stdint.h>

namespace HydroMaps
{
    const int MIN_HYDRO_DEPTH = 10000;
    const int MAX_HYDRO_DEPTH = 100000;

    /**
     * Get the days to run value from the given item.
     */
    uint16_t parseDaysToRun(QListWidgetItem* item); // TODO: currently not used, is this needed?

    /**
     * Get the hydro map file name from the given item.
     */
    QString parseHydroMapName(QListWidgetItem* item); // TODO: currently not used, is this needed?

    /**
     * Finds the appropriate hydro file based on the given integer.
     */
    QString intToHydroFile(int hydro, QString baseDir);
}

#endif // HYDROMAPS_H
