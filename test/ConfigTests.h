#ifndef __CONFIGTESTS_H__
#define __CONFIGTESTS_H__

#include <QtTest/QtTest>
#include "configuration.h"

class ConfigTests: public QObject
{
    Q_OBJECT
    private slots:
    void configTest();
};

#endif