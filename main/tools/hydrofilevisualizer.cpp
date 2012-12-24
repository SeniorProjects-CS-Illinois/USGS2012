#include "../model/hydrofile.h"
#include <QString>
#include <QImage>


int main(int argc, char *argv[]) {

    if(argc > 2){
        QString hydroFileName(argv[1]);
        QString outputName(argv[2]);

        HydroFile hydroFile(hydroFileName);
        QImage visualization = hydroFile.generateVisualization(10);
        visualization.save(outputName);

        return 0;
    }
    return 1;
}
