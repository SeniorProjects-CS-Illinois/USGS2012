#include "carbonsources.h"

void CarbonSourceCollection::initializeSource(int newX, int newY) {
    addSource( newX, newY, 1.0);
    x = newX;
    y = newY;
}

void CarbonSourceCollection::addSource(int x, int y, float ammount) {
    for( int i = 0; i < sources.size(); i++ ) {
        if( sources[i].x == x && sources[i].y == y ) {
            sources[i].ammount += ammount;
            return;
        }
    }
    CarbonSource newSource( x, y, ammount );
    sources.append( newSource );
}

void CarbonSourceCollection::addSource( CarbonSource & newSource ) {
    addSource( newSource.x, newSource.y, newSource.ammount );
}

void CarbonSourceCollection::addSources( QVector<CarbonSource> & newSources ) {
    for( int i = 0; i < newSources.size(); i++ ) {
        addSource( newSources[i] );
    }
}

void CarbonSourceCollection::removeSourcesPercent( float percent ) {
    for( int i = 0; i < sources.size(); i++) {
        sources[i].ammount *= (1.0 - percent);
    }
}

const QVector<CarbonSource> CarbonSourceCollection::getSources() const {
    return sources;
}

const QVector<CarbonSource> CarbonSourceCollection::getSourcesPercentage(float percent) const {
    QVector<CarbonSource> pctSources;
    for( int i = 0; i < sources.size(); i++ ) {
        CarbonSource newSource( sources[i].x, sources[i].y, sources[i].ammount * percent );
        pctSources.append( newSource );
    }
    return pctSources;
}
