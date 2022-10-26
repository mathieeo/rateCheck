#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>
#include <QFileDialog>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
#include <QThread>
#include <QDesktopServices>
#include <appVersion.h>
#include <QMessageBox>

typedef uint64_t int64;


#ifndef LINUX
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

///
/// MainWindow::MainWindow.
///

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(620,800);

    this->setWindowTitle("DiskRateCheck " + QString(APP_VERSION) + " [BETA]");

    UI = new GUI_Interface_Impl(this);
    manager = new appManager(UI);

    ui->statusbar->showMessage("Idle");

    ui->infoLabel->setText(QString("| RateCheck v" + QString(APP_VERSION) + " | Integrated Software Technologies Inc. |"));

#ifdef LINUX
    ui->DirectoryEdit->setText("~/");
#else
    ui->DirectoryEdit->setText("C:\\");
#endif

    ui->progressBar->hide();

}

///
/// MainWindow::~MainWindow.
///

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

void MainWindow::goToWebsite()
{
    QString link = "http://www.integratedsw.tech";
    QDesktopServices::openUrl(QUrl(link));
}

///
/// MainWindow::blockSizeStartIndex().
///

unsigned int MainWindow::blockSizeStartIndex()
{
    return ui->BlockSizeStartCombo->currentIndex();
}

///
/// MainWindow::blockSizeStartIndex().
///

unsigned int MainWindow::blockSizeEndIndex()
{
    return ui->BlockSizeEndCombo->currentIndex();
}

///
/// MainWindow::blockSizeStartIndex().
///


unsigned int MainWindow::fileSizeComboIndex()
{
    return ui->FileSizeCombo->currentIndex();
}

///
/// MainWindow::blockSizeStartIndex().
///


bool MainWindow::isValidateChecked()
{
    return ui->ValidateDataCheck->isChecked();
}

///
/// MainWindow::blockSizeStartIndex().
///


std::string MainWindow::rootDirectory()
{
    return ui->DirectoryEdit->text().toStdString();
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::updateStatusMessage(std::string msg)
{
    ui->statusbar->showMessage(QString::fromStdString(msg));
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::appendToBlockSize(std::string size)
{
    ui->BlockSizeEdit->append(QString::fromStdString(size));
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::appendToWriteRate(std::string size)
{
    ui->WriteRateEdit->append(QString::fromStdString(size));
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::appendToReadRate(std::string size)
{
    ui->ReadRateEdit->append(QString::fromStdString(size));
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::restrictGUIElements(bool state)
{
    this->ui->StartBtn->setEnabled(state);
    this->ui->dirBrowseBtn->setEnabled(state);
    this->ui->BlockSizeEndCombo->setEnabled(state);
    this->ui->BlockSizeStartCombo->setEnabled(state);
    this->ui->FileSizeCombo->setEnabled(state);
    this->ui->AboutBtn->setEnabled(state);
    this->ui->DirectoryEdit->setEnabled(state);
    this->ui->dirBrowseBtn->setEnabled(state);
    //this->ui->ValidateDataCheck->setEnabled(state);
    this->ui->reportCheckBox->setEnabled(state);
    this->ui->directModeCheckBox->setEnabled(state);
    this->ui->ReadRateEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
    this->ui->WriteRateEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
    this->ui->BlockSizeEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::updateProgressBar(int value)
{
//    QString danger = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #FF0350,stop: 0.4999 #FF0020,stop: 0.5 #FF0019,stop: 1 #FF0000 );border-bottom-right-radius: 5px;border-bottom-left-radius: 5px;border: .px solid black;}";
//    QString safe= "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #78d,stop: 0.4999 #46a,stop: 0.5 #45a,stop: 1 #238 );border-bottom-right-radius: 7px;border-bottom-left-radius: 7px;border: 1px solid black;}";
//    if(ui->progressBar->value()<80)
//        ui->progressBar->setStyleSheet(danger);
//    else
//        ui->progressBar->setStyleSheet(safe);

    this->ui->progressBar->setValue(value);
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::on_dirBrowseBtn_clicked()
{
    QString s1 = QFileDialog::getExistingDirectory(this, "Open a file", "directoryToOpen");
    ui->DirectoryEdit->setText(s1);
}

///
/// MainWindow::blockSizeStartIndex().
///


void MainWindow::on_StartBtn_clicked()
{
    ui->progressBar->show();
    //clear
    ui->BlockSizeEdit->clear();
    ui->ReadRateEdit->clear();
    ui->WriteRateEdit->clear();

    this->ui->StartBtn->setEnabled(false);
    this->ui->dirBrowseBtn->setEnabled(false);
    this->ui->BlockSizeEndCombo->setEnabled(false);
    this->ui->BlockSizeStartCombo->setEnabled(false);
    this->ui->FileSizeCombo->setEnabled(false);
    this->ui->AboutBtn->setEnabled(false);
    this->ui->DirectoryEdit->setEnabled(false);
    this->ui->dirBrowseBtn->setEnabled(false);
   // this->ui->ValidateDataCheck->setEnabled(false);
    this->ui->reportCheckBox->setEnabled(false);
    this->ui->directModeCheckBox->setEnabled(false);
    this->ui->ReadRateEdit->setTextInteractionFlags(Qt::NoTextInteraction);
    this->ui->WriteRateEdit->setTextInteractionFlags(Qt::NoTextInteraction);
    this->ui->BlockSizeEdit->setTextInteractionFlags(Qt::NoTextInteraction);

    bool directMode = this->ui->directModeCheckBox->isChecked();
    bool report = this->ui->reportCheckBox->isChecked();

    try{
        QThread *thread = QThread::create(&appManager::StartWorking, manager, directMode, report);
        thread->start();
        while(thread->isRunning()){

#ifdef LINUX
            usleep(1);
#else
            Sleep(1);
#endif
            qApp->processEvents();
            updateProgressBar(manager->BenchmarkProgress);
        }

        //manager->StartWorking(directMode); // single thread?

        QMessageBox messageBox;
        messageBox.information(0,"Successfully performed benchmarking","Benchmarking finished.");
    }
    catch(std::string &msg){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Unable to perform benchmark. Operation aborted. Reason is \n{" + QString::fromStdString(msg) + "}");
        restrictGUIElements(true);
    }
    catch(...)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Unable to perform benchmark. Operation aborted.");
        restrictGUIElements(true);
    }
}

///
/// MainWindow::on_AboutBtn_clicked().
///

void MainWindow::on_AboutBtn_clicked()
{
    goToWebsite();
}

