/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *startButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *readerlabel;
    QSpinBox *readerSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *writerlable;
    QSpinBox *writerSpinBox;
    QPushButton *stopButton;
    QCheckBox *debugCheckBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *modeChangeLable;
    QComboBox *modeComboBox;
    QPushButton *resetButton;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLabel *debugloglabel;
    QTextEdit *debugLogTextEdit;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_3;
    QLabel *loglabel;
    QTextEdit *logTextEdit;
    QMenuBar *menuBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1061, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(10, 140, 171, 61));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        startButton->setFont(font);
        startButton->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        startButton->setMouseTracking(true);
        startButton->setTabletTracking(true);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 30, 171, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        readerlabel = new QLabel(layoutWidget);
        readerlabel->setObjectName("readerlabel");
        QFont font1;
        font1.setBold(true);
        readerlabel->setFont(font1);

        horizontalLayout->addWidget(readerlabel);

        readerSpinBox = new QSpinBox(layoutWidget);
        readerSpinBox->setObjectName("readerSpinBox");

        horizontalLayout->addWidget(readerSpinBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        writerlable = new QLabel(layoutWidget);
        writerlable->setObjectName("writerlable");
        writerlable->setFont(font1);

        horizontalLayout_2->addWidget(writerlable);

        writerSpinBox = new QSpinBox(layoutWidget);
        writerSpinBox->setObjectName("writerSpinBox");

        horizontalLayout_2->addWidget(writerSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");
        stopButton->setGeometry(QRect(10, 220, 171, 61));
        stopButton->setFont(font);
        stopButton->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        stopButton->setMouseTracking(true);
        stopButton->setTabletTracking(true);
        debugCheckBox = new QCheckBox(centralwidget);
        debugCheckBox->setObjectName("debugCheckBox");
        debugCheckBox->setGeometry(QRect(10, 380, 131, 25));
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(200, 10, 111, 59));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        modeChangeLable = new QLabel(layoutWidget1);
        modeChangeLable->setObjectName("modeChangeLable");
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        modeChangeLable->setFont(font2);
        modeChangeLable->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(modeChangeLable);

        modeComboBox = new QComboBox(layoutWidget1);
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->setObjectName("modeComboBox");
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        modeComboBox->setFont(font3);
        modeComboBox->setMouseTracking(true);
        modeComboBox->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        modeComboBox->setEditable(true);
        modeComboBox->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        verticalLayout_4->addWidget(modeComboBox);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(10, 300, 171, 61));
        resetButton->setFont(font);
        resetButton->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        resetButton->setMouseTracking(true);
        resetButton->setTabletTracking(true);
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(470, 0, 258, 471));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        debugloglabel = new QLabel(layoutWidget2);
        debugloglabel->setObjectName("debugloglabel");
        debugloglabel->setFont(font1);
        debugloglabel->setMouseTracking(true);
        debugloglabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(debugloglabel);

        debugLogTextEdit = new QTextEdit(layoutWidget2);
        debugLogTextEdit->setObjectName("debugLogTextEdit");
        debugLogTextEdit->setReadOnly(true);

        verticalLayout->addWidget(debugLogTextEdit);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(730, 0, 258, 471));
        verticalLayout_3 = new QVBoxLayout(layoutWidget3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        loglabel = new QLabel(layoutWidget3);
        loglabel->setObjectName("loglabel");
        loglabel->setFont(font1);
        loglabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(loglabel);

        logTextEdit = new QTextEdit(layoutWidget3);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setReadOnly(true);

        verticalLayout_3->addWidget(logTextEdit);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1061, 20));
        menuBar->setDefaultUp(false);
        MainWindow->setMenuBar(menuBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        modeComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\250\241\346\213\237", nullptr));
        readerlabel->setText(QCoreApplication::translate("MainWindow", "\350\257\273\350\200\205\346\225\260\351\207\217\357\274\232", nullptr));
        writerlable->setText(QCoreApplication::translate("MainWindow", "\345\206\231\350\200\205\346\225\260\351\207\217\357\274\232", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\346\250\241\346\213\237", nullptr));
        debugCheckBox->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\260\203\350\257\225\344\277\241\346\201\257", nullptr));
        modeChangeLable->setText(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
        modeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\345\206\231\350\200\205\344\274\230\345\205\210", nullptr));
        modeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\350\257\273\350\200\205\344\274\230\345\205\210", nullptr));
        modeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\350\257\273\345\206\231\345\205\254\345\271\263", nullptr));

        modeComboBox->setCurrentText(QCoreApplication::translate("MainWindow", "\345\206\231\350\200\205\344\274\230\345\205\210", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256\346\250\241\346\213\237", nullptr));
        debugloglabel->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\257\225\344\277\241\346\201\257", nullptr));
        loglabel->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
