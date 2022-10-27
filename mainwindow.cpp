/// include

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
#include <sys/stat.h>

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

    /// setup the UI elements
    ui->setupUi(this);

    /// set a fixed main window side.
    this->setFixedSize(520,700);

    /// set a window title.
    this->setWindowTitle("DiskRateCheck " + QString(APP_VERSION) + " [BETA]");

    /// construct the objects
    UI = new GUI_Interface_Impl(this);
    manager = new appManager(UI);

    /// update GUI controls
    ui->statusbar->showMessage("Idle");
    ui->infoLabel->setText(QString("| RateCheck v" + QString(APP_VERSION) + " | Integrated Software Technologies Inc. |"));

#ifdef LINUX
    ui->DirectoryEdit->setText("~/");
#else
    ui->DirectoryEdit->setText("C:\\");
#endif

    ui->progressBar->hide();

    updateBlockSizeList();
}

///
/// MainWindow::~MainWindow.
///

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}


///
/// MainWindow::updateBlockSizeList.
///
/// update the GUI control to show the I/O block sizes for the test
///

void MainWindow::updateBlockSizeList()
{
    ui->BlockSizeEdit->clear();

    int start_index = ui->BlockSizeStartCombo->currentIndex();
    int end_index = ui->BlockSizeEndCombo->currentIndex();

    /// loop throght the I/O blocks and perform benchmarking
    for (int idx =start_index;idx <=end_index;++idx) {
        appendToBlockSize(manager->IoSizeTagsVec[idx]);
    }
}

///
/// MainWindow::goToWebsite.
///
/// go to the website function
///

void MainWindow::goToWebsite()
{
    QString link = "http://www.integratedsw.tech";
    QDesktopServices::openUrl(QUrl(link));
}

///
/// MainWindow::blockSizeStartIndex().
///
/// get the start I/O block size index from the GUI combobox
///

unsigned int MainWindow::blockSizeStartIndex()
{
    return ui->BlockSizeStartCombo->currentIndex();
}

///
/// MainWindow::blockSizeEndIndex().
///
/// get the end IO block size index from the GUI combobox
///

unsigned int MainWindow::blockSizeEndIndex()
{
    return ui->BlockSizeEndCombo->currentIndex();
}

///
/// MainWindow::fileSizeComboIndex().
///
/// get the file size index from the GUI combobox
///


unsigned int MainWindow::fileSizeComboIndex()
{
    return ui->FileSizeCombo->currentIndex();
}

///
/// MainWindow::isValidateChecked().
///
/// user want to validate the write data?
///


bool MainWindow::isValidateChecked()
{
    return ui->ValidateDataCheck->isChecked();
}

///
/// MainWindow::rootDirectory().
///
/// get the root directory
///


std::string MainWindow::rootDirectory()
{
    return ui->DirectoryEdit->text().toStdString();
}

///
/// MainWindow::updateStatusMessage().
///
/// update the status message on the GUI
/// @param msg is the new status message.
///


void MainWindow::updateStatusMessage(std::string msg)
{
    ui->statusbar->showMessage(QString::fromStdString(msg));
}

///
/// MainWindow::appendToBlockSize().
///
/// append the new I/O block size to the GUI
///


void MainWindow::appendToBlockSize(std::string size)
{
    ui->BlockSizeEdit->append(QString::fromStdString(size));
}

///
/// MainWindow::blockSizeStartIndex().
///
/// append the new write rate to the GUI
///


void MainWindow::appendToWriteRate(std::string size)
{
    ui->WriteRateEdit->append(QString::fromStdString(size));
}

///
/// MainWindow::appendToReadRate().
///
/// append the new read rate to the GUI
///


void MainWindow::appendToReadRate(std::string size)
{
    ui->ReadRateEdit->append(QString::fromStdString(size));
}

///
/// MainWindow::restrictGUIElements().
///
/// enable or disable the GUI controls
/// @param state in which the GUI elements must change.
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
/// MainWindow::updateProgressBar().
///
/// update the GUI progreess bar
///


void MainWindow::updateProgressBar(int value)
{
    this->ui->progressBar->setValue(value);
}

///
/// MainWindow::on_dirBrowseBtn_clicked().
///
/// browse to the directory to perform benchmarking
///


void MainWindow::on_dirBrowseBtn_clicked()
{
    QString s1 = QFileDialog::getExistingDirectory(this, "Open a file", "directoryToOpen");
    ui->DirectoryEdit->setText(s1);
}

///
/// MainWindow::on_StartBtn_clicked().
///
/// start performing the benchmark
///


void MainWindow::on_StartBtn_clicked()
{

    try{
        /// smake sure we have a valiade directory
        if( std::filesystem::exists(ui->DirectoryEdit->text().toStdString().c_str()) == false )
            throw std::string( "cannot access " + ui->DirectoryEdit->text().toStdString());

        /// show the progress bar
        ui->progressBar->show();
        /// clear vectors
        //ui->BlockSizeEdit->clear();
        ui->ReadRateEdit->clear();
        ui->WriteRateEdit->clear();

        /// disable GUI elements before starting the benchmarking process
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

        /// using direct mode? or use the standard method which supports file caching
        bool directMode = this->ui->directModeCheckBox->isChecked();
        /// generate report after finishing the benchmark?
        bool report = this->ui->reportCheckBox->isChecked();
        /// multi-threaded process?
        bool mt_enabled = this->ui->multithreadCheckBox->isChecked();

        if(mt_enabled){

            /// create the QThread for the benchmark process
            QThread *thread = QThread::create(&appManager::startBenchmarking, manager, directMode, report);

            /// start the process
            thread->start();

            /// wait and update the GUI if needed
            while(thread->isRunning()){

#ifdef LINUX
                usleep(1);
#else
                Sleep(1);
#endif
                qApp->processEvents();
                updateProgressBar(manager->benchmarkProgress());
            }
        }

        else{
            manager->startBenchmarking(directMode); // single thread?
        }
        QMessageBox messageBox;
        messageBox.information(0,"Successfully performed benchmarking","Benchmarking finished.");
    }
    catch(std::string &msg){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Unable to perform benchmark.\nOperation aborted.\nReason is \n{" + QString::fromStdString(msg) + "}");
        restrictGUIElements(true);
    }
    catch(...)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Unable to perform benchmark.\nOperation aborted.");
        restrictGUIElements(true);
    }
}

///
/// MainWindow::on_AboutBtn_clicked().
///
/// go to the website
///

void MainWindow::on_AboutBtn_clicked()
{
    goToWebsite();
}

///
/// MainWindow::on_BlockSizeStartCombo_currentIndexChanged().
///
/// user did change the I/O block size index
///

void MainWindow::on_BlockSizeStartCombo_currentIndexChanged(int /*index*/)
{
    updateBlockSizeList();
}

///
/// MainWindow::on_BlockSizeEndCombo_currentIndexChanged().
///
/// user did change the I/O block size index
///
void MainWindow::on_BlockSizeEndCombo_currentIndexChanged(int /*index*/)
{
    updateBlockSizeList();
}

