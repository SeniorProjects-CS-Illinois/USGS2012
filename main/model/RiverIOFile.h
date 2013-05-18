#ifndef __RIVERIOFILE_H__
#define __RIVERIOFILE_H__

#include <QString>
#include <QFile>
#include <QStringList>
#include <QVector>
#include <QPoint>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

class RiverIOFile
{
public:
	RiverIOFile(QString filename);

    QVector<QPoint> inputs;
    QVector<QPoint> outputs;
};


#endif