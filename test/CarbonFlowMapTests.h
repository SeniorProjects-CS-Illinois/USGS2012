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
    void testPartialFlow();
    void testLandFlow();
};

#endif