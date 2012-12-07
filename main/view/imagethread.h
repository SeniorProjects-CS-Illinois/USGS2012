#ifndef IMAGETHREAD_H
#define IMAGETHREAD_H

#include <QThread>

#include "../model/status.h"
#include "../model/rivermodel.h"

class ImageThread : public QThread
{
    Q_OBJECT
public:
    explicit ImageThread(QObject* parent = 0, RiverModel* m = 0);

    void run();

    void setRiverModel(RiverModel* m);
    
signals:
    // TODO: make this QImage instead of QString?
    void imageUpdate(QImage stockImage);
    
public slots:
    // No slots
    
private:
    RiverModel* model;
};

#endif // IMAGETHREAD_H
