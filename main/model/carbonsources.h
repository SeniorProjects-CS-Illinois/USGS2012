#ifndef __CARBONSOURCES_H__
#define __CARBONSOURCES_H__

#include <vector>

/**
 * Holds the source information for an individual cell
 */

using std::vector

struct CarbonSource {
    CarbonSource(int x, int y, float ammount) : x(x), y(y), ammount(ammount) {}
    int x;
    int y;
    float ammount;
};

class CarbonSources {
    public:
        void initalizeThisSource(int newX, int newY, bool isInputCell);

        void addSource(int x, int y, float ammount);
        void addSource(CarbonSource source);
        void addSources(vector<CarbonSource> sources);

        void removeSourcesPercent(float percent);

        vector<CarbonSource> getSources();
        vector<CarbonSource> getSourcesPercentage(float percent);

    private:
        int x;
        int y;
        vector<CarbonSource> sources;
};

#endif
