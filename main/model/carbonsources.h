#ifndef CARBONSOURCES_H
#define CARBONSOURCES_H

#include <QVector>

/**
 * Holds the source information for an individual cell
 */

struct CarbonSource {
    CarbonSource() {}
    CarbonSource(int newX,int newY, int newAmount)
        : x(newX), y(newY), amount(newAmount) {}
    int x;
    int y;
    float amount;
};

class CarbonSourceCollection {
    public:
        CarbonSourceCollection();
        CarbonSourceCollection(int newX, int newY);

        void addSource(int x, int y, float ammount);
        void addSource(CarbonSource & source);
        void addSources(QVector<CarbonSource> & sources);
        void addSources(CarbonSourceCollection & sources);

        void removeSourcesPercent(float percent);

        const QVector<CarbonSource> getSources() const;
        const QVector<CarbonSource> getSourcesPercentage(float percent) const;

    private:
        int x;
        int y;
        QVector<CarbonSource> sources;

        void initializeCollection(int newX, int newY);
};

#endif
