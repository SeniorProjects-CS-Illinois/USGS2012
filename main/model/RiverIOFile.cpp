#include "RiverIOFile.h"

RiverIOFile::RiverIOFile(QString filename) {
    
    bool comp = false;

    comp = (QPoint(1,1) == QPoint(1,1));
    

    QFile ioFile(filename);

    bool inputRead = false;
    bool outputRead = false;

    if( !ioFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        cerr << "Error opening file!" << endl;
        //TODO: Send exception
        exit(-1);
	}

    QString currLine = ioFile.readLine();
    int lineNum = 1;

    while(currLine.size() != 0) {

		if(currLine.contains("#inputs")) {
			inputRead = true;
		}
		if(currLine.contains("#outputs")) {
			outputRead = true;
		}
		QStringList numbers = currLine.split(" ");

		if(numbers.size() == 2) {
			if(inputRead && !outputRead) {
				int x = numbers[0].toInt();
				int y = numbers[1].toInt();
				QPoint pt;
				pt.setX(x);
				pt.setY(y);
				inputs.push_back(pt);
			}

			if(outputRead) {
				int x = numbers[0].toInt();
				int y = numbers[1].toInt();
				QPoint pt;
				pt.setX(x);
				pt.setY(y);
				outputs.push_back(pt);
			}
		}

		lineNum++;
		currLine = ioFile.readLine();
	}
}
