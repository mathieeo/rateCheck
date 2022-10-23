/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWebsite;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox;
    QCheckBox *ValidateDataCheck;
    QCheckBox *directModeCheckBox;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QTextEdit *BlockSizeEdit;
    QFrame *line;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_9;
    QTextEdit *WriteRateEdit;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_10;
    QTextEdit *ReadRateEdit;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *DirectoryEdit;
    QPushButton *dirBrowseBtn;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QComboBox *FileSizeCombo;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QComboBox *BlockSizeStartCombo;
    QLabel *label_6;
    QComboBox *BlockSizeEndCombo;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *StartBtn;
    QPushButton *AboutBtn;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(508, 711);
        actionWebsite = new QAction(MainWindow);
        actionWebsite->setObjectName("actionWebsite");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setEnabled(false);

        horizontalLayout_5->addWidget(checkBox);

        ValidateDataCheck = new QCheckBox(centralwidget);
        ValidateDataCheck->setObjectName("ValidateDataCheck");

        horizontalLayout_5->addWidget(ValidateDataCheck);

        directModeCheckBox = new QCheckBox(centralwidget);
        directModeCheckBox->setObjectName("directModeCheckBox");
        directModeCheckBox->setChecked(false);

        horizontalLayout_5->addWidget(directModeCheckBox);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_3, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_8);

        BlockSizeEdit = new QTextEdit(centralwidget);
        BlockSizeEdit->setObjectName("BlockSizeEdit");
        BlockSizeEdit->setMaximumSize(QSize(100, 16777215));
        BlockSizeEdit->setReadOnly(true);

        verticalLayout_5->addWidget(BlockSizeEdit);


        horizontalLayout_2->addLayout(verticalLayout_5);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_9);

        WriteRateEdit = new QTextEdit(centralwidget);
        WriteRateEdit->setObjectName("WriteRateEdit");
        WriteRateEdit->setMaximumSize(QSize(150, 16777215));
        WriteRateEdit->setReadOnly(true);

        verticalLayout_6->addWidget(WriteRateEdit);


        horizontalLayout_2->addLayout(verticalLayout_6);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_10);

        ReadRateEdit = new QTextEdit(centralwidget);
        ReadRateEdit->setObjectName("ReadRateEdit");
        ReadRateEdit->setMaximumSize(QSize(150, 16777215));
        ReadRateEdit->setReadOnly(true);

        verticalLayout_7->addWidget(ReadRateEdit);


        horizontalLayout_2->addLayout(verticalLayout_7);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        DirectoryEdit = new QLineEdit(centralwidget);
        DirectoryEdit->setObjectName("DirectoryEdit");
        DirectoryEdit->setMaximumSize(QSize(16777215, 16777215));
        DirectoryEdit->setReadOnly(true);

        horizontalLayout->addWidget(DirectoryEdit);

        dirBrowseBtn = new QPushButton(centralwidget);
        dirBrowseBtn->setObjectName("dirBrowseBtn");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dirBrowseBtn->sizePolicy().hasHeightForWidth());
        dirBrowseBtn->setSizePolicy(sizePolicy);
        dirBrowseBtn->setMinimumSize(QSize(50, 0));
        dirBrowseBtn->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(dirBrowseBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(100, 16777215));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(5);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(5, 5, 5, 5);
        FileSizeCombo = new QComboBox(groupBox_3);
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->addItem(QString());
        FileSizeCombo->setObjectName("FileSizeCombo");
        FileSizeCombo->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(FileSizeCombo, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        BlockSizeStartCombo = new QComboBox(groupBox);
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->addItem(QString());
        BlockSizeStartCombo->setObjectName("BlockSizeStartCombo");
        BlockSizeStartCombo->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(BlockSizeStartCombo);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        BlockSizeEndCombo = new QComboBox(groupBox);
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->addItem(QString());
        BlockSizeEndCombo->setObjectName("BlockSizeEndCombo");
        BlockSizeEndCombo->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(BlockSizeEndCombo);


        horizontalLayout_4->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setHorizontalSpacing(5);
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        StartBtn = new QPushButton(groupBox_2);
        StartBtn->setObjectName("StartBtn");
        StartBtn->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(StartBtn, 0, 1, 1, 1);

        AboutBtn = new QPushButton(groupBox_2);
        AboutBtn->setObjectName("AboutBtn");

        gridLayout_3->addWidget(AboutBtn, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        gridLayout_2->addWidget(progressBar, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 508, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        FileSizeCombo->setCurrentIndex(4);
        BlockSizeEndCombo->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DiskRateCheck - Integrated Software Technologies Inc.", nullptr));
        actionWebsite->setText(QCoreApplication::translate("MainWindow", "Website", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Generate Report (soon)", nullptr));
        ValidateDataCheck->setText(QCoreApplication::translate("MainWindow", "Validate Data", nullptr));
        directModeCheckBox->setText(QCoreApplication::translate("MainWindow", "Direct Disk Access (no cache)", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Block Size", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Write Rate", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Read Rate", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Directory", nullptr));
        DirectoryEdit->setText(QCoreApplication::translate("MainWindow", "\\", nullptr));
        dirBrowseBtn->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "File Size", nullptr));
        FileSizeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "32MB", nullptr));
        FileSizeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "64MB", nullptr));
        FileSizeCombo->setItemText(2, QCoreApplication::translate("MainWindow", "128MB", nullptr));
        FileSizeCombo->setItemText(3, QCoreApplication::translate("MainWindow", "256MB", nullptr));
        FileSizeCombo->setItemText(4, QCoreApplication::translate("MainWindow", "512MB", nullptr));
        FileSizeCombo->setItemText(5, QCoreApplication::translate("MainWindow", "1GB", nullptr));
        FileSizeCombo->setItemText(6, QCoreApplication::translate("MainWindow", "2GB", nullptr));
        FileSizeCombo->setItemText(7, QCoreApplication::translate("MainWindow", "4GB", nullptr));
        FileSizeCombo->setItemText(8, QCoreApplication::translate("MainWindow", "8GB", nullptr));
        FileSizeCombo->setItemText(9, QCoreApplication::translate("MainWindow", "16GB", nullptr));
        FileSizeCombo->setItemText(10, QCoreApplication::translate("MainWindow", "32GB", nullptr));

        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Block Size", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        BlockSizeStartCombo->setItemText(0, QCoreApplication::translate("MainWindow", "512B", nullptr));
        BlockSizeStartCombo->setItemText(1, QCoreApplication::translate("MainWindow", "1KB", nullptr));
        BlockSizeStartCombo->setItemText(2, QCoreApplication::translate("MainWindow", "2KB", nullptr));
        BlockSizeStartCombo->setItemText(3, QCoreApplication::translate("MainWindow", "4KB", nullptr));
        BlockSizeStartCombo->setItemText(4, QCoreApplication::translate("MainWindow", "8KB", nullptr));
        BlockSizeStartCombo->setItemText(5, QCoreApplication::translate("MainWindow", "16KB", nullptr));
        BlockSizeStartCombo->setItemText(6, QCoreApplication::translate("MainWindow", "32KB", nullptr));
        BlockSizeStartCombo->setItemText(7, QCoreApplication::translate("MainWindow", "64KB", nullptr));
        BlockSizeStartCombo->setItemText(8, QCoreApplication::translate("MainWindow", "128KB", nullptr));
        BlockSizeStartCombo->setItemText(9, QCoreApplication::translate("MainWindow", "256KB", nullptr));
        BlockSizeStartCombo->setItemText(10, QCoreApplication::translate("MainWindow", "512KB", nullptr));
        BlockSizeStartCombo->setItemText(11, QCoreApplication::translate("MainWindow", "1MB", nullptr));
        BlockSizeStartCombo->setItemText(12, QCoreApplication::translate("MainWindow", "2MB", nullptr));
        BlockSizeStartCombo->setItemText(13, QCoreApplication::translate("MainWindow", "4MB", nullptr));
        BlockSizeStartCombo->setItemText(14, QCoreApplication::translate("MainWindow", "8MB", nullptr));
        BlockSizeStartCombo->setItemText(15, QCoreApplication::translate("MainWindow", "16MB", nullptr));
        BlockSizeStartCombo->setItemText(16, QCoreApplication::translate("MainWindow", "32MB", nullptr));
        BlockSizeStartCombo->setItemText(17, QCoreApplication::translate("MainWindow", "64MB", nullptr));
        BlockSizeStartCombo->setItemText(18, QCoreApplication::translate("MainWindow", "128MB", nullptr));
        BlockSizeStartCombo->setItemText(19, QCoreApplication::translate("MainWindow", "256MB", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "To", nullptr));
        BlockSizeEndCombo->setItemText(0, QCoreApplication::translate("MainWindow", "512B", nullptr));
        BlockSizeEndCombo->setItemText(1, QCoreApplication::translate("MainWindow", "1KB", nullptr));
        BlockSizeEndCombo->setItemText(2, QCoreApplication::translate("MainWindow", "2KB", nullptr));
        BlockSizeEndCombo->setItemText(3, QCoreApplication::translate("MainWindow", "4KB", nullptr));
        BlockSizeEndCombo->setItemText(4, QCoreApplication::translate("MainWindow", "8KB", nullptr));
        BlockSizeEndCombo->setItemText(5, QCoreApplication::translate("MainWindow", "16KB", nullptr));
        BlockSizeEndCombo->setItemText(6, QCoreApplication::translate("MainWindow", "32KB", nullptr));
        BlockSizeEndCombo->setItemText(7, QCoreApplication::translate("MainWindow", "64KB", nullptr));
        BlockSizeEndCombo->setItemText(8, QCoreApplication::translate("MainWindow", "128KB", nullptr));
        BlockSizeEndCombo->setItemText(9, QCoreApplication::translate("MainWindow", "256KB", nullptr));
        BlockSizeEndCombo->setItemText(10, QCoreApplication::translate("MainWindow", "512KB", nullptr));
        BlockSizeEndCombo->setItemText(11, QCoreApplication::translate("MainWindow", "1MB", nullptr));
        BlockSizeEndCombo->setItemText(12, QCoreApplication::translate("MainWindow", "2MB", nullptr));
        BlockSizeEndCombo->setItemText(13, QCoreApplication::translate("MainWindow", "4MB", nullptr));
        BlockSizeEndCombo->setItemText(14, QCoreApplication::translate("MainWindow", "8MB", nullptr));
        BlockSizeEndCombo->setItemText(15, QCoreApplication::translate("MainWindow", "16MB", nullptr));
        BlockSizeEndCombo->setItemText(16, QCoreApplication::translate("MainWindow", "32MB", nullptr));
        BlockSizeEndCombo->setItemText(17, QCoreApplication::translate("MainWindow", "64MB", nullptr));
        BlockSizeEndCombo->setItemText(18, QCoreApplication::translate("MainWindow", "128MB", nullptr));
        BlockSizeEndCombo->setItemText(19, QCoreApplication::translate("MainWindow", "256MB", nullptr));

        groupBox_2->setTitle(QString());
        StartBtn->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        AboutBtn->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
