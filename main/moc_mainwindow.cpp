/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Dec 8 03:38:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "view/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      36,   11,   11,   11, 0x0a,
      57,   11,   11,   11, 0x0a,
      81,   11,   11,   11, 0x0a,
     110,   11,   11,   11, 0x0a,
     141,   11,   11,   11, 0x0a,
     164,   11,   11,   11, 0x0a,
     186,  177,   11,   11, 0x0a,
     213,   11,   11,   11, 0x0a,
     225,   11,   11,   11, 0x0a,
     245,  238,   11,   11, 0x0a,
     273,  265,   11,   11, 0x0a,
     318,  300,   11,   11, 0x0a,
     357,  346,   11,   11, 0x0a,
     377,   11,   11,   11, 0x08,
     397,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0selectHydroMapClicked()\0"
    "addHydroMapClicked()\0removeHydroMapClicked()\0"
    "selectDischargeFileClicked()\0"
    "selectTemperatureFileClicked()\0"
    "selectPARFileClicked()\0runClicked()\0"
    "newStock\0whichstockChanged(QString)\0"
    "enableRun()\0disableRun()\0newVal\0"
    "timestepUpdate(int)\0percent\0"
    "progressPercentUpdate(int)\0elapsed,remaining\0"
    "progressTimeUpdate(int,int)\0stockImage\0"
    "imageUpdate(QImage)\0saveConfiguration()\0"
    "loadConfiguration()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->selectHydroMapClicked(); break;
        case 1: _t->addHydroMapClicked(); break;
        case 2: _t->removeHydroMapClicked(); break;
        case 3: _t->selectDischargeFileClicked(); break;
        case 4: _t->selectTemperatureFileClicked(); break;
        case 5: _t->selectPARFileClicked(); break;
        case 6: _t->runClicked(); break;
        case 7: _t->whichstockChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->enableRun(); break;
        case 9: _t->disableRun(); break;
        case 10: _t->timestepUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->progressPercentUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->progressTimeUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->imageUpdate((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 14: _t->saveConfiguration(); break;
        case 15: _t->loadConfiguration(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
