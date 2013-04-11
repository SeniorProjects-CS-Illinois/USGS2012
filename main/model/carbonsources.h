#ifndef CARBONSOURCES_H
#define CARBONSOURCES_H

#include <QVector>

/**
 * Holds the source information for an individual cell
 */

struct CarbonSource {
    CarbonSource() {}
    CarbonSource(int newX,int newY, double newAmount)
        : x(newX), y(newY), amount(newAmount) {}
    int x;
    int y;
    double amount;
};

class CarbonSourceCollection {
    public:
        CarbonSourceCollection();
        CarbonSourceCollection(int newX, int newY);

        void addSource(int x, int y, double ammount);
        void addSource(const CarbonSource & source);
        void addSources(const QVector<CarbonSource> & sources);
        void addSources(const CarbonSourceCollection & collection);

        void removeSourcesPercent(double percent);

        const QVector<CarbonSource> * getSources() const;
        const QVector<CarbonSource> getSourcesPercentage(double percent) const;

    private:
        int x;
        int y;
        QVector<CarbonSource> sources;

        void initializeCollection(int newX, int newY);
};

#endif
