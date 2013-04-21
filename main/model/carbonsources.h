#ifndef CARBONSOURCES_H
#define CARBONSOURCES_H

#include <QVector>

/**
 * Holds the source information for an individual cell
 */

struct CarbonSource {
    CarbonSource() : x(-1), y(-1), ammount(-1.0) {}
    CarbonSource(int x, int y, float ammount) : x(x), y(y), ammount(ammount) {}
    int x;
    int y;
    float ammount;
};

class CarbonSourceCollection {
    public:
        void initializeSource(int newX, int newY);

        void addSource(int x, int y, float ammount);
        void addSource(CarbonSource & source);
        void addSources(QVector<CarbonSource> & sources);

        void removeSourcesPercent(float percent);

        const QVector<CarbonSource> getSources() const;
        const QVector<CarbonSource> getSourcesPercentage(float percent) const;

    private:
        int x;
        int y;
        QVector<CarbonSource> sources;
};

#endif
