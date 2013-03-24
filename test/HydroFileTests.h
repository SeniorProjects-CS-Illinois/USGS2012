#ifndef __HYDROFILETESTS_H__
#define __HYDROFILETESTS_H__

#include <QtTest/QtTest>
#include "hydrofile.h"

class HydroFileTests : public QObject
{
    Q_OBJECT
    private slots:
    void hydroFileTest();
};

#endif