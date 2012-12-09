/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Dec 8 03:38:39 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Configuration;
    QAction *actionLoad_Configuration;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabConfig;
    QLineEdit *lineEditTSS;
    QLabel *labelOutputFreq;
    QLabel *labelErrors;
    QPushButton *pushButtonSelectPARFile;
    QLabel *labelDaysToRun;
    QTextBrowser *textBrowserErrors;
    QPushButton *pushButtonSelectDischargeFile;
    QPushButton *pushButtonAddHydroMap;
    QLabel *labelTSS;
    QListWidget *listWidgetHydroMap;
    QCheckBox *checkBoxAdjacentCells;
    QLabel *labelHydroMap;
    QLabel *labelPARFile;
    QLineEdit *lineEditOutputFreq;
    QPushButton *pushButtonSelectHydroMap;
    QLabel *labelSelectedPAR;
    QLabel *labelSelectedMap;
    QLabel *labelTimestep;
    QLabel *labelKPhyto;
    QLineEdit *lineEditKMacro;
    QLineEdit *lineEditKPhyto;
    QSlider *horizontalSliderTimestep;
    QLabel *labelTempFile;
    QPushButton *pushButtonRun;
    QPushButton *pushButtonSelectTempFile;
    QLabel *labelKMacro;
    QLabel *labelSelectedTemp;
    QLineEdit *lineEditDaysToRun;
    QPushButton *pushButtonRemoveHydroMap;
    QLabel *labelTimestepMin;
    QLabel *labelTimestepMax;
    QLabel *labelTimestepVal;
    QLineEdit *lineEditDetritus;
    QLineEdit *lineEditSeddecomp;
    QLabel *labelDecomp;
    QLabel *labelMacro;
    QLineEdit *lineEditDoc;
    QLineEdit *lineEditConsumer;
    QLabel *labelConsumer;
    QLineEdit *lineEditHerbivore;
    QLabel *labelPhyto;
    QLabel *labelDoc;
    QLabel *labelSeddecomp;
    QLineEdit *lineEditPoc;
    QLabel *labelPoc;
    QLabel *labelHerbivore;
    QLineEdit *lineEditDecomp;
    QLineEdit *lineEditMacro;
    QLineEdit *lineEditPhyto;
    QLabel *labelSedconsumer;
    QLineEdit *lineEditSedconsumer;
    QLabel *labelDetritus;
    QWidget *tabStocks;
    QLabel *labelPhytoSenescence;
    QLineEdit *lineEditPhytoSenescence;
    QLabel *labelPhytoRespiration;
    QLineEdit *lineEditPhytoRespiration;
    QLabel *labelPhytoExcretion;
    QLineEdit *lineEditPhytoExcretion;
    QLineEdit *lineEditPhytoAj;
    QLabel *labelPhytoAj;
    QLabel *labelPhytoGj;
    QLineEdit *lineEditPhytoGj;
    QLabel *labelHerbivoreAiPhyto;
    QLineEdit *lineEditHerbivoreAiPhyto;
    QLabel *labelHerbivoreAiPeri;
    QLineEdit *lineEditHerbivoreGiPhyto;
    QLineEdit *lineEditHerbivoreGiPeri;
    QLabel *labelHerbivoreGiPhyto;
    QLineEdit *lineEditHerbivoreAiPeri;
    QLabel *labelHerbivorePrefPhyto;
    QLabel *labelHerbivoreGiPeri;
    QLineEdit *lineEditHerbivorePrefPhyto;
    QLabel *labelHerbivorePrefPeri;
    QLineEdit *lineEditHerbivorePrefPeri;
    QLabel *labelHerbivorePrefWaterdecomp;
    QLineEdit *lineEditHerbivoreAiWaterdecomp;
    QLineEdit *lineEditHerbivoreAj;
    QLabel *labelHerbivoreAiWaterdecomp;
    QLineEdit *lineEditHerbivorePrefWaterdecomp;
    QLabel *labelHerbivoreGiWaterdecomp;
    QLabel *labelHerbivoreAj;
    QLineEdit *lineEditHerbivoreGiWaterdecomp;
    QLabel *labelHerbivoreGj;
    QLineEdit *lineEditHerbivoreGj;
    QLabel *labelHerbivoreEgestion;
    QLineEdit *lineEditHerbivoreRespiration;
    QLineEdit *lineEditHerbivoreSenescence;
    QLabel *labelHerbivoreRespiration;
    QLineEdit *lineEditHerbivoreEgestion;
    QLabel *labelHerbivoreExcretion;
    QLabel *labelHerbivoreSenescence;
    QLineEdit *lineEditHerbivoreExcretion;
    QLabel *labelWaterdecompAiDoc;
    QLineEdit *lineEditWaterdecompAiDoc;
    QLineEdit *lineEditWaterdecompGiDoc;
    QLabel *labelWaterdecompGiDoc;
    QLabel *labelWaterdecompPrefDoc;
    QLineEdit *lineEditWaterdecompPrefDoc;
    QLabel *labelWaterdecompRespiration;
    QLineEdit *lineEditWaterdecompAj;
    QLineEdit *lineEditWaterdecompExcretion;
    QLabel *labelWaterdecompAj;
    QLineEdit *lineEditWaterdecompRespiration;
    QLabel *labelWaterdecompGj;
    QLabel *labelWaterdecompExcretion;
    QLineEdit *lineEditWaterdecompGj;
    QLabel *labelSeddecompAiDetritus;
    QLineEdit *lineEditSeddecompAiDetritus;
    QLabel *labelWaterdecompSenescence;
    QLineEdit *lineEditSeddecompGiDetritus;
    QLineEdit *lineEditWaterdecompMax;
    QLabel *labelSeddecompGiDetritus;
    QLineEdit *lineEditWaterdecompSenescence;
    QLabel *labelSeddecompPrefDetritus;
    QLabel *labelWaterdecompMax;
    QLineEdit *lineEditSeddecompPrefDetritus;
    QLineEdit *lineEditHerbivoreMax;
    QLabel *labelHerbivoreMax;
    QLabel *labelSeddecompAj;
    QLineEdit *lineEditSeddecompAj;
    QLineEdit *lineEditSeddecompRespiration;
    QLabel *labelSeddecompGj;
    QLineEdit *lineEditSeddecompGj;
    QLabel *labelSeddecompRespiration;
    QLabel *labelSeddecompExcretion;
    QLineEdit *lineEditSeddecompExcretion;
    QLineEdit *lineEditSeddecompMax;
    QLabel *labelSeddecompSenescence;
    QLineEdit *lineEditSeddecompSenescence;
    QLabel *labelSeddecompMax;
    QLineEdit *lineEditConsumerGiSedconsumer;
    QLineEdit *lineEditConsumerGj;
    QLineEdit *lineEditConsumerAiSedconsumer;
    QLabel *labelConsumerPrefHerbivore;
    QLabel *labelConsumerGiSedconsumer;
    QLineEdit *lineEditConsumerGiHerbivore;
    QLabel *labelConsumerAj;
    QLabel *labelConsumerRespiration;
    QLineEdit *lineEditConsumerPrefSedconsumer;
    QLabel *labelConsumerGiHerbivore;
    QLineEdit *lineEditConsumerRespiration;
    QLabel *labelConsumerPrefSedconsumer;
    QLabel *labelConsumerAiSedconsumer;
    QLabel *labelConsumerAiHerbivore;
    QLineEdit *lineEditConsumerPrefHerbivore;
    QLabel *labelConsumerGj;
    QLineEdit *lineEditConsumerAiHerbivore;
    QLineEdit *lineEditConsumerAj;
    QLineEdit *lineEditSedconsumerGiDetritus;
    QLineEdit *lineEditSedconsumerGiSeddecomp;
    QLineEdit *lineEditSedconsumerAiDetritus;
    QLabel *labelConsumerEgestion;
    QLabel *labelSedconsumerGiDetritus;
    QLineEdit *lineEditConsumerSenescence;
    QLabel *labelSedconsumerAiSeddecomp;
    QLabel *labelSedconsumerPrefSeddecomp;
    QLineEdit *lineEditSedconsumerPrefDetritus;
    QLabel *labelConsumerSenescence;
    QLineEdit *lineEditSedconsumerPrefSeddecomp;
    QLabel *labelSedconsumerPrefDetritus;
    QLabel *labelSedconsumerAiDetritus;
    QLabel *labelConsumerExcretion;
    QLineEdit *lineEditConsumerEgestion;
    QLabel *labelSedconsumerGiSeddecomp;
    QLineEdit *lineEditConsumerExcretion;
    QLineEdit *lineEditSedconsumerAiSeddecomp;
    QLabel *labelSedconsumerMax;
    QLineEdit *lineEditSedconsumerSenescence;
    QLabel *labelSedconsumerAj;
    QLabel *labelSedconsumerExcretion;
    QLineEdit *lineEditSedconsumerRespiration;
    QLineEdit *lineEditSedconsumerAj;
    QLabel *labelSedconsumerGj;
    QLabel *labelSedconsumerSenescence;
    QLineEdit *lineEditSedconsumerGj;
    QLabel *labelSedconsumerRespiration;
    QLineEdit *lineEditSedconsumerMax;
    QLineEdit *lineEditSedconsumerExcretion;
    QLineEdit *lineEditConsumerMax;
    QLabel *labelConsumerMax;
    QLabel *labelMacroRespiration;
    QLineEdit *lineEditMacroSenescence;
    QLabel *labelMacroExcretion;
    QLabel *labelMacroSenescence;
    QLineEdit *lineEditMacroRespiration;
    QLineEdit *lineEditMacroExcretion;
    QLineEdit *lineEditWaterdecompPrefPoc;
    QLabel *labelWaterdecompPrefPoc;
    QLineEdit *lineEditWaterdecompAiPoc;
    QLabel *labelWaterdecompGiPoc;
    QLineEdit *lineEditWaterdecompGiPoc;
    QLabel *labelWaterdecompAiPoc;
    QLineEdit *lineEditMacroMassMax;
    QLabel *labelMacroTemp;
    QLineEdit *lineEditMacroVelocityMax;
    QLabel *labelMacroVelocityMax;
    QLineEdit *lineEditMacroGrossCoef;
    QLabel *labelMacroGrossCoef;
    QLineEdit *lineEditMacroTemp;
    QLabel *labelMacroMassMax;
    QWidget *tabOuput;
    QProgressBar *progressBar;
    QLabel *labelTimeRemaining;
    QLabel *labelTimeRemainingValue;
    QLabel *labelTimeElapsedValue;
    QLabel *labelTimeElapsed;
    QLabel *labelImageOutput;
    QPushButton *pushButtonFirstImage;
    QPushButton *pushButtonPreviousImage;
    QPushButton *pushButtonLastImage;
    QPushButton *pushButtonNextImage;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonPause;
    QLabel *labelWhichStock;
    QTextBrowser *textBrowserSelectedOutput;
    QComboBox *comboBoxWhichStock;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionSave_Configuration = new QAction(MainWindow);
        actionSave_Configuration->setObjectName(QString::fromUtf8("actionSave_Configuration"));
        actionLoad_Configuration = new QAction(MainWindow);
        actionLoad_Configuration->setObjectName(QString::fromUtf8("actionLoad_Configuration"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 850, 545));
        tabConfig = new QWidget();
        tabConfig->setObjectName(QString::fromUtf8("tabConfig"));
        lineEditTSS = new QLineEdit(tabConfig);
        lineEditTSS->setObjectName(QString::fromUtf8("lineEditTSS"));
        lineEditTSS->setGeometry(QRect(100, 360, 50, 20));
        labelOutputFreq = new QLabel(tabConfig);
        labelOutputFreq->setObjectName(QString::fromUtf8("labelOutputFreq"));
        labelOutputFreq->setGeometry(QRect(270, 380, 140, 15));
        labelErrors = new QLabel(tabConfig);
        labelErrors->setObjectName(QString::fromUtf8("labelErrors"));
        labelErrors->setGeometry(QRect(520, 200, 120, 15));
        labelErrors->setAlignment(Qt::AlignCenter);
        pushButtonSelectPARFile = new QPushButton(tabConfig);
        pushButtonSelectPARFile->setObjectName(QString::fromUtf8("pushButtonSelectPARFile"));
        pushButtonSelectPARFile->setGeometry(QRect(540, 100, 80, 20));
        labelDaysToRun = new QLabel(tabConfig);
        labelDaysToRun->setObjectName(QString::fromUtf8("labelDaysToRun"));
        labelDaysToRun->setGeometry(QRect(380, 80, 60, 15));
        textBrowserErrors = new QTextBrowser(tabConfig);
        textBrowserErrors->setObjectName(QString::fromUtf8("textBrowserErrors"));
        textBrowserErrors->setGeometry(QRect(505, 230, 150, 150));
        pushButtonSelectDischargeFile = new QPushButton(tabConfig);
        pushButtonSelectDischargeFile->setObjectName(QString::fromUtf8("pushButtonSelectDischargeFile"));
        pushButtonSelectDischargeFile->setGeometry(QRect(250, 50, 110, 20));
        pushButtonAddHydroMap = new QPushButton(tabConfig);
        pushButtonAddHydroMap->setObjectName(QString::fromUtf8("pushButtonAddHydroMap"));
        pushButtonAddHydroMap->setGeometry(QRect(305, 110, 130, 20));
        labelTSS = new QLabel(tabConfig);
        labelTSS->setObjectName(QString::fromUtf8("labelTSS"));
        labelTSS->setGeometry(QRect(30, 360, 80, 15));
        labelTSS->setAlignment(Qt::AlignCenter);
        listWidgetHydroMap = new QListWidget(tabConfig);
        listWidgetHydroMap->setObjectName(QString::fromUtf8("listWidgetHydroMap"));
        listWidgetHydroMap->setGeometry(QRect(295, 140, 150, 150));
        listWidgetHydroMap->setSelectionMode(QAbstractItemView::MultiSelection);
        checkBoxAdjacentCells = new QCheckBox(tabConfig);
        checkBoxAdjacentCells->setObjectName(QString::fromUtf8("checkBoxAdjacentCells"));
        checkBoxAdjacentCells->setGeometry(QRect(310, 340, 120, 15));
        labelHydroMap = new QLabel(tabConfig);
        labelHydroMap->setObjectName(QString::fromUtf8("labelHydroMap"));
        labelHydroMap->setGeometry(QRect(380, 60, 100, 15));
        labelHydroMap->setAlignment(Qt::AlignCenter);
        labelPARFile = new QLabel(tabConfig);
        labelPARFile->setObjectName(QString::fromUtf8("labelPARFile"));
        labelPARFile->setGeometry(QRect(520, 150, 120, 15));
        labelPARFile->setAlignment(Qt::AlignCenter);
        lineEditOutputFreq = new QLineEdit(tabConfig);
        lineEditOutputFreq->setObjectName(QString::fromUtf8("lineEditOutputFreq"));
        lineEditOutputFreq->setGeometry(QRect(420, 380, 50, 20));
        pushButtonSelectHydroMap = new QPushButton(tabConfig);
        pushButtonSelectHydroMap->setObjectName(QString::fromUtf8("pushButtonSelectHydroMap"));
        pushButtonSelectHydroMap->setGeometry(QRect(380, 10, 100, 20));
        labelSelectedPAR = new QLabel(tabConfig);
        labelSelectedPAR->setObjectName(QString::fromUtf8("labelSelectedPAR"));
        labelSelectedPAR->setGeometry(QRect(520, 130, 120, 15));
        labelSelectedPAR->setAlignment(Qt::AlignCenter);
        labelSelectedMap = new QLabel(tabConfig);
        labelSelectedMap->setObjectName(QString::fromUtf8("labelSelectedMap"));
        labelSelectedMap->setGeometry(QRect(380, 40, 100, 15));
        labelSelectedMap->setAlignment(Qt::AlignCenter);
        labelTimestep = new QLabel(tabConfig);
        labelTimestep->setObjectName(QString::fromUtf8("labelTimestep"));
        labelTimestep->setGeometry(QRect(270, 430, 50, 15));
        labelKPhyto = new QLabel(tabConfig);
        labelKPhyto->setObjectName(QString::fromUtf8("labelKPhyto"));
        labelKPhyto->setGeometry(QRect(30, 380, 80, 15));
        labelKPhyto->setAlignment(Qt::AlignCenter);
        lineEditKMacro = new QLineEdit(tabConfig);
        lineEditKMacro->setObjectName(QString::fromUtf8("lineEditKMacro"));
        lineEditKMacro->setGeometry(QRect(100, 400, 50, 20));
        lineEditKPhyto = new QLineEdit(tabConfig);
        lineEditKPhyto->setObjectName(QString::fromUtf8("lineEditKPhyto"));
        lineEditKPhyto->setGeometry(QRect(100, 380, 50, 20));
        horizontalSliderTimestep = new QSlider(tabConfig);
        horizontalSliderTimestep->setObjectName(QString::fromUtf8("horizontalSliderTimestep"));
        horizontalSliderTimestep->setGeometry(QRect(320, 430, 150, 20));
        horizontalSliderTimestep->setMinimum(1);
        horizontalSliderTimestep->setMaximum(60);
        horizontalSliderTimestep->setValue(1);
        horizontalSliderTimestep->setOrientation(Qt::Horizontal);
        horizontalSliderTimestep->setTickPosition(QSlider::NoTicks);
        horizontalSliderTimestep->setTickInterval(30);
        labelTempFile = new QLabel(tabConfig);
        labelTempFile->setObjectName(QString::fromUtf8("labelTempFile"));
        labelTempFile->setGeometry(QRect(520, 60, 120, 13));
        labelTempFile->setAlignment(Qt::AlignCenter);
        pushButtonRun = new QPushButton(tabConfig);
        pushButtonRun->setObjectName(QString::fromUtf8("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(620, 450, 50, 20));
        pushButtonSelectTempFile = new QPushButton(tabConfig);
        pushButtonSelectTempFile->setObjectName(QString::fromUtf8("pushButtonSelectTempFile"));
        pushButtonSelectTempFile->setGeometry(QRect(520, 10, 120, 20));
        labelKMacro = new QLabel(tabConfig);
        labelKMacro->setObjectName(QString::fromUtf8("labelKMacro"));
        labelKMacro->setGeometry(QRect(30, 400, 80, 15));
        labelKMacro->setAlignment(Qt::AlignCenter);
        labelSelectedTemp = new QLabel(tabConfig);
        labelSelectedTemp->setObjectName(QString::fromUtf8("labelSelectedTemp"));
        labelSelectedTemp->setGeometry(QRect(520, 40, 120, 15));
        labelSelectedTemp->setAlignment(Qt::AlignCenter);
        lineEditDaysToRun = new QLineEdit(tabConfig);
        lineEditDaysToRun->setObjectName(QString::fromUtf8("lineEditDaysToRun"));
        lineEditDaysToRun->setGeometry(QRect(440, 80, 40, 20));
        pushButtonRemoveHydroMap = new QPushButton(tabConfig);
        pushButtonRemoveHydroMap->setObjectName(QString::fromUtf8("pushButtonRemoveHydroMap"));
        pushButtonRemoveHydroMap->setGeometry(QRect(295, 300, 150, 20));
        labelTimestepMin = new QLabel(tabConfig);
        labelTimestepMin->setObjectName(QString::fromUtf8("labelTimestepMin"));
        labelTimestepMin->setGeometry(QRect(322, 450, 12, 15));
        labelTimestepMin->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelTimestepMax = new QLabel(tabConfig);
        labelTimestepMax->setObjectName(QString::fromUtf8("labelTimestepMax"));
        labelTimestepMax->setGeometry(QRect(460, 450, 12, 15));
        labelTimestepMax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelTimestepVal = new QLabel(tabConfig);
        labelTimestepVal->setObjectName(QString::fromUtf8("labelTimestepVal"));
        labelTimestepVal->setGeometry(QRect(322, 410, 12, 15));
        labelTimestepVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditDetritus = new QLineEdit(tabConfig);
        lineEditDetritus->setObjectName(QString::fromUtf8("lineEditDetritus"));
        lineEditDetritus->setGeometry(QRect(150, 180, 50, 20));
        lineEditSeddecomp = new QLineEdit(tabConfig);
        lineEditSeddecomp->setObjectName(QString::fromUtf8("lineEditSeddecomp"));
        lineEditSeddecomp->setGeometry(QRect(150, 140, 50, 20));
        labelDecomp = new QLabel(tabConfig);
        labelDecomp->setObjectName(QString::fromUtf8("labelDecomp"));
        labelDecomp->setGeometry(QRect(20, 100, 120, 15));
        labelDecomp->setAlignment(Qt::AlignCenter);
        labelMacro = new QLabel(tabConfig);
        labelMacro->setObjectName(QString::fromUtf8("labelMacro"));
        labelMacro->setGeometry(QRect(20, 40, 120, 15));
        labelMacro->setAlignment(Qt::AlignCenter);
        lineEditDoc = new QLineEdit(tabConfig);
        lineEditDoc->setObjectName(QString::fromUtf8("lineEditDoc"));
        lineEditDoc->setGeometry(QRect(150, 220, 50, 20));
        lineEditConsumer = new QLineEdit(tabConfig);
        lineEditConsumer->setObjectName(QString::fromUtf8("lineEditConsumer"));
        lineEditConsumer->setGeometry(QRect(150, 80, 50, 20));
        labelConsumer = new QLabel(tabConfig);
        labelConsumer->setObjectName(QString::fromUtf8("labelConsumer"));
        labelConsumer->setGeometry(QRect(20, 80, 120, 15));
        labelConsumer->setAlignment(Qt::AlignCenter);
        lineEditHerbivore = new QLineEdit(tabConfig);
        lineEditHerbivore->setObjectName(QString::fromUtf8("lineEditHerbivore"));
        lineEditHerbivore->setGeometry(QRect(150, 160, 50, 20));
        labelPhyto = new QLabel(tabConfig);
        labelPhyto->setObjectName(QString::fromUtf8("labelPhyto"));
        labelPhyto->setGeometry(QRect(20, 60, 120, 15));
        labelPhyto->setAlignment(Qt::AlignCenter);
        labelDoc = new QLabel(tabConfig);
        labelDoc->setObjectName(QString::fromUtf8("labelDoc"));
        labelDoc->setGeometry(QRect(20, 220, 120, 15));
        labelDoc->setAlignment(Qt::AlignCenter);
        labelSeddecomp = new QLabel(tabConfig);
        labelSeddecomp->setObjectName(QString::fromUtf8("labelSeddecomp"));
        labelSeddecomp->setGeometry(QRect(20, 140, 120, 15));
        labelSeddecomp->setAlignment(Qt::AlignCenter);
        lineEditPoc = new QLineEdit(tabConfig);
        lineEditPoc->setObjectName(QString::fromUtf8("lineEditPoc"));
        lineEditPoc->setGeometry(QRect(150, 200, 50, 20));
        labelPoc = new QLabel(tabConfig);
        labelPoc->setObjectName(QString::fromUtf8("labelPoc"));
        labelPoc->setGeometry(QRect(20, 200, 120, 15));
        labelPoc->setAlignment(Qt::AlignCenter);
        labelHerbivore = new QLabel(tabConfig);
        labelHerbivore->setObjectName(QString::fromUtf8("labelHerbivore"));
        labelHerbivore->setGeometry(QRect(20, 160, 120, 15));
        labelHerbivore->setAlignment(Qt::AlignCenter);
        lineEditDecomp = new QLineEdit(tabConfig);
        lineEditDecomp->setObjectName(QString::fromUtf8("lineEditDecomp"));
        lineEditDecomp->setGeometry(QRect(150, 100, 50, 20));
        lineEditMacro = new QLineEdit(tabConfig);
        lineEditMacro->setObjectName(QString::fromUtf8("lineEditMacro"));
        lineEditMacro->setGeometry(QRect(150, 40, 50, 20));
        lineEditPhyto = new QLineEdit(tabConfig);
        lineEditPhyto->setObjectName(QString::fromUtf8("lineEditPhyto"));
        lineEditPhyto->setGeometry(QRect(150, 60, 50, 20));
        labelSedconsumer = new QLabel(tabConfig);
        labelSedconsumer->setObjectName(QString::fromUtf8("labelSedconsumer"));
        labelSedconsumer->setGeometry(QRect(20, 120, 120, 15));
        labelSedconsumer->setAlignment(Qt::AlignCenter);
        lineEditSedconsumer = new QLineEdit(tabConfig);
        lineEditSedconsumer->setObjectName(QString::fromUtf8("lineEditSedconsumer"));
        lineEditSedconsumer->setGeometry(QRect(150, 120, 50, 20));
        labelDetritus = new QLabel(tabConfig);
        labelDetritus->setObjectName(QString::fromUtf8("labelDetritus"));
        labelDetritus->setGeometry(QRect(20, 180, 120, 15));
        labelDetritus->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tabConfig, QString());
        lineEditTSS->raise();
        labelTSS->raise();
        labelKPhyto->raise();
        lineEditKMacro->raise();
        lineEditKPhyto->raise();
        labelKMacro->raise();
        labelOutputFreq->raise();
        labelErrors->raise();
        pushButtonSelectPARFile->raise();
        labelDaysToRun->raise();
        textBrowserErrors->raise();
        pushButtonSelectDischargeFile->raise();
        pushButtonAddHydroMap->raise();
        listWidgetHydroMap->raise();
        checkBoxAdjacentCells->raise();
        labelHydroMap->raise();
        labelPARFile->raise();
        lineEditOutputFreq->raise();
        pushButtonSelectHydroMap->raise();
        labelSelectedPAR->raise();
        labelSelectedMap->raise();
        labelTimestep->raise();
        horizontalSliderTimestep->raise();
        labelTempFile->raise();
        pushButtonRun->raise();
        pushButtonSelectTempFile->raise();
        labelSelectedTemp->raise();
        lineEditDaysToRun->raise();
        pushButtonRemoveHydroMap->raise();
        labelTimestepMin->raise();
        labelTimestepMax->raise();
        labelTimestepVal->raise();
        lineEditDetritus->raise();
        lineEditSeddecomp->raise();
        labelDecomp->raise();
        labelMacro->raise();
        lineEditDoc->raise();
        lineEditConsumer->raise();
        labelConsumer->raise();
        lineEditHerbivore->raise();
        labelPhyto->raise();
        labelDoc->raise();
        labelSeddecomp->raise();
        lineEditPoc->raise();
        labelPoc->raise();
        labelHerbivore->raise();
        lineEditDecomp->raise();
        lineEditMacro->raise();
        lineEditPhyto->raise();
        labelSedconsumer->raise();
        lineEditSedconsumer->raise();
        labelDetritus->raise();
        tabStocks = new QWidget();
        tabStocks->setObjectName(QString::fromUtf8("tabStocks"));
        labelPhytoSenescence = new QLabel(tabStocks);
        labelPhytoSenescence->setObjectName(QString::fromUtf8("labelPhytoSenescence"));
        labelPhytoSenescence->setGeometry(QRect(20, 20, 120, 15));
        labelPhytoSenescence->setAlignment(Qt::AlignCenter);
        lineEditPhytoSenescence = new QLineEdit(tabStocks);
        lineEditPhytoSenescence->setObjectName(QString::fromUtf8("lineEditPhytoSenescence"));
        lineEditPhytoSenescence->setGeometry(QRect(150, 20, 50, 20));
        labelPhytoRespiration = new QLabel(tabStocks);
        labelPhytoRespiration->setObjectName(QString::fromUtf8("labelPhytoRespiration"));
        labelPhytoRespiration->setGeometry(QRect(20, 40, 120, 15));
        labelPhytoRespiration->setAlignment(Qt::AlignCenter);
        lineEditPhytoRespiration = new QLineEdit(tabStocks);
        lineEditPhytoRespiration->setObjectName(QString::fromUtf8("lineEditPhytoRespiration"));
        lineEditPhytoRespiration->setGeometry(QRect(150, 40, 50, 20));
        labelPhytoExcretion = new QLabel(tabStocks);
        labelPhytoExcretion->setObjectName(QString::fromUtf8("labelPhytoExcretion"));
        labelPhytoExcretion->setGeometry(QRect(20, 60, 120, 15));
        labelPhytoExcretion->setAlignment(Qt::AlignCenter);
        lineEditPhytoExcretion = new QLineEdit(tabStocks);
        lineEditPhytoExcretion->setObjectName(QString::fromUtf8("lineEditPhytoExcretion"));
        lineEditPhytoExcretion->setGeometry(QRect(150, 60, 50, 20));
        lineEditPhytoAj = new QLineEdit(tabStocks);
        lineEditPhytoAj->setObjectName(QString::fromUtf8("lineEditPhytoAj"));
        lineEditPhytoAj->setGeometry(QRect(150, 80, 50, 20));
        labelPhytoAj = new QLabel(tabStocks);
        labelPhytoAj->setObjectName(QString::fromUtf8("labelPhytoAj"));
        labelPhytoAj->setGeometry(QRect(20, 80, 120, 15));
        labelPhytoAj->setAlignment(Qt::AlignCenter);
        labelPhytoGj = new QLabel(tabStocks);
        labelPhytoGj->setObjectName(QString::fromUtf8("labelPhytoGj"));
        labelPhytoGj->setGeometry(QRect(20, 100, 120, 15));
        labelPhytoGj->setAlignment(Qt::AlignCenter);
        lineEditPhytoGj = new QLineEdit(tabStocks);
        lineEditPhytoGj->setObjectName(QString::fromUtf8("lineEditPhytoGj"));
        lineEditPhytoGj->setGeometry(QRect(150, 100, 50, 20));
        labelHerbivoreAiPhyto = new QLabel(tabStocks);
        labelHerbivoreAiPhyto->setObjectName(QString::fromUtf8("labelHerbivoreAiPhyto"));
        labelHerbivoreAiPhyto->setGeometry(QRect(20, 140, 120, 15));
        labelHerbivoreAiPhyto->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreAiPhyto = new QLineEdit(tabStocks);
        lineEditHerbivoreAiPhyto->setObjectName(QString::fromUtf8("lineEditHerbivoreAiPhyto"));
        lineEditHerbivoreAiPhyto->setGeometry(QRect(150, 140, 50, 20));
        labelHerbivoreAiPeri = new QLabel(tabStocks);
        labelHerbivoreAiPeri->setObjectName(QString::fromUtf8("labelHerbivoreAiPeri"));
        labelHerbivoreAiPeri->setGeometry(QRect(20, 200, 120, 15));
        labelHerbivoreAiPeri->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreGiPhyto = new QLineEdit(tabStocks);
        lineEditHerbivoreGiPhyto->setObjectName(QString::fromUtf8("lineEditHerbivoreGiPhyto"));
        lineEditHerbivoreGiPhyto->setGeometry(QRect(150, 160, 50, 20));
        lineEditHerbivoreGiPeri = new QLineEdit(tabStocks);
        lineEditHerbivoreGiPeri->setObjectName(QString::fromUtf8("lineEditHerbivoreGiPeri"));
        lineEditHerbivoreGiPeri->setGeometry(QRect(150, 220, 50, 20));
        labelHerbivoreGiPhyto = new QLabel(tabStocks);
        labelHerbivoreGiPhyto->setObjectName(QString::fromUtf8("labelHerbivoreGiPhyto"));
        labelHerbivoreGiPhyto->setGeometry(QRect(20, 160, 120, 15));
        labelHerbivoreGiPhyto->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreAiPeri = new QLineEdit(tabStocks);
        lineEditHerbivoreAiPeri->setObjectName(QString::fromUtf8("lineEditHerbivoreAiPeri"));
        lineEditHerbivoreAiPeri->setGeometry(QRect(150, 200, 50, 20));
        labelHerbivorePrefPhyto = new QLabel(tabStocks);
        labelHerbivorePrefPhyto->setObjectName(QString::fromUtf8("labelHerbivorePrefPhyto"));
        labelHerbivorePrefPhyto->setGeometry(QRect(20, 180, 120, 15));
        labelHerbivorePrefPhyto->setAlignment(Qt::AlignCenter);
        labelHerbivoreGiPeri = new QLabel(tabStocks);
        labelHerbivoreGiPeri->setObjectName(QString::fromUtf8("labelHerbivoreGiPeri"));
        labelHerbivoreGiPeri->setGeometry(QRect(20, 220, 120, 15));
        labelHerbivoreGiPeri->setAlignment(Qt::AlignCenter);
        lineEditHerbivorePrefPhyto = new QLineEdit(tabStocks);
        lineEditHerbivorePrefPhyto->setObjectName(QString::fromUtf8("lineEditHerbivorePrefPhyto"));
        lineEditHerbivorePrefPhyto->setGeometry(QRect(150, 180, 50, 20));
        labelHerbivorePrefPeri = new QLabel(tabStocks);
        labelHerbivorePrefPeri->setObjectName(QString::fromUtf8("labelHerbivorePrefPeri"));
        labelHerbivorePrefPeri->setGeometry(QRect(20, 240, 120, 15));
        labelHerbivorePrefPeri->setAlignment(Qt::AlignCenter);
        lineEditHerbivorePrefPeri = new QLineEdit(tabStocks);
        lineEditHerbivorePrefPeri->setObjectName(QString::fromUtf8("lineEditHerbivorePrefPeri"));
        lineEditHerbivorePrefPeri->setGeometry(QRect(150, 240, 50, 20));
        labelHerbivorePrefWaterdecomp = new QLabel(tabStocks);
        labelHerbivorePrefWaterdecomp->setObjectName(QString::fromUtf8("labelHerbivorePrefWaterdecomp"));
        labelHerbivorePrefWaterdecomp->setGeometry(QRect(5, 300, 145, 15));
        labelHerbivorePrefWaterdecomp->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreAiWaterdecomp = new QLineEdit(tabStocks);
        lineEditHerbivoreAiWaterdecomp->setObjectName(QString::fromUtf8("lineEditHerbivoreAiWaterdecomp"));
        lineEditHerbivoreAiWaterdecomp->setGeometry(QRect(150, 260, 50, 20));
        lineEditHerbivoreAj = new QLineEdit(tabStocks);
        lineEditHerbivoreAj->setObjectName(QString::fromUtf8("lineEditHerbivoreAj"));
        lineEditHerbivoreAj->setGeometry(QRect(150, 320, 50, 20));
        labelHerbivoreAiWaterdecomp = new QLabel(tabStocks);
        labelHerbivoreAiWaterdecomp->setObjectName(QString::fromUtf8("labelHerbivoreAiWaterdecomp"));
        labelHerbivoreAiWaterdecomp->setGeometry(QRect(10, 260, 140, 15));
        labelHerbivoreAiWaterdecomp->setAlignment(Qt::AlignCenter);
        lineEditHerbivorePrefWaterdecomp = new QLineEdit(tabStocks);
        lineEditHerbivorePrefWaterdecomp->setObjectName(QString::fromUtf8("lineEditHerbivorePrefWaterdecomp"));
        lineEditHerbivorePrefWaterdecomp->setGeometry(QRect(150, 300, 50, 20));
        labelHerbivoreGiWaterdecomp = new QLabel(tabStocks);
        labelHerbivoreGiWaterdecomp->setObjectName(QString::fromUtf8("labelHerbivoreGiWaterdecomp"));
        labelHerbivoreGiWaterdecomp->setGeometry(QRect(10, 280, 140, 15));
        labelHerbivoreGiWaterdecomp->setAlignment(Qt::AlignCenter);
        labelHerbivoreAj = new QLabel(tabStocks);
        labelHerbivoreAj->setObjectName(QString::fromUtf8("labelHerbivoreAj"));
        labelHerbivoreAj->setGeometry(QRect(20, 320, 120, 15));
        labelHerbivoreAj->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreGiWaterdecomp = new QLineEdit(tabStocks);
        lineEditHerbivoreGiWaterdecomp->setObjectName(QString::fromUtf8("lineEditHerbivoreGiWaterdecomp"));
        lineEditHerbivoreGiWaterdecomp->setGeometry(QRect(150, 280, 50, 20));
        labelHerbivoreGj = new QLabel(tabStocks);
        labelHerbivoreGj->setObjectName(QString::fromUtf8("labelHerbivoreGj"));
        labelHerbivoreGj->setGeometry(QRect(20, 340, 120, 15));
        labelHerbivoreGj->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreGj = new QLineEdit(tabStocks);
        lineEditHerbivoreGj->setObjectName(QString::fromUtf8("lineEditHerbivoreGj"));
        lineEditHerbivoreGj->setGeometry(QRect(150, 340, 50, 20));
        labelHerbivoreEgestion = new QLabel(tabStocks);
        labelHerbivoreEgestion->setObjectName(QString::fromUtf8("labelHerbivoreEgestion"));
        labelHerbivoreEgestion->setGeometry(QRect(20, 400, 120, 15));
        labelHerbivoreEgestion->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreRespiration = new QLineEdit(tabStocks);
        lineEditHerbivoreRespiration->setObjectName(QString::fromUtf8("lineEditHerbivoreRespiration"));
        lineEditHerbivoreRespiration->setGeometry(QRect(150, 360, 50, 20));
        lineEditHerbivoreSenescence = new QLineEdit(tabStocks);
        lineEditHerbivoreSenescence->setObjectName(QString::fromUtf8("lineEditHerbivoreSenescence"));
        lineEditHerbivoreSenescence->setGeometry(QRect(150, 420, 50, 20));
        labelHerbivoreRespiration = new QLabel(tabStocks);
        labelHerbivoreRespiration->setObjectName(QString::fromUtf8("labelHerbivoreRespiration"));
        labelHerbivoreRespiration->setGeometry(QRect(20, 360, 120, 15));
        labelHerbivoreRespiration->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreEgestion = new QLineEdit(tabStocks);
        lineEditHerbivoreEgestion->setObjectName(QString::fromUtf8("lineEditHerbivoreEgestion"));
        lineEditHerbivoreEgestion->setGeometry(QRect(150, 400, 50, 20));
        labelHerbivoreExcretion = new QLabel(tabStocks);
        labelHerbivoreExcretion->setObjectName(QString::fromUtf8("labelHerbivoreExcretion"));
        labelHerbivoreExcretion->setGeometry(QRect(20, 380, 120, 15));
        labelHerbivoreExcretion->setAlignment(Qt::AlignCenter);
        labelHerbivoreSenescence = new QLabel(tabStocks);
        labelHerbivoreSenescence->setObjectName(QString::fromUtf8("labelHerbivoreSenescence"));
        labelHerbivoreSenescence->setGeometry(QRect(20, 420, 120, 15));
        labelHerbivoreSenescence->setAlignment(Qt::AlignCenter);
        lineEditHerbivoreExcretion = new QLineEdit(tabStocks);
        lineEditHerbivoreExcretion->setObjectName(QString::fromUtf8("lineEditHerbivoreExcretion"));
        lineEditHerbivoreExcretion->setGeometry(QRect(150, 380, 50, 20));
        labelWaterdecompAiDoc = new QLabel(tabStocks);
        labelWaterdecompAiDoc->setObjectName(QString::fromUtf8("labelWaterdecompAiDoc"));
        labelWaterdecompAiDoc->setGeometry(QRect(220, 20, 120, 15));
        labelWaterdecompAiDoc->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompAiDoc = new QLineEdit(tabStocks);
        lineEditWaterdecompAiDoc->setObjectName(QString::fromUtf8("lineEditWaterdecompAiDoc"));
        lineEditWaterdecompAiDoc->setGeometry(QRect(350, 20, 50, 20));
        lineEditWaterdecompGiDoc = new QLineEdit(tabStocks);
        lineEditWaterdecompGiDoc->setObjectName(QString::fromUtf8("lineEditWaterdecompGiDoc"));
        lineEditWaterdecompGiDoc->setGeometry(QRect(350, 40, 50, 20));
        labelWaterdecompGiDoc = new QLabel(tabStocks);
        labelWaterdecompGiDoc->setObjectName(QString::fromUtf8("labelWaterdecompGiDoc"));
        labelWaterdecompGiDoc->setGeometry(QRect(220, 40, 120, 15));
        labelWaterdecompGiDoc->setAlignment(Qt::AlignCenter);
        labelWaterdecompPrefDoc = new QLabel(tabStocks);
        labelWaterdecompPrefDoc->setObjectName(QString::fromUtf8("labelWaterdecompPrefDoc"));
        labelWaterdecompPrefDoc->setGeometry(QRect(220, 60, 120, 15));
        labelWaterdecompPrefDoc->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompPrefDoc = new QLineEdit(tabStocks);
        lineEditWaterdecompPrefDoc->setObjectName(QString::fromUtf8("lineEditWaterdecompPrefDoc"));
        lineEditWaterdecompPrefDoc->setGeometry(QRect(350, 60, 50, 20));
        labelWaterdecompRespiration = new QLabel(tabStocks);
        labelWaterdecompRespiration->setObjectName(QString::fromUtf8("labelWaterdecompRespiration"));
        labelWaterdecompRespiration->setGeometry(QRect(215, 180, 130, 15));
        labelWaterdecompRespiration->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompAj = new QLineEdit(tabStocks);
        lineEditWaterdecompAj->setObjectName(QString::fromUtf8("lineEditWaterdecompAj"));
        lineEditWaterdecompAj->setGeometry(QRect(350, 140, 50, 20));
        lineEditWaterdecompExcretion = new QLineEdit(tabStocks);
        lineEditWaterdecompExcretion->setObjectName(QString::fromUtf8("lineEditWaterdecompExcretion"));
        lineEditWaterdecompExcretion->setGeometry(QRect(350, 200, 50, 20));
        labelWaterdecompAj = new QLabel(tabStocks);
        labelWaterdecompAj->setObjectName(QString::fromUtf8("labelWaterdecompAj"));
        labelWaterdecompAj->setGeometry(QRect(220, 140, 120, 15));
        labelWaterdecompAj->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompRespiration = new QLineEdit(tabStocks);
        lineEditWaterdecompRespiration->setObjectName(QString::fromUtf8("lineEditWaterdecompRespiration"));
        lineEditWaterdecompRespiration->setGeometry(QRect(350, 180, 50, 20));
        labelWaterdecompGj = new QLabel(tabStocks);
        labelWaterdecompGj->setObjectName(QString::fromUtf8("labelWaterdecompGj"));
        labelWaterdecompGj->setGeometry(QRect(220, 160, 120, 15));
        labelWaterdecompGj->setAlignment(Qt::AlignCenter);
        labelWaterdecompExcretion = new QLabel(tabStocks);
        labelWaterdecompExcretion->setObjectName(QString::fromUtf8("labelWaterdecompExcretion"));
        labelWaterdecompExcretion->setGeometry(QRect(220, 200, 120, 15));
        labelWaterdecompExcretion->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompGj = new QLineEdit(tabStocks);
        lineEditWaterdecompGj->setObjectName(QString::fromUtf8("lineEditWaterdecompGj"));
        lineEditWaterdecompGj->setGeometry(QRect(350, 160, 50, 20));
        labelSeddecompAiDetritus = new QLabel(tabStocks);
        labelSeddecompAiDetritus->setObjectName(QString::fromUtf8("labelSeddecompAiDetritus"));
        labelSeddecompAiDetritus->setGeometry(QRect(220, 280, 120, 15));
        labelSeddecompAiDetritus->setAlignment(Qt::AlignCenter);
        lineEditSeddecompAiDetritus = new QLineEdit(tabStocks);
        lineEditSeddecompAiDetritus->setObjectName(QString::fromUtf8("lineEditSeddecompAiDetritus"));
        lineEditSeddecompAiDetritus->setGeometry(QRect(350, 280, 50, 20));
        labelWaterdecompSenescence = new QLabel(tabStocks);
        labelWaterdecompSenescence->setObjectName(QString::fromUtf8("labelWaterdecompSenescence"));
        labelWaterdecompSenescence->setGeometry(QRect(214, 220, 131, 15));
        labelWaterdecompSenescence->setAlignment(Qt::AlignCenter);
        lineEditSeddecompGiDetritus = new QLineEdit(tabStocks);
        lineEditSeddecompGiDetritus->setObjectName(QString::fromUtf8("lineEditSeddecompGiDetritus"));
        lineEditSeddecompGiDetritus->setGeometry(QRect(350, 300, 50, 20));
        lineEditWaterdecompMax = new QLineEdit(tabStocks);
        lineEditWaterdecompMax->setObjectName(QString::fromUtf8("lineEditWaterdecompMax"));
        lineEditWaterdecompMax->setGeometry(QRect(350, 240, 50, 20));
        labelSeddecompGiDetritus = new QLabel(tabStocks);
        labelSeddecompGiDetritus->setObjectName(QString::fromUtf8("labelSeddecompGiDetritus"));
        labelSeddecompGiDetritus->setGeometry(QRect(220, 300, 120, 15));
        labelSeddecompGiDetritus->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompSenescence = new QLineEdit(tabStocks);
        lineEditWaterdecompSenescence->setObjectName(QString::fromUtf8("lineEditWaterdecompSenescence"));
        lineEditWaterdecompSenescence->setGeometry(QRect(350, 220, 50, 20));
        labelSeddecompPrefDetritus = new QLabel(tabStocks);
        labelSeddecompPrefDetritus->setObjectName(QString::fromUtf8("labelSeddecompPrefDetritus"));
        labelSeddecompPrefDetritus->setGeometry(QRect(217, 320, 125, 15));
        labelSeddecompPrefDetritus->setAlignment(Qt::AlignCenter);
        labelWaterdecompMax = new QLabel(tabStocks);
        labelWaterdecompMax->setObjectName(QString::fromUtf8("labelWaterdecompMax"));
        labelWaterdecompMax->setGeometry(QRect(220, 240, 120, 15));
        labelWaterdecompMax->setAlignment(Qt::AlignCenter);
        lineEditSeddecompPrefDetritus = new QLineEdit(tabStocks);
        lineEditSeddecompPrefDetritus->setObjectName(QString::fromUtf8("lineEditSeddecompPrefDetritus"));
        lineEditSeddecompPrefDetritus->setGeometry(QRect(350, 320, 50, 20));
        lineEditHerbivoreMax = new QLineEdit(tabStocks);
        lineEditHerbivoreMax->setObjectName(QString::fromUtf8("lineEditHerbivoreMax"));
        lineEditHerbivoreMax->setGeometry(QRect(150, 440, 50, 20));
        labelHerbivoreMax = new QLabel(tabStocks);
        labelHerbivoreMax->setObjectName(QString::fromUtf8("labelHerbivoreMax"));
        labelHerbivoreMax->setGeometry(QRect(20, 440, 120, 15));
        labelHerbivoreMax->setAlignment(Qt::AlignCenter);
        labelSeddecompAj = new QLabel(tabStocks);
        labelSeddecompAj->setObjectName(QString::fromUtf8("labelSeddecompAj"));
        labelSeddecompAj->setGeometry(QRect(220, 340, 120, 15));
        labelSeddecompAj->setAlignment(Qt::AlignCenter);
        lineEditSeddecompAj = new QLineEdit(tabStocks);
        lineEditSeddecompAj->setObjectName(QString::fromUtf8("lineEditSeddecompAj"));
        lineEditSeddecompAj->setGeometry(QRect(350, 340, 50, 20));
        lineEditSeddecompRespiration = new QLineEdit(tabStocks);
        lineEditSeddecompRespiration->setObjectName(QString::fromUtf8("lineEditSeddecompRespiration"));
        lineEditSeddecompRespiration->setGeometry(QRect(350, 380, 50, 20));
        labelSeddecompGj = new QLabel(tabStocks);
        labelSeddecompGj->setObjectName(QString::fromUtf8("labelSeddecompGj"));
        labelSeddecompGj->setGeometry(QRect(220, 360, 120, 15));
        labelSeddecompGj->setAlignment(Qt::AlignCenter);
        lineEditSeddecompGj = new QLineEdit(tabStocks);
        lineEditSeddecompGj->setObjectName(QString::fromUtf8("lineEditSeddecompGj"));
        lineEditSeddecompGj->setGeometry(QRect(350, 360, 50, 20));
        labelSeddecompRespiration = new QLabel(tabStocks);
        labelSeddecompRespiration->setObjectName(QString::fromUtf8("labelSeddecompRespiration"));
        labelSeddecompRespiration->setGeometry(QRect(220, 380, 120, 15));
        labelSeddecompRespiration->setAlignment(Qt::AlignCenter);
        labelSeddecompExcretion = new QLabel(tabStocks);
        labelSeddecompExcretion->setObjectName(QString::fromUtf8("labelSeddecompExcretion"));
        labelSeddecompExcretion->setGeometry(QRect(220, 400, 120, 15));
        labelSeddecompExcretion->setAlignment(Qt::AlignCenter);
        lineEditSeddecompExcretion = new QLineEdit(tabStocks);
        lineEditSeddecompExcretion->setObjectName(QString::fromUtf8("lineEditSeddecompExcretion"));
        lineEditSeddecompExcretion->setGeometry(QRect(350, 400, 50, 20));
        lineEditSeddecompMax = new QLineEdit(tabStocks);
        lineEditSeddecompMax->setObjectName(QString::fromUtf8("lineEditSeddecompMax"));
        lineEditSeddecompMax->setGeometry(QRect(350, 440, 50, 20));
        labelSeddecompSenescence = new QLabel(tabStocks);
        labelSeddecompSenescence->setObjectName(QString::fromUtf8("labelSeddecompSenescence"));
        labelSeddecompSenescence->setGeometry(QRect(220, 420, 120, 15));
        labelSeddecompSenescence->setAlignment(Qt::AlignCenter);
        lineEditSeddecompSenescence = new QLineEdit(tabStocks);
        lineEditSeddecompSenescence->setObjectName(QString::fromUtf8("lineEditSeddecompSenescence"));
        lineEditSeddecompSenescence->setGeometry(QRect(350, 420, 50, 20));
        labelSeddecompMax = new QLabel(tabStocks);
        labelSeddecompMax->setObjectName(QString::fromUtf8("labelSeddecompMax"));
        labelSeddecompMax->setGeometry(QRect(220, 440, 120, 15));
        labelSeddecompMax->setAlignment(Qt::AlignCenter);
        lineEditConsumerGiSedconsumer = new QLineEdit(tabStocks);
        lineEditConsumerGiSedconsumer->setObjectName(QString::fromUtf8("lineEditConsumerGiSedconsumer"));
        lineEditConsumerGiSedconsumer->setGeometry(QRect(560, 100, 50, 20));
        lineEditConsumerGj = new QLineEdit(tabStocks);
        lineEditConsumerGj->setObjectName(QString::fromUtf8("lineEditConsumerGj"));
        lineEditConsumerGj->setGeometry(QRect(560, 160, 50, 20));
        lineEditConsumerAiSedconsumer = new QLineEdit(tabStocks);
        lineEditConsumerAiSedconsumer->setObjectName(QString::fromUtf8("lineEditConsumerAiSedconsumer"));
        lineEditConsumerAiSedconsumer->setGeometry(QRect(560, 80, 50, 20));
        labelConsumerPrefHerbivore = new QLabel(tabStocks);
        labelConsumerPrefHerbivore->setObjectName(QString::fromUtf8("labelConsumerPrefHerbivore"));
        labelConsumerPrefHerbivore->setGeometry(QRect(428, 60, 125, 15));
        labelConsumerPrefHerbivore->setAlignment(Qt::AlignCenter);
        labelConsumerGiSedconsumer = new QLabel(tabStocks);
        labelConsumerGiSedconsumer->setObjectName(QString::fromUtf8("labelConsumerGiSedconsumer"));
        labelConsumerGiSedconsumer->setGeometry(QRect(422, 100, 135, 15));
        labelConsumerGiSedconsumer->setAlignment(Qt::AlignCenter);
        lineEditConsumerGiHerbivore = new QLineEdit(tabStocks);
        lineEditConsumerGiHerbivore->setObjectName(QString::fromUtf8("lineEditConsumerGiHerbivore"));
        lineEditConsumerGiHerbivore->setGeometry(QRect(560, 40, 50, 20));
        labelConsumerAj = new QLabel(tabStocks);
        labelConsumerAj->setObjectName(QString::fromUtf8("labelConsumerAj"));
        labelConsumerAj->setGeometry(QRect(430, 140, 120, 15));
        labelConsumerAj->setAlignment(Qt::AlignCenter);
        labelConsumerRespiration = new QLabel(tabStocks);
        labelConsumerRespiration->setObjectName(QString::fromUtf8("labelConsumerRespiration"));
        labelConsumerRespiration->setGeometry(QRect(430, 180, 120, 15));
        labelConsumerRespiration->setAlignment(Qt::AlignCenter);
        lineEditConsumerPrefSedconsumer = new QLineEdit(tabStocks);
        lineEditConsumerPrefSedconsumer->setObjectName(QString::fromUtf8("lineEditConsumerPrefSedconsumer"));
        lineEditConsumerPrefSedconsumer->setGeometry(QRect(560, 120, 50, 20));
        labelConsumerGiHerbivore = new QLabel(tabStocks);
        labelConsumerGiHerbivore->setObjectName(QString::fromUtf8("labelConsumerGiHerbivore"));
        labelConsumerGiHerbivore->setGeometry(QRect(430, 40, 120, 15));
        labelConsumerGiHerbivore->setAlignment(Qt::AlignCenter);
        lineEditConsumerRespiration = new QLineEdit(tabStocks);
        lineEditConsumerRespiration->setObjectName(QString::fromUtf8("lineEditConsumerRespiration"));
        lineEditConsumerRespiration->setGeometry(QRect(560, 180, 50, 20));
        labelConsumerPrefSedconsumer = new QLabel(tabStocks);
        labelConsumerPrefSedconsumer->setObjectName(QString::fromUtf8("labelConsumerPrefSedconsumer"));
        labelConsumerPrefSedconsumer->setGeometry(QRect(417, 120, 142, 15));
        labelConsumerPrefSedconsumer->setAlignment(Qt::AlignCenter);
        labelConsumerAiSedconsumer = new QLabel(tabStocks);
        labelConsumerAiSedconsumer->setObjectName(QString::fromUtf8("labelConsumerAiSedconsumer"));
        labelConsumerAiSedconsumer->setGeometry(QRect(422, 80, 135, 15));
        labelConsumerAiSedconsumer->setAlignment(Qt::AlignCenter);
        labelConsumerAiHerbivore = new QLabel(tabStocks);
        labelConsumerAiHerbivore->setObjectName(QString::fromUtf8("labelConsumerAiHerbivore"));
        labelConsumerAiHerbivore->setGeometry(QRect(430, 20, 120, 15));
        labelConsumerAiHerbivore->setAlignment(Qt::AlignCenter);
        lineEditConsumerPrefHerbivore = new QLineEdit(tabStocks);
        lineEditConsumerPrefHerbivore->setObjectName(QString::fromUtf8("lineEditConsumerPrefHerbivore"));
        lineEditConsumerPrefHerbivore->setGeometry(QRect(560, 60, 50, 20));
        labelConsumerGj = new QLabel(tabStocks);
        labelConsumerGj->setObjectName(QString::fromUtf8("labelConsumerGj"));
        labelConsumerGj->setGeometry(QRect(430, 160, 120, 15));
        labelConsumerGj->setAlignment(Qt::AlignCenter);
        lineEditConsumerAiHerbivore = new QLineEdit(tabStocks);
        lineEditConsumerAiHerbivore->setObjectName(QString::fromUtf8("lineEditConsumerAiHerbivore"));
        lineEditConsumerAiHerbivore->setGeometry(QRect(560, 20, 50, 20));
        lineEditConsumerAj = new QLineEdit(tabStocks);
        lineEditConsumerAj->setObjectName(QString::fromUtf8("lineEditConsumerAj"));
        lineEditConsumerAj->setGeometry(QRect(560, 140, 50, 20));
        lineEditSedconsumerGiDetritus = new QLineEdit(tabStocks);
        lineEditSedconsumerGiDetritus->setObjectName(QString::fromUtf8("lineEditSedconsumerGiDetritus"));
        lineEditSedconsumerGiDetritus->setGeometry(QRect(760, 40, 50, 20));
        lineEditSedconsumerGiSeddecomp = new QLineEdit(tabStocks);
        lineEditSedconsumerGiSeddecomp->setObjectName(QString::fromUtf8("lineEditSedconsumerGiSeddecomp"));
        lineEditSedconsumerGiSeddecomp->setGeometry(QRect(760, 100, 50, 20));
        lineEditSedconsumerAiDetritus = new QLineEdit(tabStocks);
        lineEditSedconsumerAiDetritus->setObjectName(QString::fromUtf8("lineEditSedconsumerAiDetritus"));
        lineEditSedconsumerAiDetritus->setGeometry(QRect(760, 20, 50, 20));
        labelConsumerEgestion = new QLabel(tabStocks);
        labelConsumerEgestion->setObjectName(QString::fromUtf8("labelConsumerEgestion"));
        labelConsumerEgestion->setGeometry(QRect(430, 240, 120, 15));
        labelConsumerEgestion->setAlignment(Qt::AlignCenter);
        labelSedconsumerGiDetritus = new QLabel(tabStocks);
        labelSedconsumerGiDetritus->setObjectName(QString::fromUtf8("labelSedconsumerGiDetritus"));
        labelSedconsumerGiDetritus->setGeometry(QRect(629, 40, 122, 15));
        labelSedconsumerGiDetritus->setAlignment(Qt::AlignCenter);
        lineEditConsumerSenescence = new QLineEdit(tabStocks);
        lineEditConsumerSenescence->setObjectName(QString::fromUtf8("lineEditConsumerSenescence"));
        lineEditConsumerSenescence->setGeometry(QRect(560, 220, 50, 20));
        labelSedconsumerAiSeddecomp = new QLabel(tabStocks);
        labelSedconsumerAiSeddecomp->setObjectName(QString::fromUtf8("labelSedconsumerAiSeddecomp"));
        labelSedconsumerAiSeddecomp->setGeometry(QRect(620, 80, 140, 15));
        labelSedconsumerAiSeddecomp->setAlignment(Qt::AlignCenter);
        labelSedconsumerPrefSeddecomp = new QLabel(tabStocks);
        labelSedconsumerPrefSeddecomp->setObjectName(QString::fromUtf8("labelSedconsumerPrefSeddecomp"));
        labelSedconsumerPrefSeddecomp->setGeometry(QRect(612, 120, 150, 15));
        labelSedconsumerPrefSeddecomp->setAlignment(Qt::AlignCenter);
        lineEditSedconsumerPrefDetritus = new QLineEdit(tabStocks);
        lineEditSedconsumerPrefDetritus->setObjectName(QString::fromUtf8("lineEditSedconsumerPrefDetritus"));
        lineEditSedconsumerPrefDetritus->setGeometry(QRect(760, 60, 50, 20));
        labelConsumerSenescence = new QLabel(tabStocks);
        labelConsumerSenescence->setObjectName(QString::fromUtf8("labelConsumerSenescence"));
        labelConsumerSenescence->setGeometry(QRect(430, 220, 120, 15));
        labelConsumerSenescence->setAlignment(Qt::AlignCenter);
        lineEditSedconsumerPrefSeddecomp = new QLineEdit(tabStocks);
        lineEditSedconsumerPrefSeddecomp->setObjectName(QString::fromUtf8("lineEditSedconsumerPrefSeddecomp"));
        lineEditSedconsumerPrefSeddecomp->setGeometry(QRect(760, 120, 50, 20));
        labelSedconsumerPrefDetritus = new QLabel(tabStocks);
        labelSedconsumerPrefDetritus->setObjectName(QString::fromUtf8("labelSedconsumerPrefDetritus"));
        labelSedconsumerPrefDetritus->setGeometry(QRect(624, 60, 132, 15));
        labelSedconsumerPrefDetritus->setAlignment(Qt::AlignCenter);
        labelSedconsumerAiDetritus = new QLabel(tabStocks);
        labelSedconsumerAiDetritus->setObjectName(QString::fromUtf8("labelSedconsumerAiDetritus"));
        labelSedconsumerAiDetritus->setGeometry(QRect(629, 20, 122, 15));
        labelSedconsumerAiDetritus->setAlignment(Qt::AlignCenter);
        labelConsumerExcretion = new QLabel(tabStocks);
        labelConsumerExcretion->setObjectName(QString::fromUtf8("labelConsumerExcretion"));
        labelConsumerExcretion->setGeometry(QRect(430, 200, 120, 15));
        labelConsumerExcretion->setAlignment(Qt::AlignCenter);
        lineEditConsumerEgestion = new QLineEdit(tabStocks);
        lineEditConsumerEgestion->setObjectName(QString::fromUtf8("lineEditConsumerEgestion"));
        lineEditConsumerEgestion->setGeometry(QRect(560, 240, 50, 20));
        labelSedconsumerGiSeddecomp = new QLabel(tabStocks);
        labelSedconsumerGiSeddecomp->setObjectName(QString::fromUtf8("labelSedconsumerGiSeddecomp"));
        labelSedconsumerGiSeddecomp->setGeometry(QRect(620, 100, 140, 15));
        labelSedconsumerGiSeddecomp->setAlignment(Qt::AlignCenter);
        lineEditConsumerExcretion = new QLineEdit(tabStocks);
        lineEditConsumerExcretion->setObjectName(QString::fromUtf8("lineEditConsumerExcretion"));
        lineEditConsumerExcretion->setGeometry(QRect(560, 200, 50, 20));
        lineEditSedconsumerAiSeddecomp = new QLineEdit(tabStocks);
        lineEditSedconsumerAiSeddecomp->setObjectName(QString::fromUtf8("lineEditSedconsumerAiSeddecomp"));
        lineEditSedconsumerAiSeddecomp->setGeometry(QRect(760, 80, 50, 20));
        labelSedconsumerMax = new QLabel(tabStocks);
        labelSedconsumerMax->setObjectName(QString::fromUtf8("labelSedconsumerMax"));
        labelSedconsumerMax->setGeometry(QRect(630, 240, 120, 15));
        labelSedconsumerMax->setAlignment(Qt::AlignCenter);
        lineEditSedconsumerSenescence = new QLineEdit(tabStocks);
        lineEditSedconsumerSenescence->setObjectName(QString::fromUtf8("lineEditSedconsumerSenescence"));
        lineEditSedconsumerSenescence->setGeometry(QRect(760, 220, 50, 20));
        labelSedconsumerAj = new QLabel(tabStocks);
        labelSedconsumerAj->setObjectName(QString::fromUtf8("labelSedconsumerAj"));
        labelSedconsumerAj->setGeometry(QRect(630, 140, 120, 15));
        labelSedconsumerAj->setAlignment(Qt::AlignCenter);
        labelSedconsumerExcretion = new QLabel(tabStocks);
        labelSedconsumerExcretion->setObjectName(QString::fromUtf8("labelSedconsumerExcretion"));
        labelSedconsumerExcretion->setGeometry(QRect(630, 200, 120, 15));
        labelSedconsumerExcretion->setAlignment(Qt::AlignCenter);
        lineEditSedconsumerRespiration = new QLineEdit(tabStocks);
        lineEditSedconsumerRespiration->setObjectName(QString::fromUtf8("lineEditSedconsumerRespiration"));
        lineEditSedconsumerRespiration->setGeometry(QRect(760, 180, 50, 20));
        lineEditSedconsumerAj = new QLineEdit(tabStocks);
        lineEditSedconsumerAj->setObjectName(QString::fromUtf8("lineEditSedconsumerAj"));
        lineEditSedconsumerAj->setGeometry(QRect(760, 140, 50, 20));
        labelSedconsumerGj = new QLabel(tabStocks);
        labelSedconsumerGj->setObjectName(QString::fromUtf8("labelSedconsumerGj"));
        labelSedconsumerGj->setGeometry(QRect(630, 160, 120, 15));
        labelSedconsumerGj->setAlignment(Qt::AlignCenter);
        labelSedconsumerSenescence = new QLabel(tabStocks);
        labelSedconsumerSenescence->setObjectName(QString::fromUtf8("labelSedconsumerSenescence"));
        labelSedconsumerSenescence->setGeometry(QRect(625, 220, 130, 15));
        labelSedconsumerSenescence->setAlignment(Qt::AlignCenter);
        lineEditSedconsumerGj = new QLineEdit(tabStocks);
        lineEditSedconsumerGj->setObjectName(QString::fromUtf8("lineEditSedconsumerGj"));
        lineEditSedconsumerGj->setGeometry(QRect(760, 160, 50, 20));
        labelSedconsumerRespiration = new QLabel(tabStocks);
        labelSedconsumerRespiration->setObjectName(QString::fromUtf8("labelSedconsumerRespiration"));
        labelSedconsumerRespiration->setGeometry(QRect(628, 180, 125, 15));
        labelSedconsumerRespiration->setAlignment(Qt::AlignCenter);
        lineEditSedconsumerMax = new QLineEdit(tabStocks);
        lineEditSedconsumerMax->setObjectName(QString::fromUtf8("lineEditSedconsumerMax"));
        lineEditSedconsumerMax->setGeometry(QRect(760, 240, 50, 20));
        lineEditSedconsumerExcretion = new QLineEdit(tabStocks);
        lineEditSedconsumerExcretion->setObjectName(QString::fromUtf8("lineEditSedconsumerExcretion"));
        lineEditSedconsumerExcretion->setGeometry(QRect(760, 200, 50, 20));
        lineEditConsumerMax = new QLineEdit(tabStocks);
        lineEditConsumerMax->setObjectName(QString::fromUtf8("lineEditConsumerMax"));
        lineEditConsumerMax->setGeometry(QRect(560, 260, 50, 20));
        labelConsumerMax = new QLabel(tabStocks);
        labelConsumerMax->setObjectName(QString::fromUtf8("labelConsumerMax"));
        labelConsumerMax->setGeometry(QRect(430, 260, 120, 15));
        labelConsumerMax->setAlignment(Qt::AlignCenter);
        labelMacroRespiration = new QLabel(tabStocks);
        labelMacroRespiration->setObjectName(QString::fromUtf8("labelMacroRespiration"));
        labelMacroRespiration->setGeometry(QRect(430, 320, 120, 15));
        labelMacroRespiration->setAlignment(Qt::AlignCenter);
        lineEditMacroSenescence = new QLineEdit(tabStocks);
        lineEditMacroSenescence->setObjectName(QString::fromUtf8("lineEditMacroSenescence"));
        lineEditMacroSenescence->setGeometry(QRect(560, 300, 50, 20));
        labelMacroExcretion = new QLabel(tabStocks);
        labelMacroExcretion->setObjectName(QString::fromUtf8("labelMacroExcretion"));
        labelMacroExcretion->setGeometry(QRect(430, 340, 120, 15));
        labelMacroExcretion->setAlignment(Qt::AlignCenter);
        labelMacroSenescence = new QLabel(tabStocks);
        labelMacroSenescence->setObjectName(QString::fromUtf8("labelMacroSenescence"));
        labelMacroSenescence->setGeometry(QRect(430, 300, 120, 15));
        labelMacroSenescence->setAlignment(Qt::AlignCenter);
        lineEditMacroRespiration = new QLineEdit(tabStocks);
        lineEditMacroRespiration->setObjectName(QString::fromUtf8("lineEditMacroRespiration"));
        lineEditMacroRespiration->setGeometry(QRect(560, 320, 50, 20));
        lineEditMacroExcretion = new QLineEdit(tabStocks);
        lineEditMacroExcretion->setObjectName(QString::fromUtf8("lineEditMacroExcretion"));
        lineEditMacroExcretion->setGeometry(QRect(560, 340, 50, 20));
        lineEditWaterdecompPrefPoc = new QLineEdit(tabStocks);
        lineEditWaterdecompPrefPoc->setObjectName(QString::fromUtf8("lineEditWaterdecompPrefPoc"));
        lineEditWaterdecompPrefPoc->setGeometry(QRect(350, 120, 50, 20));
        labelWaterdecompPrefPoc = new QLabel(tabStocks);
        labelWaterdecompPrefPoc->setObjectName(QString::fromUtf8("labelWaterdecompPrefPoc"));
        labelWaterdecompPrefPoc->setGeometry(QRect(220, 120, 120, 15));
        labelWaterdecompPrefPoc->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompAiPoc = new QLineEdit(tabStocks);
        lineEditWaterdecompAiPoc->setObjectName(QString::fromUtf8("lineEditWaterdecompAiPoc"));
        lineEditWaterdecompAiPoc->setGeometry(QRect(350, 80, 50, 20));
        labelWaterdecompGiPoc = new QLabel(tabStocks);
        labelWaterdecompGiPoc->setObjectName(QString::fromUtf8("labelWaterdecompGiPoc"));
        labelWaterdecompGiPoc->setGeometry(QRect(220, 100, 120, 15));
        labelWaterdecompGiPoc->setAlignment(Qt::AlignCenter);
        lineEditWaterdecompGiPoc = new QLineEdit(tabStocks);
        lineEditWaterdecompGiPoc->setObjectName(QString::fromUtf8("lineEditWaterdecompGiPoc"));
        lineEditWaterdecompGiPoc->setGeometry(QRect(350, 100, 50, 20));
        labelWaterdecompAiPoc = new QLabel(tabStocks);
        labelWaterdecompAiPoc->setObjectName(QString::fromUtf8("labelWaterdecompAiPoc"));
        labelWaterdecompAiPoc->setGeometry(QRect(220, 80, 120, 15));
        labelWaterdecompAiPoc->setAlignment(Qt::AlignCenter);
        lineEditMacroMassMax = new QLineEdit(tabStocks);
        lineEditMacroMassMax->setObjectName(QString::fromUtf8("lineEditMacroMassMax"));
        lineEditMacroMassMax->setGeometry(QRect(560, 400, 50, 20));
        labelMacroTemp = new QLabel(tabStocks);
        labelMacroTemp->setObjectName(QString::fromUtf8("labelMacroTemp"));
        labelMacroTemp->setGeometry(QRect(430, 360, 120, 15));
        labelMacroTemp->setAlignment(Qt::AlignCenter);
        lineEditMacroVelocityMax = new QLineEdit(tabStocks);
        lineEditMacroVelocityMax->setObjectName(QString::fromUtf8("lineEditMacroVelocityMax"));
        lineEditMacroVelocityMax->setGeometry(QRect(560, 420, 50, 20));
        labelMacroVelocityMax = new QLabel(tabStocks);
        labelMacroVelocityMax->setObjectName(QString::fromUtf8("labelMacroVelocityMax"));
        labelMacroVelocityMax->setGeometry(QRect(430, 420, 120, 15));
        labelMacroVelocityMax->setAlignment(Qt::AlignCenter);
        lineEditMacroGrossCoef = new QLineEdit(tabStocks);
        lineEditMacroGrossCoef->setObjectName(QString::fromUtf8("lineEditMacroGrossCoef"));
        lineEditMacroGrossCoef->setGeometry(QRect(560, 380, 50, 20));
        labelMacroGrossCoef = new QLabel(tabStocks);
        labelMacroGrossCoef->setObjectName(QString::fromUtf8("labelMacroGrossCoef"));
        labelMacroGrossCoef->setGeometry(QRect(430, 380, 120, 15));
        labelMacroGrossCoef->setAlignment(Qt::AlignCenter);
        lineEditMacroTemp = new QLineEdit(tabStocks);
        lineEditMacroTemp->setObjectName(QString::fromUtf8("lineEditMacroTemp"));
        lineEditMacroTemp->setGeometry(QRect(560, 360, 50, 20));
        labelMacroMassMax = new QLabel(tabStocks);
        labelMacroMassMax->setObjectName(QString::fromUtf8("labelMacroMassMax"));
        labelMacroMassMax->setGeometry(QRect(430, 400, 120, 15));
        labelMacroMassMax->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tabStocks, QString());
        tabOuput = new QWidget();
        tabOuput->setObjectName(QString::fromUtf8("tabOuput"));
        progressBar = new QProgressBar(tabOuput);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(100, 450, 650, 20));
        progressBar->setValue(0);
        labelTimeRemaining = new QLabel(tabOuput);
        labelTimeRemaining->setObjectName(QString::fromUtf8("labelTimeRemaining"));
        labelTimeRemaining->setGeometry(QRect(500, 430, 80, 15));
        labelTimeRemainingValue = new QLabel(tabOuput);
        labelTimeRemainingValue->setObjectName(QString::fromUtf8("labelTimeRemainingValue"));
        labelTimeRemainingValue->setGeometry(QRect(590, 430, 50, 15));
        labelTimeElapsedValue = new QLabel(tabOuput);
        labelTimeElapsedValue->setObjectName(QString::fromUtf8("labelTimeElapsedValue"));
        labelTimeElapsedValue->setGeometry(QRect(270, 430, 50, 15));
        labelTimeElapsed = new QLabel(tabOuput);
        labelTimeElapsed->setObjectName(QString::fromUtf8("labelTimeElapsed"));
        labelTimeElapsed->setGeometry(QRect(190, 430, 70, 15));
        labelImageOutput = new QLabel(tabOuput);
        labelImageOutput->setObjectName(QString::fromUtf8("labelImageOutput"));
        labelImageOutput->setGeometry(QRect(15, 60, 400, 300));
        labelImageOutput->setAlignment(Qt::AlignCenter);
        pushButtonFirstImage = new QPushButton(tabOuput);
        pushButtonFirstImage->setObjectName(QString::fromUtf8("pushButtonFirstImage"));
        pushButtonFirstImage->setGeometry(QRect(60, 375, 30, 20));
        pushButtonPreviousImage = new QPushButton(tabOuput);
        pushButtonPreviousImage->setObjectName(QString::fromUtf8("pushButtonPreviousImage"));
        pushButtonPreviousImage->setGeometry(QRect(100, 375, 30, 20));
        pushButtonLastImage = new QPushButton(tabOuput);
        pushButtonLastImage->setObjectName(QString::fromUtf8("pushButtonLastImage"));
        pushButtonLastImage->setGeometry(QRect(340, 375, 30, 20));
        pushButtonNextImage = new QPushButton(tabOuput);
        pushButtonNextImage->setObjectName(QString::fromUtf8("pushButtonNextImage"));
        pushButtonNextImage->setGeometry(QRect(300, 375, 30, 20));
        pushButtonStop = new QPushButton(tabOuput);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(155, 375, 50, 20));
        pushButtonPause = new QPushButton(tabOuput);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setGeometry(QRect(225, 375, 50, 20));
        labelWhichStock = new QLabel(tabOuput);
        labelWhichStock->setObjectName(QString::fromUtf8("labelWhichStock"));
        labelWhichStock->setGeometry(QRect(15, 10, 100, 20));
        labelWhichStock->setAlignment(Qt::AlignCenter);
        textBrowserSelectedOutput = new QTextBrowser(tabOuput);
        textBrowserSelectedOutput->setObjectName(QString::fromUtf8("textBrowserSelectedOutput"));
        textBrowserSelectedOutput->setGeometry(QRect(510, 70, 241, 241));
        comboBoxWhichStock = new QComboBox(tabOuput);
        comboBoxWhichStock->setObjectName(QString::fromUtf8("comboBoxWhichStock"));
        comboBoxWhichStock->setGeometry(QRect(20, 30, 100, 20));
        tabWidget->addTab(tabOuput, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave_Configuration);
        menuFile->addAction(actionLoad_Configuration);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonSelectHydroMap, SIGNAL(clicked()), MainWindow, SLOT(selectHydroMapClicked()));
        QObject::connect(pushButtonAddHydroMap, SIGNAL(clicked()), MainWindow, SLOT(addHydroMapClicked()));
        QObject::connect(pushButtonRemoveHydroMap, SIGNAL(clicked()), MainWindow, SLOT(removeHydroMapClicked()));
        QObject::connect(pushButtonSelectTempFile, SIGNAL(clicked()), MainWindow, SLOT(selectTemperatureFileClicked()));
        QObject::connect(pushButtonSelectPARFile, SIGNAL(clicked()), MainWindow, SLOT(selectPARFileClicked()));
        QObject::connect(pushButtonRun, SIGNAL(clicked()), MainWindow, SLOT(runClicked()));
        QObject::connect(horizontalSliderTimestep, SIGNAL(sliderMoved(int)), MainWindow, SLOT(timestepUpdate(int)));
        QObject::connect(actionSave_Configuration, SIGNAL(triggered()), MainWindow, SLOT(saveConfiguration()));
        QObject::connect(actionLoad_Configuration, SIGNAL(triggered()), MainWindow, SLOT(loadConfiguration()));
        QObject::connect(pushButtonSelectDischargeFile, SIGNAL(clicked()), MainWindow, SLOT(selectDischargeFileClicked()));
        QObject::connect(horizontalSliderTimestep, SIGNAL(valueChanged(int)), MainWindow, SLOT(timestepUpdate(int)));
        QObject::connect(comboBoxWhichStock, SIGNAL(currentIndexChanged(QString)), MainWindow, SLOT(whichstockChanged(QString)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSave_Configuration->setText(QApplication::translate("MainWindow", "Save Configuration", 0, QApplication::UnicodeUTF8));
        actionLoad_Configuration->setText(QApplication::translate("MainWindow", "Load Configuration", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tabConfig->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        lineEditTSS->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelOutputFreq->setToolTip(QApplication::translate("MainWindow", "The rate at which images should be output", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelOutputFreq->setText(QApplication::translate("MainWindow", "Output Frequency (# Days):", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelErrors->setToolTip(QApplication::translate("MainWindow", "Errors with model displayed below", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelErrors->setText(QApplication::translate("MainWindow", "Errors:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonSelectPARFile->setToolTip(QApplication::translate("MainWindow", "Push to select a PAR file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonSelectPARFile->setText(QApplication::translate("MainWindow", "Select PAR File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDaysToRun->setToolTip(QApplication::translate("MainWindow", "Number of days to simulate this model", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelDaysToRun->setText(QApplication::translate("MainWindow", "Days to run:", 0, QApplication::UnicodeUTF8));
        textBrowserErrors->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">None</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonSelectDischargeFile->setToolTip(QApplication::translate("MainWindow", "Push to select a discharge file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonSelectDischargeFile->setText(QApplication::translate("MainWindow", "Select Discharge File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonAddHydroMap->setToolTip(QApplication::translate("MainWindow", "Push to add current hydro map", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonAddHydroMap->setText(QApplication::translate("MainWindow", "Add Hydro Map to Model", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelTSS->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelTSS->setText(QApplication::translate("MainWindow", "TSS:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBoxAdjacentCells->setToolTip(QApplication::translate("MainWindow", "Check this box if you want carbon flows to be limited to only adjacent cells", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBoxAdjacentCells->setText(QApplication::translate("MainWindow", "Adjacent Cells Only?", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHydroMap->setToolTip(QApplication::translate("MainWindow", "No file selected", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHydroMap->setText(QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPARFile->setToolTip(QApplication::translate("MainWindow", "No file selected", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPARFile->setText(QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditOutputFreq->setToolTip(QApplication::translate("MainWindow", "Positive integer, # of days", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditOutputFreq->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonSelectHydroMap->setToolTip(QApplication::translate("MainWindow", "Push to select a hydro map", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonSelectHydroMap->setText(QApplication::translate("MainWindow", "Select Hydro Map", 0, QApplication::UnicodeUTF8));
        labelSelectedPAR->setText(QApplication::translate("MainWindow", "Selected PAR:", 0, QApplication::UnicodeUTF8));
        labelSelectedMap->setText(QApplication::translate("MainWindow", "Selected Map:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelTimestep->setToolTip(QApplication::translate("MainWindow", "Granularity of calculation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelTimestep->setText(QApplication::translate("MainWindow", "Timestep:", 0, QApplication::UnicodeUTF8));
        labelKPhyto->setText(QApplication::translate("MainWindow", "K-Phyto:", 0, QApplication::UnicodeUTF8));
        lineEditKMacro->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
        lineEditKPhyto->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        horizontalSliderTimestep->setToolTip(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelTempFile->setToolTip(QApplication::translate("MainWindow", "No file selected", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelTempFile->setText(QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QApplication::translate("MainWindow", "Push to run the model", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonSelectTempFile->setToolTip(QApplication::translate("MainWindow", "Push to select a temperature file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonSelectTempFile->setText(QApplication::translate("MainWindow", "Select Temperature File", 0, QApplication::UnicodeUTF8));
        labelKMacro->setText(QApplication::translate("MainWindow", "K-Macro:", 0, QApplication::UnicodeUTF8));
        labelSelectedTemp->setText(QApplication::translate("MainWindow", "Selected Temperature:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditDaysToRun->setToolTip(QApplication::translate("MainWindow", "Positive integer, # of days", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditDaysToRun->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonRemoveHydroMap->setToolTip(QApplication::translate("MainWindow", "Push to remove selected hydro map(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonRemoveHydroMap->setText(QApplication::translate("MainWindow", "Remove Selected Hydro Map", 0, QApplication::UnicodeUTF8));
        labelTimestepMin->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        labelTimestepMax->setText(QApplication::translate("MainWindow", "60", 0, QApplication::UnicodeUTF8));
        labelTimestepVal->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        lineEditDetritus->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
        lineEditSeddecomp->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDecomp->setToolTip(QApplication::translate("MainWindow", "Base decomposer stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelDecomp->setText(QApplication::translate("MainWindow", "Decomp:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelMacro->setToolTip(QApplication::translate("MainWindow", "Base macrophyte stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelMacro->setText(QApplication::translate("MainWindow", "Macro:", 0, QApplication::UnicodeUTF8));
        lineEditDoc->setText(QApplication::translate("MainWindow", "0.1", 0, QApplication::UnicodeUTF8));
        lineEditConsumer->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumer->setToolTip(QApplication::translate("MainWindow", "Base consumer stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumer->setText(QApplication::translate("MainWindow", "Consumer:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivore->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPhyto->setToolTip(QApplication::translate("MainWindow", "Base phytoplankton stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPhyto->setText(QApplication::translate("MainWindow", "Phyto:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDoc->setToolTip(QApplication::translate("MainWindow", "Base DOC stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelDoc->setText(QApplication::translate("MainWindow", "DOC:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecomp->setToolTip(QApplication::translate("MainWindow", "Base seddecomposer stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecomp->setText(QApplication::translate("MainWindow", "Seddecomp:", 0, QApplication::UnicodeUTF8));
        lineEditPoc->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPoc->setToolTip(QApplication::translate("MainWindow", "Base POC stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPoc->setText(QApplication::translate("MainWindow", "POC:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivore->setToolTip(QApplication::translate("MainWindow", "Base herbivore stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivore->setText(QApplication::translate("MainWindow", "Herbivore:", 0, QApplication::UnicodeUTF8));
        lineEditDecomp->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        lineEditMacro->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        lineEditPhyto->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumer->setToolTip(QApplication::translate("MainWindow", "Base sedconsumer stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumer->setText(QApplication::translate("MainWindow", "Sedconsumer:", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumer->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDetritus->setToolTip(QApplication::translate("MainWindow", "Base detritus stock value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelDetritus->setText(QApplication::translate("MainWindow", "Detritus:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabConfig), QApplication::translate("MainWindow", "Configuration", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabStocks->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelPhytoSenescence->setToolTip(QApplication::translate("MainWindow", "Phytoplankton that senescences per day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPhytoSenescence->setText(QApplication::translate("MainWindow", "Phyto Senescence:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditPhytoSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditPhytoSenescence->setText(QApplication::translate("MainWindow", "0.02", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPhytoRespiration->setToolTip(QApplication::translate("MainWindow", "Phytoplankton lost to respiration per day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPhytoRespiration->setText(QApplication::translate("MainWindow", "Phyto Respiration:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditPhytoRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditPhytoRespiration->setText(QApplication::translate("MainWindow", "0.1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPhytoExcretion->setToolTip(QApplication::translate("MainWindow", "Phytoplankton lost to excretion per day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPhytoExcretion->setText(QApplication::translate("MainWindow", "Phyto Excretion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditPhytoExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditPhytoExcretion->setText(QApplication::translate("MainWindow", "0.05", 0, QApplication::UnicodeUTF8));
        lineEditPhytoAj->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPhytoAj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - maximum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPhytoAj->setText(QApplication::translate("MainWindow", "Phyto Aj:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelPhytoGj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - minimum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelPhytoGj->setText(QApplication::translate("MainWindow", "Phyto Gj:", 0, QApplication::UnicodeUTF8));
        lineEditPhytoGj->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreAiPhyto->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for herbivores feeding on phytoplankton", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreAiPhyto->setText(QApplication::translate("MainWindow", "Herbivore Ai Phyto:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreAiPhyto->setText(QApplication::translate("MainWindow", "20", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreAiPeri->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for herbivores feeding on periphyton", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreAiPeri->setText(QApplication::translate("MainWindow", "Herbivore Ai Peri:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreGiPhyto->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreGiPeri->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreGiPhyto->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for herbivores feeding on phytoplankton", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreGiPhyto->setText(QApplication::translate("MainWindow", "Herbivore Gi Phyto:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreAiPeri->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivorePrefPhyto->setToolTip(QApplication::translate("MainWindow", "Preference of herbivores for phytoplankton", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivorePrefPhyto->setText(QApplication::translate("MainWindow", "Herbivore Pref Phyto:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreGiPeri->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for herbivores feeding on periphyton", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreGiPeri->setText(QApplication::translate("MainWindow", "Herbivore Gi Peri:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivorePrefPhyto->setText(QApplication::translate("MainWindow", "0.7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivorePrefPeri->setToolTip(QApplication::translate("MainWindow", "Preference of herbivores for periphyton", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivorePrefPeri->setText(QApplication::translate("MainWindow", "Herbivore Pref Peri:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivorePrefPeri->setText(QApplication::translate("MainWindow", "0.15", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivorePrefWaterdecomp->setToolTip(QApplication::translate("MainWindow", "Preference of herbivores for water decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivorePrefWaterdecomp->setText(QApplication::translate("MainWindow", "Herbivore Pref Waterdecomp:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreAiWaterdecomp->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreAj->setText(QApplication::translate("MainWindow", "2.4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreAiWaterdecomp->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for herbivores feeding on water decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreAiWaterdecomp->setText(QApplication::translate("MainWindow", "Herbivore Ai Waterdecomp:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivorePrefWaterdecomp->setText(QApplication::translate("MainWindow", "0.15", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreGiWaterdecomp->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for herbivores feeding on water decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreGiWaterdecomp->setText(QApplication::translate("MainWindow", "Herbivore Gi Waterdecomp:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreAj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - maximum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreAj->setText(QApplication::translate("MainWindow", "Herbivore Aj:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreGiWaterdecomp->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreGj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - minimum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreGj->setText(QApplication::translate("MainWindow", "Herbivore Gj:", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreGj->setText(QApplication::translate("MainWindow", "108", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreEgestion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from herbivores to egestion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreEgestion->setText(QApplication::translate("MainWindow", "Herbivore Egestion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditHerbivoreRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditHerbivoreRespiration->setText(QApplication::translate("MainWindow", "0.08", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditHerbivoreSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditHerbivoreSenescence->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreRespiration->setToolTip(QApplication::translate("MainWindow", "Carbon lost from herbivores to respiration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreRespiration->setText(QApplication::translate("MainWindow", "Herbivore Respiration:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditHerbivoreEgestion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditHerbivoreEgestion->setText(QApplication::translate("MainWindow", "0.2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreExcretion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from herbivores to excretion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreExcretion->setText(QApplication::translate("MainWindow", "Herbivore Excretion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreSenescence->setToolTip(QApplication::translate("MainWindow", "Carbon lost from herbivores to senescence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreSenescence->setText(QApplication::translate("MainWindow", "Herbivore Senescence", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditHerbivoreExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditHerbivoreExcretion->setText(QApplication::translate("MainWindow", "0.4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompAiDoc->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for water decomposers feeding on dissolved organic carbon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompAiDoc->setText(QApplication::translate("MainWindow", "Waterdecomp Ai DOC:", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompAiDoc->setText(QApplication::translate("MainWindow", "30", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompGiDoc->setText(QApplication::translate("MainWindow", "0.05", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompGiDoc->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for water decomposers feeding on dissolved organic carbon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompGiDoc->setText(QApplication::translate("MainWindow", "Waterdecomp Gi DOC:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompPrefDoc->setToolTip(QApplication::translate("MainWindow", "Preference of water decomposers for dissolved organic carbon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompPrefDoc->setText(QApplication::translate("MainWindow", "Waterdecomp Pref DOC:", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompPrefDoc->setText(QApplication::translate("MainWindow", "0.5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompRespiration->setToolTip(QApplication::translate("MainWindow", "Carbon lost from water decompsers to respiration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompRespiration->setText(QApplication::translate("MainWindow", "Waterdecomp Respiration:", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompAj->setText(QApplication::translate("MainWindow", "1.2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditWaterdecompExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditWaterdecompExcretion->setText(QApplication::translate("MainWindow", "0.173", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompAj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - maximum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompAj->setText(QApplication::translate("MainWindow", "Waterdecomp Aj:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditWaterdecompRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditWaterdecompRespiration->setText(QApplication::translate("MainWindow", "0.6", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompGj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - minimum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompGj->setText(QApplication::translate("MainWindow", "Waterdecomp Gj:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompExcretion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from waterde compsers to excretion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompExcretion->setText(QApplication::translate("MainWindow", "Waterdecomp Excretion:", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompGj->setText(QApplication::translate("MainWindow", "20", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompAiDetritus->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for sediment decomposers feeding on detritus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompAiDetritus->setText(QApplication::translate("MainWindow", "Seddecomp Ai Detritus:", 0, QApplication::UnicodeUTF8));
        lineEditSeddecompAiDetritus->setText(QApplication::translate("MainWindow", "0.6", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompSenescence->setToolTip(QApplication::translate("MainWindow", "Carbon lost from water decompsers to senescence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompSenescence->setText(QApplication::translate("MainWindow", "Waterdecomp Senescence:", 0, QApplication::UnicodeUTF8));
        lineEditSeddecompGiDetritus->setText(QApplication::translate("MainWindow", "0.005", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompMax->setText(QApplication::translate("MainWindow", "6.26", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompGiDetritus->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for sediment decomposers feeding on detritus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompGiDetritus->setText(QApplication::translate("MainWindow", "Seddecomp Gi Detritus:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditWaterdecompSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditWaterdecompSenescence->setText(QApplication::translate("MainWindow", "0.05", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompPrefDetritus->setToolTip(QApplication::translate("MainWindow", "Preference of sediment decomposers for detritus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompPrefDetritus->setText(QApplication::translate("MainWindow", "Seddecomp Pref Detritus:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompMax->setToolTip(QApplication::translate("MainWindow", "Maximum rate of consumption of water decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompMax->setText(QApplication::translate("MainWindow", "Waterdecomp Max:", 0, QApplication::UnicodeUTF8));
        lineEditSeddecompPrefDetritus->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        lineEditHerbivoreMax->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelHerbivoreMax->setToolTip(QApplication::translate("MainWindow", "Maximum rate of consumption of herbivores", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelHerbivoreMax->setText(QApplication::translate("MainWindow", "Herbivore Max", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompAj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - maximum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompAj->setText(QApplication::translate("MainWindow", "Seddecomp Aj:", 0, QApplication::UnicodeUTF8));
        lineEditSeddecompAj->setText(QApplication::translate("MainWindow", "0.2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditSeddecompRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditSeddecompRespiration->setText(QApplication::translate("MainWindow", "0.6", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompGj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - minimum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompGj->setText(QApplication::translate("MainWindow", "Seddecomp Gj:", 0, QApplication::UnicodeUTF8));
        lineEditSeddecompGj->setText(QApplication::translate("MainWindow", "120", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompRespiration->setToolTip(QApplication::translate("MainWindow", "Carbon lost from sediment decomposers  to respiration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompRespiration->setText(QApplication::translate("MainWindow", "Seddecomp Respiration:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompExcretion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from sediment decomposers to excretion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompExcretion->setText(QApplication::translate("MainWindow", "Seddecomp Excretion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditSeddecompExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditSeddecompExcretion->setText(QApplication::translate("MainWindow", "0.173", 0, QApplication::UnicodeUTF8));
        lineEditSeddecompMax->setText(QApplication::translate("MainWindow", "6.26", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompSenescence->setToolTip(QApplication::translate("MainWindow", "Carbon lost from sediment decomposers to senescence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompSenescence->setText(QApplication::translate("MainWindow", "Seddecomp Senescence:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditSeddecompSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditSeddecompSenescence->setText(QApplication::translate("MainWindow", "0.05", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSeddecompMax->setToolTip(QApplication::translate("MainWindow", "Maximum rate of consumption of sediment decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSeddecompMax->setText(QApplication::translate("MainWindow", "Seddecomp Max:", 0, QApplication::UnicodeUTF8));
        lineEditConsumerGiSedconsumer->setText(QApplication::translate("MainWindow", "0.4", 0, QApplication::UnicodeUTF8));
        lineEditConsumerGj->setText(QApplication::translate("MainWindow", "6.5", 0, QApplication::UnicodeUTF8));
        lineEditConsumerAiSedconsumer->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerPrefHerbivore->setToolTip(QApplication::translate("MainWindow", "Preference of consumers for herbivores", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerPrefHerbivore->setText(QApplication::translate("MainWindow", "Consumer Pref Herbivore:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerGiSedconsumer->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for consumers feeding on sediment consumers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerGiSedconsumer->setText(QApplication::translate("MainWindow", "Consumer Gi Sedconsumer:", 0, QApplication::UnicodeUTF8));
        lineEditConsumerGiHerbivore->setText(QApplication::translate("MainWindow", "0.025", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerAj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - maximum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerAj->setText(QApplication::translate("MainWindow", "Consumer Aj:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerRespiration->setToolTip(QApplication::translate("MainWindow", "Carbon lost from consumers to respiration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerRespiration->setText(QApplication::translate("MainWindow", "Consumer Respiration:", 0, QApplication::UnicodeUTF8));
        lineEditConsumerPrefSedconsumer->setText(QApplication::translate("MainWindow", "0.3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerGiHerbivore->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for consumers feeding on herbivores", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerGiHerbivore->setText(QApplication::translate("MainWindow", "Consumer Gi Herbivore:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditConsumerRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditConsumerRespiration->setText(QApplication::translate("MainWindow", "0.0125", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerPrefSedconsumer->setToolTip(QApplication::translate("MainWindow", "Preference of consumers for sediment consumers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerPrefSedconsumer->setText(QApplication::translate("MainWindow", "Consumer Pref Sedconsumer:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerAiSedconsumer->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for consumers feeding on sediment consumers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerAiSedconsumer->setText(QApplication::translate("MainWindow", "Consumer Ai Sedconsumer:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerAiHerbivore->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for consumers feeding on herbivores", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerAiHerbivore->setText(QApplication::translate("MainWindow", "Consumer Ai Herbivore:", 0, QApplication::UnicodeUTF8));
        lineEditConsumerPrefHerbivore->setText(QApplication::translate("MainWindow", "0.7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerGj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - minimum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerGj->setText(QApplication::translate("MainWindow", "Consumer Gj:", 0, QApplication::UnicodeUTF8));
        lineEditConsumerAiHerbivore->setText(QApplication::translate("MainWindow", "3.5", 0, QApplication::UnicodeUTF8));
        lineEditConsumerAj->setText(QApplication::translate("MainWindow", "0.65", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerGiDetritus->setText(QApplication::translate("MainWindow", "0.02", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerGiSeddecomp->setText(QApplication::translate("MainWindow", "0.02", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerAiDetritus->setText(QApplication::translate("MainWindow", "3.5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerEgestion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from consumers to egestion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerEgestion->setText(QApplication::translate("MainWindow", "Consumer Egestion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerGiDetritus->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for sediment consumers feeding on detritus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerGiDetritus->setText(QApplication::translate("MainWindow", "Sedconsumer Gi Detritus:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditConsumerSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditConsumerSenescence->setText(QApplication::translate("MainWindow", "0.002", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerAiSeddecomp->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for sediment consumers feeding on sediment decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerAiSeddecomp->setText(QApplication::translate("MainWindow", "Sedconsumer Ai Seddecomp:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerPrefSeddecomp->setToolTip(QApplication::translate("MainWindow", "Preference of sediment consumers for sediment decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerPrefSeddecomp->setText(QApplication::translate("MainWindow", "Sedconsumer Pref Seddecomp:", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerPrefDetritus->setText(QApplication::translate("MainWindow", "0.1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerSenescence->setToolTip(QApplication::translate("MainWindow", "Carbon lost from consumers to senescence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerSenescence->setText(QApplication::translate("MainWindow", "Consumer Senescence:", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerPrefSeddecomp->setText(QApplication::translate("MainWindow", "0.5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerPrefDetritus->setToolTip(QApplication::translate("MainWindow", "Preference of sediment consumers for detritus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerPrefDetritus->setText(QApplication::translate("MainWindow", "Sedconsumer Pref Detritus:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerAiDetritus->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for sediment consumers feeding on detritus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerAiDetritus->setText(QApplication::translate("MainWindow", "Sedconsumer Ai Detritus:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerExcretion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from consumers to excretion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerExcretion->setText(QApplication::translate("MainWindow", "Consumer Excretion:", 0, QApplication::UnicodeUTF8));
        lineEditConsumerEgestion->setText(QApplication::translate("MainWindow", "0.2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerGiSeddecomp->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for sediment consumers feeding on sediment decomposers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerGiSeddecomp->setText(QApplication::translate("MainWindow", "Sedconsumer Gi Seddecomp:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditConsumerExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditConsumerExcretion->setText(QApplication::translate("MainWindow", "0.0032", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerAiSeddecomp->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerMax->setToolTip(QApplication::translate("MainWindow", "Maximum rate of consumption of sediment consumers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerMax->setText(QApplication::translate("MainWindow", "Sedconsumer Max:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditSedconsumerSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditSedconsumerSenescence->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerAj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - maximum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerAj->setText(QApplication::translate("MainWindow", "Sedconsumer Aj:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerExcretion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from sediment consumers to excretion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerExcretion->setText(QApplication::translate("MainWindow", "Sedconsumer Excretion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditSedconsumerRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditSedconsumerRespiration->setText(QApplication::translate("MainWindow", "0.04", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerAj->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerGj->setToolTip(QApplication::translate("MainWindow", "Density dependent crowding factors - minimum", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerGj->setText(QApplication::translate("MainWindow", "Sedconsumer Gj:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerSenescence->setToolTip(QApplication::translate("MainWindow", "Carbon lost from sediment consumers to senescence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerSenescence->setText(QApplication::translate("MainWindow", "Sedconsumer Senescence:", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerGj->setText(QApplication::translate("MainWindow", "20", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelSedconsumerRespiration->setToolTip(QApplication::translate("MainWindow", "Carbon lost from sediment consumers to respiration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelSedconsumerRespiration->setText(QApplication::translate("MainWindow", "Sedconsumer Respiration:", 0, QApplication::UnicodeUTF8));
        lineEditSedconsumerMax->setText(QApplication::translate("MainWindow", "0.55", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditSedconsumerExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditSedconsumerExcretion->setText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
        lineEditConsumerMax->setText(QApplication::translate("MainWindow", "0.125", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelConsumerMax->setToolTip(QApplication::translate("MainWindow", "Maximum rate of consumption of consumers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelConsumerMax->setText(QApplication::translate("MainWindow", "Consumer Max:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelMacroRespiration->setToolTip(QApplication::translate("MainWindow", "Carbon lost from macrophytes to respiration", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelMacroRespiration->setText(QApplication::translate("MainWindow", "Macro Respiration:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditMacroSenescence->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditMacroSenescence->setText(QApplication::translate("MainWindow", "0.08", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelMacroExcretion->setToolTip(QApplication::translate("MainWindow", "Carbon lost from macrophytes to excretion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelMacroExcretion->setText(QApplication::translate("MainWindow", "Macro Excretion:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelMacroSenescence->setToolTip(QApplication::translate("MainWindow", "Carbon lost from macrophytes to senescence", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelMacroSenescence->setText(QApplication::translate("MainWindow", "Macro Senescence:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditMacroRespiration->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditMacroRespiration->setText(QApplication::translate("MainWindow", "0.04", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditMacroExcretion->setToolTip(QApplication::translate("MainWindow", "gC/day", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditMacroExcretion->setText(QApplication::translate("MainWindow", "0.04", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompPrefPoc->setText(QApplication::translate("MainWindow", "0.5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompPrefPoc->setToolTip(QApplication::translate("MainWindow", "Preference of water decomposers for particulate organic carbon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompPrefPoc->setText(QApplication::translate("MainWindow", "Waterdecomp Pref POC:", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompAiPoc->setText(QApplication::translate("MainWindow", "30", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompGiPoc->setToolTip(QApplication::translate("MainWindow", "Prey refuge level for water decomposers feeding on particulate organic carbon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompGiPoc->setText(QApplication::translate("MainWindow", "Waterdecomp Gi POC:", 0, QApplication::UnicodeUTF8));
        lineEditWaterdecompGiPoc->setText(QApplication::translate("MainWindow", "0.05", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWaterdecompAiPoc->setToolTip(QApplication::translate("MainWindow", "Prey density threshold for water decomposers feeding on particulate organic carbon", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelWaterdecompAiPoc->setText(QApplication::translate("MainWindow", "Waterdecomp Ai POC:", 0, QApplication::UnicodeUTF8));
        lineEditMacroMassMax->setText(QApplication::translate("MainWindow", "1000", 0, QApplication::UnicodeUTF8));
        labelMacroTemp->setText(QApplication::translate("MainWindow", "Macro Temperature:", 0, QApplication::UnicodeUTF8));
        lineEditMacroVelocityMax->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        labelMacroVelocityMax->setText(QApplication::translate("MainWindow", "Macro Velocity Max:", 0, QApplication::UnicodeUTF8));
        lineEditMacroGrossCoef->setText(QApplication::translate("MainWindow", "0.08", 0, QApplication::UnicodeUTF8));
        labelMacroGrossCoef->setText(QApplication::translate("MainWindow", "Macro Gross:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditMacroTemp->setToolTip(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lineEditMacroTemp->setText(QApplication::translate("MainWindow", "19.7", 0, QApplication::UnicodeUTF8));
        labelMacroMassMax->setText(QApplication::translate("MainWindow", "Macro Mass Max:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabStocks), QApplication::translate("MainWindow", "Stocks", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabOuput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelTimeRemaining->setText(QApplication::translate("MainWindow", "Time Remaining:", 0, QApplication::UnicodeUTF8));
        labelTimeRemainingValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        labelTimeElapsedValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        labelTimeElapsed->setText(QApplication::translate("MainWindow", "Time Elapsed:", 0, QApplication::UnicodeUTF8));
        labelImageOutput->setText(QApplication::translate("MainWindow", "Image Here", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonFirstImage->setToolTip(QApplication::translate("MainWindow", "Display first image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonFirstImage->setText(QApplication::translate("MainWindow", "<<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonPreviousImage->setToolTip(QApplication::translate("MainWindow", "Display previous image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonPreviousImage->setText(QApplication::translate("MainWindow", "<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonLastImage->setToolTip(QApplication::translate("MainWindow", "Display last image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonLastImage->setText(QApplication::translate("MainWindow", ">>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonNextImage->setToolTip(QApplication::translate("MainWindow", "Display next image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonNextImage->setText(QApplication::translate("MainWindow", ">", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonStop->setToolTip(QApplication::translate("MainWindow", "Stop the model", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonPause->setToolTip(QApplication::translate("MainWindow", "Pause the model", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonPause->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        labelWhichStock->setText(QApplication::translate("MainWindow", "Which Stock", 0, QApplication::UnicodeUTF8));
        comboBoxWhichStock->clear();
        comboBoxWhichStock->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Consum", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Detritus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "DOC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Herbivore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Macro", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "POC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Phyto", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Sedconsumer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Seddecomp", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Waterdecomp", 0, QApplication::UnicodeUTF8)
        );
        tabWidget->setTabText(tabWidget->indexOf(tabOuput), QApplication::translate("MainWindow", "Ouput", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
