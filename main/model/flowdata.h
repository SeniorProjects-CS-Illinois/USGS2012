#ifndef FLOWDATA_H
#define FLOWDATA_H

typedef struct FlowData
{
    bool hasWater;
    double depth;
    double velocity;
    double py_vector;
    double px_vector;
    double DOC;
    double POC;
    double phyto;
    double waterdecomp;

    FlowData() : hasWater(false), depth(0.0), velocity(0.0), py_vector(0.0), px_vector(0.0),\
        DOC(0.0), POC(0.0), phyto(0.0), waterdecomp(0.0) {}
} FlowData;


#endif
