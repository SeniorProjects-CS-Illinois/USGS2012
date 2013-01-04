#ifndef HYDROMAPS_H
#define HYDROMAPS_H

#include <QListWidgetItem>
#include <stdint.h>

namespace HydroMaps
{
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
    QString intToHydroFile(int hydro, QString base);
}

#endif // HYDROMAPS_H
