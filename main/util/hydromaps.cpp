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

QString HydroMaps::intToHydroFile(int hydro,  const QString & baseDir,
                                  const QVector<int> & minBounds, const QVector<int> & maxBounds)
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

    for (int i = 0; i < minBounds.size() && i < maxBounds.size(); i++)
    {
        if (hydro >= minBounds[i] && hydro <= maxBounds[i])
        {
            file.prepend(i+1);
        }
    }

    return baseDir + QDir::separator() + file;
}
