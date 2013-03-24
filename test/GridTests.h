#ifndef __GRIDTESTS_H__
#define __GRIDTESTS_H__

#include <QtTest/QtTest>
#include "grid.h"

class GridTests : public QObject
{
    Q_OBJECT
    private slots:
    void gridTest();
};

#endif