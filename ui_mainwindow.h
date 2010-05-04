/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 4. May 22:12:31 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionRun;
    QAction *actionReset;
    QAction *actionPowerOff;
    QAction *actionSettings;
    QAction *actionExit;
    QAction *actionScreenshot;
    QAction *actionSuspend;
    QAction *actionResume;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabDebug;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClear;
    QTextBrowser *textBrowser;
    QWidget *tabScreenshot;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_5;
    QLineEdit *leBasePointer;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_6;
    QComboBox *cbWH;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QLineEdit *leWidth;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_3;
    QLineEdit *leHeight;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_4;
    QComboBox *cbFormat;
    QHBoxLayout *laySSImage;
    QLabel *lblScreenshot;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnScreenshot;
    QPushButton *btnSave;
    QGroupBox *gbAspectRatio;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rbOneOne;
    QRadioButton *rbOneTwo;
    QRadioButton *rbFourThree;
    QRadioButton *rbSixteenNine;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *fileName;
    QToolButton *btnOpen;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLabel *txtStatus;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuDevice;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/network.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(24, 24));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon1);
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset->setIcon(icon2);
        actionPowerOff = new QAction(MainWindow);
        actionPowerOff->setObjectName(QString::fromUtf8("actionPowerOff"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/poff.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPowerOff->setIcon(icon3);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionScreenshot = new QAction(MainWindow);
        actionScreenshot->setObjectName(QString::fromUtf8("actionScreenshot"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/screenshot.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScreenshot->setIcon(icon4);
        actionSuspend = new QAction(MainWindow);
        actionSuspend->setObjectName(QString::fromUtf8("actionSuspend"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/suspend.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSuspend->setIcon(icon5);
        actionResume = new QAction(MainWindow);
        actionResume->setObjectName(QString::fromUtf8("actionResume"));
        actionResume->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(9, 37, 482, 442));
        tabDebug = new QWidget();
        tabDebug->setObjectName(QString::fromUtf8("tabDebug"));
        verticalLayout_3 = new QVBoxLayout(tabDebug);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnClear = new QPushButton(tabDebug);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        horizontalLayout_2->addWidget(btnClear);


        verticalLayout_3->addLayout(horizontalLayout_2);

        textBrowser = new QTextBrowser(tabDebug);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_3->addWidget(textBrowser);

        tabWidget->addTab(tabDebug, QString());
        tabScreenshot = new QWidget();
        tabScreenshot->setObjectName(QString::fromUtf8("tabScreenshot"));
        verticalLayout_2 = new QVBoxLayout(tabScreenshot);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setContentsMargins(4, 4, 4, 4);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(0);
#ifndef Q_OS_MAC
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
#endif
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_5 = new QLabel(tabScreenshot);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_9->addWidget(label_5);

        leBasePointer = new QLineEdit(tabScreenshot);
        leBasePointer->setObjectName(QString::fromUtf8("leBasePointer"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leBasePointer->sizePolicy().hasHeightForWidth());
        leBasePointer->setSizePolicy(sizePolicy);
        leBasePointer->setMinimumSize(QSize(60, 0));

        verticalLayout_9->addWidget(leBasePointer);


        horizontalLayout_7->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setSizeConstraint(QLayout::SetMinimumSize);
        label_6 = new QLabel(tabScreenshot);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_10->addWidget(label_6);

        cbWH = new QComboBox(tabScreenshot);
        cbWH->setObjectName(QString::fromUtf8("cbWH"));
        sizePolicy.setHeightForWidth(cbWH->sizePolicy().hasHeightForWidth());
        cbWH->setSizePolicy(sizePolicy);
        cbWH->setMinimumSize(QSize(120, 0));

        verticalLayout_10->addWidget(cbWH);


        horizontalLayout_7->addLayout(verticalLayout_10);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        label_2 = new QLabel(tabScreenshot);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_6->addWidget(label_2);

        leWidth = new QLineEdit(tabScreenshot);
        leWidth->setObjectName(QString::fromUtf8("leWidth"));
        sizePolicy.setHeightForWidth(leWidth->sizePolicy().hasHeightForWidth());
        leWidth->setSizePolicy(sizePolicy);
        leWidth->setMinimumSize(QSize(40, 0));

        verticalLayout_6->addWidget(leWidth);


        horizontalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        label_3 = new QLabel(tabScreenshot);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_7->addWidget(label_3);

        leHeight = new QLineEdit(tabScreenshot);
        leHeight->setObjectName(QString::fromUtf8("leHeight"));
        sizePolicy.setHeightForWidth(leHeight->sizePolicy().hasHeightForWidth());
        leHeight->setSizePolicy(sizePolicy);
        leHeight->setMinimumSize(QSize(40, 0));

        verticalLayout_7->addWidget(leHeight);


        horizontalLayout_7->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_4 = new QLabel(tabScreenshot);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_8->addWidget(label_4);

        cbFormat = new QComboBox(tabScreenshot);
        cbFormat->setObjectName(QString::fromUtf8("cbFormat"));
        sizePolicy.setHeightForWidth(cbFormat->sizePolicy().hasHeightForWidth());
        cbFormat->setSizePolicy(sizePolicy);
        cbFormat->setMinimumSize(QSize(100, 0));

        verticalLayout_8->addWidget(cbFormat);


        horizontalLayout_7->addLayout(verticalLayout_8);


        verticalLayout_2->addLayout(horizontalLayout_7);

        laySSImage = new QHBoxLayout();
        laySSImage->setObjectName(QString::fromUtf8("laySSImage"));
        laySSImage->setSizeConstraint(QLayout::SetDefaultConstraint);
        lblScreenshot = new QLabel(tabScreenshot);
        lblScreenshot->setObjectName(QString::fromUtf8("lblScreenshot"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblScreenshot->sizePolicy().hasHeightForWidth());
        lblScreenshot->setSizePolicy(sizePolicy1);
        lblScreenshot->setAutoFillBackground(false);
        lblScreenshot->setFrameShape(QFrame::StyledPanel);

        laySSImage->addWidget(lblScreenshot);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnScreenshot = new QPushButton(tabScreenshot);
        btnScreenshot->setObjectName(QString::fromUtf8("btnScreenshot"));

        verticalLayout_4->addWidget(btnScreenshot);

        btnSave = new QPushButton(tabScreenshot);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setEnabled(true);

        verticalLayout_4->addWidget(btnSave);

        gbAspectRatio = new QGroupBox(tabScreenshot);
        gbAspectRatio->setObjectName(QString::fromUtf8("gbAspectRatio"));
        verticalLayout_5 = new QVBoxLayout(gbAspectRatio);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        rbOneOne = new QRadioButton(gbAspectRatio);
        rbOneOne->setObjectName(QString::fromUtf8("rbOneOne"));

        verticalLayout_5->addWidget(rbOneOne);

        rbOneTwo = new QRadioButton(gbAspectRatio);
        rbOneTwo->setObjectName(QString::fromUtf8("rbOneTwo"));

        verticalLayout_5->addWidget(rbOneTwo);

        rbFourThree = new QRadioButton(gbAspectRatio);
        rbFourThree->setObjectName(QString::fromUtf8("rbFourThree"));

        verticalLayout_5->addWidget(rbFourThree);

        rbSixteenNine = new QRadioButton(gbAspectRatio);
        rbSixteenNine->setObjectName(QString::fromUtf8("rbSixteenNine"));

        verticalLayout_5->addWidget(rbSixteenNine);


        verticalLayout_4->addWidget(gbAspectRatio);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_4->addItem(verticalSpacer);


        laySSImage->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(laySSImage);

        tabWidget->addTab(tabScreenshot, QString());
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 481, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        fileName = new QLineEdit(widget);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setReadOnly(true);

        horizontalLayout->addWidget(fileName);

        btnOpen = new QToolButton(widget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        horizontalLayout->addWidget(btnOpen);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 490, 481, 22));
        horizontalLayout_3 = new QHBoxLayout(widget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        txtStatus = new QLabel(widget1);
        txtStatus->setObjectName(QString::fromUtf8("txtStatus"));

        horizontalLayout_3->addWidget(txtStatus);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuDevice = new QMenu(menubar);
        menuDevice->setObjectName(QString::fromUtf8("menuDevice"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(16, 16));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        QWidget::setTabOrder(fileName, btnOpen);
        QWidget::setTabOrder(btnOpen, tabWidget);
        QWidget::setTabOrder(tabWidget, leBasePointer);
        QWidget::setTabOrder(leBasePointer, cbWH);
        QWidget::setTabOrder(cbWH, leWidth);
        QWidget::setTabOrder(leWidth, leHeight);
        QWidget::setTabOrder(leHeight, cbFormat);
        QWidget::setTabOrder(cbFormat, btnScreenshot);
        QWidget::setTabOrder(btnScreenshot, btnSave);
        QWidget::setTabOrder(btnSave, rbOneOne);
        QWidget::setTabOrder(rbOneOne, rbOneTwo);
        QWidget::setTabOrder(rbOneTwo, rbFourThree);
        QWidget::setTabOrder(rbFourThree, rbSixteenNine);
        QWidget::setTabOrder(rbSixteenNine, textBrowser);
        QWidget::setTabOrder(textBrowser, btnClear);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuDevice->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        menuDevice->addAction(actionRun);
        menuDevice->addAction(actionReset);
        menuDevice->addAction(actionPowerOff);
        menuDevice->addSeparator();
        menuDevice->addAction(actionSuspend);
        menuDevice->addAction(actionResume);
        menuDevice->addSeparator();
        menuDevice->addAction(actionScreenshot);
        menuFile->addAction(actionSettings);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        toolBar->addAction(actionRun);
        toolBar->addAction(actionReset);
        toolBar->addAction(actionPowerOff);
        toolBar->addSeparator();
        toolBar->addAction(actionSuspend);
        toolBar->addAction(actionResume);
        toolBar->addSeparator();
        toolBar->addAction(actionScreenshot);

        retranslateUi(MainWindow);
        QObject::connect(btnClear, SIGNAL(clicked()), textBrowser, SLOT(clear()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ConsoleLink", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionRun->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRun->setToolTip(QApplication::translate("MainWindow", "Upload executable and run", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionReset->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionReset->setToolTip(QApplication::translate("MainWindow", "Reset console", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPowerOff->setText(QApplication::translate("MainWindow", "Power off", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPowerOff->setToolTip(QApplication::translate("MainWindow", "Power off console", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionScreenshot->setText(QApplication::translate("MainWindow", "Screenshot", 0, QApplication::UnicodeUTF8));
        actionSuspend->setText(QApplication::translate("MainWindow", "Suspend", 0, QApplication::UnicodeUTF8));
        actionResume->setText(QApplication::translate("MainWindow", "Resume", 0, QApplication::UnicodeUTF8));
        btnClear->setText(QApplication::translate("MainWindow", "Clear Log", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabDebug), QApplication::translate("MainWindow", "Debugging", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Base Pointer", 0, QApplication::UnicodeUTF8));
        leBasePointer->setInputMask(QApplication::translate("MainWindow", "HHHHHH;_", 0, QApplication::UnicodeUTF8));
        leBasePointer->setText(QApplication::translate("MainWindow", "000000", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Resolution", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Width", 0, QApplication::UnicodeUTF8));
        leWidth->setInputMask(QApplication::translate("MainWindow", "0000;_", 0, QApplication::UnicodeUTF8));
        leWidth->setText(QApplication::translate("MainWindow", "640", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Height", 0, QApplication::UnicodeUTF8));
        leHeight->setInputMask(QApplication::translate("MainWindow", "0000;_", 0, QApplication::UnicodeUTF8));
        leHeight->setText(QApplication::translate("MainWindow", "512", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Format", 0, QApplication::UnicodeUTF8));
        lblScreenshot->setText(QString());
        btnScreenshot->setText(QApplication::translate("MainWindow", "Take Screenshot", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("MainWindow", "Save As", 0, QApplication::UnicodeUTF8));
        gbAspectRatio->setTitle(QApplication::translate("MainWindow", "Aspect Ratio", 0, QApplication::UnicodeUTF8));
        rbOneOne->setText(QApplication::translate("MainWindow", "1:1 Pixel", 0, QApplication::UnicodeUTF8));
        rbOneTwo->setText(QApplication::translate("MainWindow", "1:2 Pixel", 0, QApplication::UnicodeUTF8));
        rbFourThree->setText(QApplication::translate("MainWindow", "4:3", 0, QApplication::UnicodeUTF8));
        rbSixteenNine->setText(QApplication::translate("MainWindow", "16:9", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabScreenshot), QApplication::translate("MainWindow", "Screenshots", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Current File:", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Connection Status:", 0, QApplication::UnicodeUTF8));
        txtStatus->setText(QApplication::translate("MainWindow", "???", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuDevice->setTitle(QApplication::translate("MainWindow", "Device", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
