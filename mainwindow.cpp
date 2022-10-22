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

typedef uint64_t ii64;


#ifndef LINUX
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)/*, File("Data.bin", ios::binary|ios::ate)*/
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UI = new GUI_Interface_Impl(this);
    manager = new appManager(UI);

    ui->statusbar->showMessage("Idle");
}

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

unsigned int MainWindow::blockSizeStartIndex()
{
    return ui->BlockSizeStartCombo->currentIndex();
}

unsigned int MainWindow::blockSizeEndIndex()
{
    return ui->BlockSizeEndCombo->currentIndex();
}

unsigned int MainWindow::fileSizeComboIndex()
{
    return ui->FileSizeCombo->currentIndex();
}

bool MainWindow::isValidateChecked()
{
    return ui->ValidateDataCheck->isChecked();
}

string MainWindow::rootDirectory()
{
    return ui->DirectoryEdit->text().toStdString();
}

void MainWindow::updateStatusMessage(string msg)
{
    ui->statusbar->showMessage(QString::fromStdString(msg));
}

void MainWindow::appendToBlockSize(string size)
{
    ui->BlockSizeEdit->append(QString::fromStdString(size));
}

void MainWindow::appendToWriteRate(string size)
{
    ui->WriteRateEdit->append(QString::fromStdString(size));
}

void MainWindow::appendToReadRate(string size)
{
    ui->ReadRateEdit->append(QString::fromStdString(size));
}

void MainWindow::RestrictGUIElements(bool state)
{
        this->ui->StartStopButton->setEnabled(state);
        this->ui->pushButton_2->setEnabled(state);
        this->ui->BlockSizeEndCombo->setEnabled(state);
        this->ui->BlockSizeStartCombo->setEnabled(state);
        this->ui->FileSizeCombo->setEnabled(state);
}




void MainWindow::on_pushButton_2_clicked()
{
    QString s1 = QFileDialog::getExistingDirectory(this, "Open a file", "directoryToOpen");
    ui->DirectoryEdit->setText(s1);
}


void MainWindow::on_StartStopButton_clicked()
{
    //clear
    ui->BlockSizeEdit->clear();
    ui->ReadRateEdit->clear();
    ui->WriteRateEdit->clear();

    this->ui->StartStopButton->setEnabled(false);
    this->ui->pushButton_2->setEnabled(false);
    this->ui->BlockSizeEndCombo->setEnabled(false);
    this->ui->BlockSizeStartCombo->setEnabled(false);
    this->ui->FileSizeCombo->setEnabled(false);

    QThread *thread = QThread::create(&appManager::StartWorking, manager);
    thread->start();
}
