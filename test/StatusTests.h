#ifndef __STATUSTESTS_H__
#define __STATUSTESTS_H__

#include <QtTest/QtTest>
#include "status.h"

class StatusTests : public QObject
{
    Q_OBJECT
    private slots:
    void statusTest();
};

#endif