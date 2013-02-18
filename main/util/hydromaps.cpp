#include "hydromaps.h"

uint16_t HydroMaps::parseDaysToRun(QListWidgetItem* item)
{
    QString text = item->text();
    size_t colonIndex = text.lastIndexOf(':');
    size_t daysIndex = text.indexOf('D', colonIndex + 2);
    size_t size = daysIndex - colonIndex - 3;

    return atoi(text.toStdString().substr(colonIndex + 2, size).c_str());
}

QString HydroMaps::parseHydroMapName(QListWidgetItem* item)
{
    QString text = item->text();
    size_t colonIndex = text.lastIndexOf(':');

    return text.mid(0, colonIndex);
}

QString HydroMaps::intToHydroFile(int hydro, QString baseDir)
{
    // TODO: make more general
    QString file("0k-new.txt");
    if (hydro < MIN_HYDRO_DEPTH)
    {
        hydro = MIN_HYDRO_DEPTH;
    }
    else if (hydro > MAX_HYDRO_DEPTH)
    {
        hydro = MAX_HYDRO_DEPTH;
    }
    hydro += 5000; // this is to make rounding accurate
    file.prepend(QString::number(hydro/10000));
    return baseDir + QDir::separator() + file;
}
