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
    QGridLayout *gridLayout_4;
    QProgressBar *progressBar;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_2;
    QFrame *line_11;
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
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *StartBtn;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *DirectoryEdit;
    QPushButton *dirBrowseBtn;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *multithreadCheckBox;
    QCheckBox *reportCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *ValidateDataCheck;
    QCheckBox *directModeCheckBox;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_8;
    QFrame *line_2;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_6;
    QTextEdit *WriteRateEdit;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_7;
    QTextEdit *ReadRateEdit;
    QFrame *line;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_5;
    QTextEdit *BlockSizeEdit;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *AboutBtn;
    QLabel *infoLabel;
    QFrame *line_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(569, 793);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionWebsite = new QAction(MainWindow);
        actionWebsite->setObjectName("actionWebsite");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        gridLayout_4->addWidget(progressBar, 3, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_9 = new QGridLayout(groupBox_4);
        gridLayout_9->setObjectName("gridLayout_9");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        line_11 = new QFrame(groupBox_4);
        line_11->setObjectName("line_11");
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_11);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(80, 16777215));
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
        FileSizeCombo->setMaxVisibleItems(11);

        gridLayout->addWidget(FileSizeCombo, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox_3);

        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(250, 16777215));
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

        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(5);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        StartBtn = new QPushButton(groupBox_2);
        StartBtn->setObjectName("StartBtn");
        StartBtn->setMinimumSize(QSize(0, 0));
        StartBtn->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(StartBtn, 0, 1, 1, 1);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout_9->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        DirectoryEdit = new QLineEdit(groupBox_4);
        DirectoryEdit->setObjectName("DirectoryEdit");
        DirectoryEdit->setMaximumSize(QSize(16777215, 16777215));
        DirectoryEdit->setReadOnly(false);

        horizontalLayout->addWidget(DirectoryEdit);

        dirBrowseBtn = new QPushButton(groupBox_4);
        dirBrowseBtn->setObjectName("dirBrowseBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(20);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dirBrowseBtn->sizePolicy().hasHeightForWidth());
        dirBrowseBtn->setSizePolicy(sizePolicy1);
        dirBrowseBtn->setMinimumSize(QSize(50, 0));
        dirBrowseBtn->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(dirBrowseBtn);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_9->addLayout(verticalLayout, 0, 0, 1, 1);

        groupBox_9 = new QGroupBox(groupBox_4);
        groupBox_9->setObjectName("groupBox_9");
        verticalLayout_3 = new QVBoxLayout(groupBox_9);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        multithreadCheckBox = new QCheckBox(groupBox_9);
        multithreadCheckBox->setObjectName("multithreadCheckBox");
        multithreadCheckBox->setChecked(true);

        horizontalLayout_5->addWidget(multithreadCheckBox);

        reportCheckBox = new QCheckBox(groupBox_9);
        reportCheckBox->setObjectName("reportCheckBox");
        reportCheckBox->setEnabled(true);
        reportCheckBox->setChecked(true);

        horizontalLayout_5->addWidget(reportCheckBox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        ValidateDataCheck = new QCheckBox(groupBox_9);
        ValidateDataCheck->setObjectName("ValidateDataCheck");
        ValidateDataCheck->setEnabled(false);

        horizontalLayout_2->addWidget(ValidateDataCheck);

        directModeCheckBox = new QCheckBox(groupBox_9);
        directModeCheckBox->setObjectName("directModeCheckBox");
        directModeCheckBox->setChecked(true);

        horizontalLayout_2->addWidget(directModeCheckBox);


        verticalLayout_3->addLayout(horizontalLayout_2);


        gridLayout_9->addWidget(groupBox_9, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        gridLayout_8 = new QGridLayout(groupBox_5);
        gridLayout_8->setSpacing(5);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_8->setContentsMargins(5, 5, 5, 5);
        line_2 = new QFrame(groupBox_5);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_2, 0, 3, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName("groupBox_7");
        gridLayout_6 = new QGridLayout(groupBox_7);
        gridLayout_6->setSpacing(3);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(3, 3, 3, 3);
        WriteRateEdit = new QTextEdit(groupBox_7);
        WriteRateEdit->setObjectName("WriteRateEdit");
        WriteRateEdit->setMaximumSize(QSize(16777215, 16777215));
        WriteRateEdit->setMouseTracking(false);
        WriteRateEdit->setUndoRedoEnabled(false);
        WriteRateEdit->setReadOnly(true);
        WriteRateEdit->setAcceptRichText(false);
        WriteRateEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        gridLayout_6->addWidget(WriteRateEdit, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_7, 0, 2, 1, 1);

        groupBox_8 = new QGroupBox(groupBox_5);
        groupBox_8->setObjectName("groupBox_8");
        gridLayout_7 = new QGridLayout(groupBox_8);
        gridLayout_7->setSpacing(3);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(3, 3, 3, 3);
        ReadRateEdit = new QTextEdit(groupBox_8);
        ReadRateEdit->setObjectName("ReadRateEdit");
        ReadRateEdit->setMaximumSize(QSize(16777215, 16777215));
        ReadRateEdit->setMouseTracking(false);
        ReadRateEdit->setUndoRedoEnabled(false);
        ReadRateEdit->setReadOnly(true);
        ReadRateEdit->setAcceptRichText(false);
        ReadRateEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        gridLayout_7->addWidget(ReadRateEdit, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_8, 0, 4, 1, 1);

        line = new QFrame(groupBox_5);
        line->setObjectName("line");
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line, 0, 1, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setMaximumSize(QSize(100, 16777215));
        gridLayout_5 = new QGridLayout(groupBox_6);
        gridLayout_5->setSpacing(3);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        BlockSizeEdit = new QTextEdit(groupBox_6);
        BlockSizeEdit->setObjectName("BlockSizeEdit");
        BlockSizeEdit->setMaximumSize(QSize(16777215, 16777215));
        BlockSizeEdit->setMouseTracking(false);
        BlockSizeEdit->setUndoRedoEnabled(false);
        BlockSizeEdit->setReadOnly(true);
        BlockSizeEdit->setAcceptRichText(false);
        BlockSizeEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        gridLayout_5->addWidget(BlockSizeEdit, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_6, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_5, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        AboutBtn = new QPushButton(centralwidget);
        AboutBtn->setObjectName("AboutBtn");
        AboutBtn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(AboutBtn);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setLayoutDirection(Qt::RightToLeft);
        infoLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(infoLabel);


        gridLayout_4->addLayout(horizontalLayout_6, 4, 0, 1, 1);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 569, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        FileSizeCombo->setCurrentIndex(5);
        BlockSizeStartCombo->setCurrentIndex(9);
        BlockSizeEndCombo->setCurrentIndex(15);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DiskRateCheck - Integrated Software Technologies Inc.", nullptr));
        actionWebsite->setText(QCoreApplication::translate("MainWindow", "Website", nullptr));
        progressBar->setFormat(QCoreApplication::translate("MainWindow", "Benchmarking In Progress %p%", nullptr));
        groupBox_4->setTitle(QString());
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

        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "I/O", nullptr));
        StartBtn->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Directory", nullptr));
        DirectoryEdit->setText(QCoreApplication::translate("MainWindow", "/home/matt/Personal", nullptr));
        dirBrowseBtn->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "Checks", nullptr));
        multithreadCheckBox->setText(QCoreApplication::translate("MainWindow", "Multi-Threading", nullptr));
        reportCheckBox->setText(QCoreApplication::translate("MainWindow", "Generate Report", nullptr));
        ValidateDataCheck->setText(QCoreApplication::translate("MainWindow", "Validate Data (soon)", nullptr));
        directModeCheckBox->setText(QCoreApplication::translate("MainWindow", "Direct Disk Access (no cache)", nullptr));
        groupBox_5->setTitle(QString());
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Write Rate", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "Read Rate", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Block Size", nullptr));
        AboutBtn->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        infoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
