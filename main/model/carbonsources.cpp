#include "carbonsources.h"

void CarbonSources::initializeThisSource(int newX, int newY) {
    addSource( newX, newY, 1.0);
    x = newX;
    y = newY;
}

void CarbonSources::addSource(int x, int y, float ammount) {
    for( int i = 0; i < sources.size(); i++ ) {
        if( sources[i].x == x && sources[i].y == y ) {
            sources[i].ammount += ammount;
            return;
        }
    }
    CarbonSource newSource( x, y, ammount );
    sources.add( newSource );
}

void CarbonSources::addSource( CarbonSource & newSource ) {
    addSources( newSource.x, newSource.y, newSource.ammount );
}

void CarbonSources::addSources( vector<CarbonSource> & newSources ) {
    for( int i = 0; i < newSources.size(); i++ ) {
        addSource( newSources[i] );
    }
}

void CarbonSources::removeSourcesPercent( float percent ) {
    for( int i = 0; i < sources.size(); i++) {
        sources[i] *= (1.0 - percent);
    }
}

vector<CarbonSource> CarbonSources::getSources() {
    return sources;
}

vector<CarbonSource> CarbonSources::getSourcesPercentage(float percent) {
    vector<CarbonSource> pctSources;
    for( int i = 0; i < sources.size(); i++ ) {
        CarbonSource newSource( sources[i].x, sources[i].y, sources[i].ammount * percent );
        pctSources.add( newSource );
    }
    return pctSources;
}
