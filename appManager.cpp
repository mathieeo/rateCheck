#include <appManager.h>

#include <thread>
#include <chrono>
#include <support/start_stop_watch.h>
#include <support/benchmark.h>
#include <support/file_manager.h>
#include <QString>
#include <iostream>

using namespace rateCheckApp;
using namespace std::chrono;


appManager::appManager(GUI_Interface *_gui_interface) :
    gui_interface(_gui_interface)
{

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

}

appManager::~appManager() {
    delete gui_interface;
}

void appManager::fillRandomly(unsigned int size, int *ptr)
{
    srand(unsigned(time(nullptr)));
    unsigned int counter = 0;
    while(counter < size)
    {
        // fixme use arc4randm for clang?
        ptr[counter] = (arc4random() % 50) + 1;
        counter++;
    }
}

string appManager::AttachTag(double rate)
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


int appManager::StartWorking(bool directMode)
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

    BS_Start_Idx =  gui_interface->blockSizeStartIndex(); //ui->BlockSizeStartCombo->currentIndex();
    BS_Stop_Idx =  gui_interface->blockSizeEndIndex(); //ui->BlockSizeEndCombo->currentIndex();
    CheckData = gui_interface->isValidateChecked();//ui->ValidateDataCheck->isChecked();
    StartBlockSize = blockSizeVec[static_cast<size_t>(BS_Start_Idx)];
    StopBlockSize = blockSizeVec[static_cast<size_t>(BS_Stop_Idx)];
    CurrentFileSize = FileSizeVec[static_cast<size_t>(gui_interface->fileSizeComboIndex())];


    if(StartBlockSize > StopBlockSize)
    {
        gui_interface->updateStatusMessage("Please Start With Smaller IO Block Size.");
        FinishedBenchmarking(); return 0;
    }

    gui_interface->updateStatusMessage("Initilizing the file for operation.");

    //Get Dir and create the file
    MainDIR = gui_interface->rootDirectory(); // ui->DirectoryEdit->text().toStdString();
    FilePath = MainDIR + "\\" + "WriteFile.bin";
    remove(FilePath.c_str());

    //Dummy Data
    unsigned int maxBlockSize = 64*Meg;
    int *ReadData = new int[maxBlockSize];
    int *WriteData = new int[maxBlockSize];
    fillRandomly(maxBlockSize, WriteData);

    gui_interface->updateStatusMessage("Benchmarking is in the process...");

    float number_of_runs = BS_Stop_Idx-BS_Start_Idx;
    for (int idx =BS_Start_Idx;idx <=BS_Stop_Idx;++idx) {

        cout << idx << " " << number_of_runs << " " << (float(float(idx)/float(number_of_runs))*100) << endl;
        gui_interface->updateProgressBar((float(float(idx)/float(number_of_runs)))*100);

        size_t idx_t = static_cast<size_t>(idx);
        CurrentBlockSize = static_cast<unsigned long>(blockSizeVec[idx_t]);

        gui_interface->appendToBlockSize(IoSizeTagsVec[idx_t]);

        //---------------
        // Write
        //---------------
        {
            FileManager file(FilePath, !directMode);

            if(file.Create() == false)
            {
                gui_interface->updateStatusMessage("Cannot create the write file.");
                FinishedBenchmarking();
                delete[] ReadData;
                delete[] WriteData;
                return 0;
            }

            counter = 0;
            unsigned long long IOCount = CurrentFileSize / CurrentBlockSize;
            IOCount = std::max(IOCount, static_cast<unsigned long long>(10));
            IOCount = std::min(IOCount, static_cast<unsigned long long>(30000));


            watch.Start();

            while(counter < IOCount){
                uint bytes = file.Write(reinterpret_cast<char*>(WriteData), CurrentBlockSize);
                //WriteFile(WriteFileHandle, WriteData, CurrentBlockSize, &dwBytesWritten, nullptr);
                if(bytes == 0)
                {
                    gui_interface->updateStatusMessage("Failed to write to the file.");
                    FinishedBenchmarking();
                    delete[] ReadData;
                    delete[] WriteData;
                    return 0;
                }
                counter+=1;

            }

            double timediff = watch.Stop();
            FTxBlockRate = (IOCount*CurrentBlockSize) / (timediff*1.0e6);

            gui_interface->appendToWriteRate(AttachTag(FTxBlockRate));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            file.Close();
        }

        //---------------
        // Read
        //---------------
        {
            //Open The File
            FileManager file(FilePath, !directMode);
            if(file.Open() == false)
            {
                gui_interface->appendToWriteRate("Cannot create the read file.");
                FinishedBenchmarking();
                delete[] ReadData;
                delete[] WriteData;
                return 0;
            }

            counter = 0;
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
                        gui_interface->appendToWriteRate("Failed the data validation.");
                        FinishedBenchmarking();
                        return 0;
                    }
                }

                counter+=1;
            }
            double timediff = watch.Stop();
            long long num1 = (counter*(CurrentBlockSize<1000? CurrentBlockSize : CurrentBlockSize/1000));
            double num2 =  (timediff*1.0e6);
            FTxBlockRate =  CurrentBlockSize<1000? (num1/num2): (num1/num2)*1000;
            // AddToControl(this->ui->ReadRateEdit, AttachTag(FTxBlockRate));
            gui_interface->appendToReadRate(AttachTag(FTxBlockRate));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            //CloseHandle(ReadFileHandle);
            file.Close();
        }
        remove(FilePath.c_str());
    }

    delete[] ReadData;
    delete[] WriteData;

    remove(FilePath.c_str());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    gui_interface->updateStatusMessage("Finished Benchmarking.");
    FinishedBenchmarking();

    return 1;
}

void appManager::FinishedBenchmarking()
{
    gui_interface->restrictGUIElements(true);
}
