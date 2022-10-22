﻿#include "mainwindow.h"
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
#include <support/start_stop_watch.h>
#include <support/benchmark.h>
#include <support/file_manager.h>

using namespace rateCheckApp;
using namespace std::chrono;

typedef uint64_t ii64;


#ifndef LINUX
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif


////=================================
////  CLASS CopyThread  --  Background thread used to copy files
////=================================

//class CopyThread : public StartStopThread
//{
//    typedef StartStopThread  inherited;
//public:
//    // Ctor
//    CopyThread(class MainWindow & owner)
//        : inherited("CopyThread"), Owner(owner)
//    {
//        Resume();
//    }

//protected:
//    //
//    class MainWindow &   Owner;



//    //  do one iteration of main process
//    virtual void SingleExecution()
//    {
//        Owner.StartWorking();
//        Stop();
//    }
//};




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)/*, File("Data.bin", ios::binary|ios::ate)*/
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //Block size init
    blockSizeVec.push_back(512);
    blockSizeVec.push_back(1*Kay);
    blockSizeVec.push_back(2*Kay);
    blockSizeVec.push_back(4*Kay);
    blockSizeVec.push_back(8*Kay);
    blockSizeVec.push_back(16*Kay);
    blockSizeVec.push_back(32*Kay);
    blockSizeVec.push_back(64*Kay);
    blockSizeVec.push_back(128*Kay);
    blockSizeVec.push_back(256*Kay);
    blockSizeVec.push_back(512*Kay);
    blockSizeVec.push_back(1*Meg);
    blockSizeVec.push_back(2*Meg);
    blockSizeVec.push_back(4*Meg);
    blockSizeVec.push_back(8*Meg);
    blockSizeVec.push_back(16*Meg);
    blockSizeVec.push_back(32*Meg);
    blockSizeVec.push_back(64*Meg);
    blockSizeVec.push_back(128*Meg);
    blockSizeVec.push_back(256*Meg);
    //File Size Init
    FileSizeVec.push_back(32*Meg);
    FileSizeVec.push_back(64*Meg);
    FileSizeVec.push_back(128*Meg);
    FileSizeVec.push_back(256*Meg);
    FileSizeVec.push_back(512*Meg);
    FileSizeVec.push_back(1*Geg);
    FileSizeVec.push_back(2*Geg);
    FileSizeVec.push_back(4*Geg);
    FileSizeVec.push_back(8*Geg);
    FileSizeVec.push_back(16*Geg);
    FileSizeVec.push_back(32*Geg);
    //IO Tags
    IoSizeTagsVec.push_back("512 B");
    IoSizeTagsVec.push_back("1 KB");
    IoSizeTagsVec.push_back("2 KB");
    IoSizeTagsVec.push_back("4 KB");
    IoSizeTagsVec.push_back("8 KB");
    IoSizeTagsVec.push_back("16 KB");
    IoSizeTagsVec.push_back("32 KB");
    IoSizeTagsVec.push_back("64 KB");
    IoSizeTagsVec.push_back("128 KB");
    IoSizeTagsVec.push_back("256 KB");
    IoSizeTagsVec.push_back("512 KB");
    IoSizeTagsVec.push_back("1 MB");
    IoSizeTagsVec.push_back("2 MB");
    IoSizeTagsVec.push_back("4 MB");
    IoSizeTagsVec.push_back("8 MB");
    IoSizeTagsVec.push_back("16 MB");
    IoSizeTagsVec.push_back("32 MB");
    IoSizeTagsVec.push_back("64 MB");
    IoSizeTagsVec.push_back("128 MB");
    IoSizeTagsVec.push_back("256 MB");

    ui->statusbar->showMessage("Idle");
}

MainWindow::~MainWindow()
{
    //   delete workThread;
    delete ui;
}

void MainWindow::fillRandomly(unsigned int size, int *ptr)
{
    srand(unsigned(time(nullptr)));
    unsigned int counter = 0;
    while(counter < size)
    {
        // fixme use arc4randm for clang?
        ptr[counter] = (rand() %50)+1;
        counter++;
    }
}

string MainWindow::AttachTag(double rate)
{
    if(rate < 1)
      {
        rate = rate * 1000;
    return QString::number(rate).toStdString() + " KB/S";
    }
    else if(rate > 1010)
    {
        rate = rate / 1000;
        return QString::number(rate).toStdString() + " GB/S";
    }
    else
        return QString::number(rate).toStdString() + " MB/S";

}
//#define ROUND_UP_SIZE(Value,Pow2) ((SIZE_T) ((((ULONG)(Value)) + (Pow2) - 1) & (~(((LONG)(Pow2)) - 1))))

//#define ROUND_UP_PTR(Ptr,Pow2)  ((void *) ((((ULONG_PTR)(Ptr)) + (Pow2) - 1) & (~(((LONG_PTR)(Pow2)) - 1))))


void MainWindow::StartWorking()
{
    // Required Parm
    unsigned int counter = 0;
    StartStopWatch watch;
    AveragedRate TxBytesPerBlock(10);
    std::string MainDIR, FilePath;
    double FTxBlockRate = 0.0;
    unsigned long long StartBlockSize, StopBlockSize, CurrentFileSize;
    unsigned long CurrentBlockSize;
    int BS_Start_Idx, BS_Stop_Idx;
    bool CheckData;


    StartBlockSize = blockSizeVec[static_cast<size_t>(this->ui->BlockSizeStartCombo->currentIndex())];
    StopBlockSize = blockSizeVec[static_cast<size_t>(this->ui->BlockSizeEndCombo->currentIndex())];
    CurrentFileSize = FileSizeVec[static_cast<size_t>(ui->FileSizeCombo->currentIndex())];
    BS_Start_Idx =  ui->BlockSizeStartCombo->currentIndex();
    BS_Stop_Idx =  ui->BlockSizeEndCombo->currentIndex();
    CheckData = ui->ValidateDataCheck->isChecked();

    if(StartBlockSize > StopBlockSize)
    {
        ui->statusbar->showMessage("Please Start With Smaller IO Block Size.");
        FinishedBenchmarking(); return;
    }

    this->ui->statusbar->showMessage("Initilizing the file for operation.");

    //Get Dir and create the file
    MainDIR = ui->DirectoryEdit->text().toStdString();
    FilePath = MainDIR + "\\" + "WriteFile.bin";
    remove(FilePath.c_str());

    //Dummy Data
    unsigned int maxBlockSize = 64*Meg;
    int *ReadData = new int[maxBlockSize];
    int *WriteData = new int[maxBlockSize];
    fillRandomly(maxBlockSize, WriteData);

    this->ui->statusbar->showMessage("Benchmarking is in the process...");

    for (int idx =BS_Start_Idx;idx <=BS_Stop_Idx;++idx) {

        size_t idx_t = static_cast<size_t>(idx);
        CurrentBlockSize = static_cast<unsigned long>(blockSizeVec[idx_t]);

        ui->BlockSizeEdit->append(QString::fromStdString(IoSizeTagsVec[idx_t]));

        //---------------
        // Write Windows
        //---------------
#ifndef LINUX
        {

            WriteFileHandle = CreateFileA(FilePath.c_str(), GENERIC_ALL, 0, nullptr, CREATE_NEW,  FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING , nullptr);
            if (WriteFileHandle == INVALID_HANDLE_VALUE)
            {
                this->ui->statusbar->showMessage("Cannot create the write file.");
                FinishedBenchmarking();
                return;
            }
            counter = 0;
            FTxBlockRate = 0.0;
            unsigned long long IOCount = CurrentFileSize / CurrentBlockSize;
            IOCount = std::max(IOCount, static_cast<unsigned long long>(10));
            IOCount = std::min(IOCount, static_cast<unsigned long long>(30000));


//             DWORD dwBytesWritten = 0;

//            DWORD BytesPerSector = 0; // obtained from the GetFreeDiskSpace function.
//         // ... obtain data here
//         // sample data
//             BytesPerSector = 512;
//            SIZE_T SizeNeeded = BytesPerSector + ROUND_UP_SIZE(CurrentBlockSize, BytesPerSector);  // Replace this statement with any allocation routine.
//            LPBYTE Buffer = (LPBYTE) malloc(SizeNeeded);  // Error checking of your choice.
//            if ( !Buffer )
//            {
//              FinishedBenchmarking();
//              return;
//            }
//            void * BufferAligned = ROUND_UP_PTR(WriteData, BytesPerSector);



            while(counter < IOCount){
                WriteFile(WriteFileHandle, WriteData, CurrentBlockSize, &dwBytesWritten, nullptr);
                if(dwBytesWritten == 0)
                {
                    this->ui->statusbar->showMessage("Failed to write to the file.");
                    FinishedBenchmarking();
                    return;
                }
                counter+=1;

            }
            double timediff = watch.Stop();
            FTxBlockRate = (IOCount*CurrentBlockSize) / (timediff*1.0e6);

            this->ui->WriteRateEdit->append(QString::fromStdString(AttachTag(FTxBlockRate)));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            CloseHandle(WriteFileHandle);
        }
#else
        //---------------
        // Write Linux/Mac
        //---------------
        {
            FileManager file(FilePath);
            // WriteFileHandle = CreateFileA(FilePath.c_str(), GENERIC_ALL, 0, nullptr, CREATE_NEW,  FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING , nullptr);
            //if (WriteFileHandle == INVALID_HANDLE_VALUE)

            if(file.Create() == false)
            {
                this->ui->statusbar->showMessage("Cannot create the write file.");
                FinishedBenchmarking();
                delete[] ReadData;
                delete[] WriteData;
                return;
            }

            counter = 0;
            FTxBlockRate = 0.0;
            unsigned long long IOCount = CurrentFileSize / CurrentBlockSize;
            IOCount = std::max(IOCount, static_cast<unsigned long long>(10));
            IOCount = std::min(IOCount, static_cast<unsigned long long>(30000));


            watch.Start();

            while(counter < IOCount){
                uint bytes = file.Write(reinterpret_cast<char*>(WriteData), CurrentBlockSize);
                //WriteFile(WriteFileHandle, WriteData, CurrentBlockSize, &dwBytesWritten, nullptr);
                if(bytes == 0)
                {
                    this->ui->statusbar->showMessage("Failed to write to the file.");
                    FinishedBenchmarking();
                    delete[] ReadData;
                    delete[] WriteData;
                    return;
                }
                counter+=1;

            }

            double timediff = watch.Stop();
            FTxBlockRate = (IOCount*CurrentBlockSize) / (timediff*1.0e6);

            this->ui->WriteRateEdit->append(QString::fromStdString(AttachTag(FTxBlockRate)));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            CloseHandle(WriteFileHandle);
            file.Close();
        }
#endif

        //---------------
        // Read
        //---------------

#ifndef LINUX
    {
            //Open The File
            ReadFileHandle = CreateFileA(FilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , nullptr);
            if (ReadFileHandle == INVALID_HANDLE_VALUE)
            {
                this->ui->statusbar->showMessage("Cannot create the read file.");
                FinishedBenchmarking();
                return;
            }

            counter = 0;
            FTxBlockRate = 0.0;
            unsigned long bytes;
            watch.Start();
            while(true){
                ReadFile(ReadFileHandle, ReadData, CurrentBlockSize, &bytes, nullptr);
                if(bytes == 0)
                {
                    break;
                }
                if(CheckData)
                {
                    bool result = memcmp(ReadData,WriteData,CurrentBlockSize);
                    if(result != 0)
                    {
                        this->ui->statusbar->showMessage("Failed the data validation.");
                        FinishedBenchmarking();
                        return;
                    }
                }

                counter+=1;
            }
            double timediff = watch.Stop();
            long long num1 = (counter*(CurrentBlockSize<1000? CurrentBlockSize : CurrentBlockSize/1000));
            double num2 =  (timediff*1.0e6);
            FTxBlockRate =  CurrentBlockSize<1000? (num1/num2): (num1/num2)*1000;
            AddToControl(this->ui->ReadRateEdit, AttachTag(FTxBlockRate));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            CloseHandle(ReadFileHandle);

        }

#else
        {
                //Open The File
                //ReadFileHandle = CreateFileA(FilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , nullptr);
                FileManager file(FilePath);
                if(file.Open() == false)
                {
                    this->ui->statusbar->showMessage("Cannot create the read file.");
                    FinishedBenchmarking();
                    delete[] ReadData;
                    delete[] WriteData;
                    return;
                }

                counter = 0;
                FTxBlockRate = 0.0;
                unsigned long bytes;
                watch.Start();
                while(true){
                    //ReadFile(ReadFileHandle, ReadData, CurrentBlockSize, &bytes, nullptr);
                    bytes = file.Read(reinterpret_cast<char*>(ReadData), CurrentBlockSize);
                    if(bytes == 0)
                    {
                        break;
                    }
                    if(CheckData)
                    {
                        bool result = memcmp(ReadData,WriteData,CurrentBlockSize);
                        if(result != 0)
                        {
                            this->ui->statusbar->showMessage("Failed the data validation.");
                            FinishedBenchmarking();
                            return;
                        }
                    }

                    counter+=1;
                }
                double timediff = watch.Stop();
                long long num1 = (counter*(CurrentBlockSize<1000? CurrentBlockSize : CurrentBlockSize/1000));
                double num2 =  (timediff*1.0e6);
                FTxBlockRate =  CurrentBlockSize<1000? (num1/num2): (num1/num2)*1000;
                // AddToControl(this->ui->ReadRateEdit, AttachTag(FTxBlockRate));
                ui->ReadRateEdit->append(QString::fromStdString(AttachTag(FTxBlockRate)));
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                //CloseHandle(ReadFileHandle);
                file.Close();
            }
#endif
        remove(FilePath.c_str());
    }

    delete[] ReadData;
    delete[] WriteData;

    remove(FilePath.c_str());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    this->ui->statusbar->showMessage("Finished Benchmarking.");
    FinishedBenchmarking();
}

void MainWindow::FinishedBenchmarking()
{
    this->ui->StartStopButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(true);
    this->ui->BlockSizeEndCombo->setEnabled(true);
    this->ui->BlockSizeStartCombo->setEnabled(true);
    this->ui->FileSizeCombo->setEnabled(true);
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

    std::thread workThread = std::thread( [this] { StartWorking(); } );
    workThread.join();
 //   StartWorking();
}
