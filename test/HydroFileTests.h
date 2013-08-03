#ifndef __HYDROFILETESTS_H__
#define __HYDROFILETESTS_H__

#include <QtTest/QtTest>
#include "hydrofile.h"

class HydroFileTests : public QObject
{
    private:
    HydroFile hydroFile_;
    HydroFile hydroFileWithIO_;

    Q_OBJECT
    private slots:
    void dimensionsTest();
    void initTestCase();
    void patchExistTest();
    void patchNotExhistTest();
    void depthTest();
    void vectorTest();
    void velocityTest();
    void testIO();

};

#endif