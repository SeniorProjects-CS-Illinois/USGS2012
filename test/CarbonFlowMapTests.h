#ifndef __CARBONFLOWMAPTESTS_H__
#define __CARBONFLOWMAPTESTS_H__

#include <QtTest/QtTest>
#include "carbonflowmap.h"
#include "hydrofile.h"


class CarbonFlowMapTests : public QObject
{
    Q_OBJECT
    private slots:
    void testFullFlow();
    void testFullFlow2iter();
    void testPartialFlow();
    void testPartialFlow2iter();
    void testLandFlow();
    void testLandFlow2iter();
    void testRiverIO();
};

#endif