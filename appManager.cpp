#include <appManager.h>

#include <thread>
#include <chrono>
#include <support/start_stop_watch.h>
#include <support/benchmark.h>
#include <support/file_manager.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace rateCheckApp;
using namespace std::chrono;


///
///  Constructor of class appManager.
///
/// This class handles the file managements and benchmarking routines.
/// @param reference from the GUI object so we can call the GUI setters and getters
///
appManager::appManager(GUI_Interface *_gui_interface) :
    gui_interface(_gui_interface)
{
    /// reset benchmark progress var
    BenchmarkProgress = 0.0f;

    /// init vectors.
    /// Block size vection
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
    /// File Size vector
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
    /// IO Tags vector
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
///
///  Destractor of class appManager
///
appManager::~appManager() {
    delete gui_interface;
}

///
/// appManager::fillRandomly().
///
/// Fill random data to the buffer.
/// @param size number of bytes to write.
/// @param ptr buffer pointer.
///

void appManager::fillRandomly(unsigned int size, int *ptr)
{
    srand(unsigned(time(nullptr)));
    unsigned int counter = 0;
    while(counter < size)
    {
        // fixme use arc4random for clang?
        ptr[counter] = (rand() % 50) + 1;
        counter++;
    }
}

///
///  appManager::attachTag().
///
/// helper function to attach the rate tag next to the rate for example 11234 B/S rate will be 111.234 GB/S
/// @param rate variable is the actual rate that the tag must be attached to.
///

std::string appManager::attachTag(double rate)
{
    if(rate < 1)
    {
        rate = rate * 1000;
        return std::to_string(rate) + " KB/S";
    }
    else if(rate > 1010)
    {
        rate = rate / 1000;
        return std::to_string(rate) + " GB/S";
    }
    else
        return std::to_string(rate) + " MB/S";

}

///
///  appManager::generateReport().
///
/// Generate report function; creates a txt file with the details.
///

std::string appManager::generateReport()
{
    std::stringstream ss;

    ss << "| Block-Size | Write-Rate | Read-Rate |" << std::endl;
    for(size_t i=0;i<measuredBlockSizeVec.size();++i)
    {
        ss << "| " << measuredBlockSizeVec[i] << " | " << measuredWriteRateVec[i] << " | " << measuredReadRateVec[i] << " |" << std::endl;
    }

    std::ofstream out_file("report.txt");
    out_file << ss.str();
    out_file.close();

    return ss.str();
}


///
///  appManager::startBenchmarking().
///
/// Start benchmarking is the main process to start benchmarking, the function takes two booloan prams.
/// @param directMode avoid caching the file to the host RAM usually done by the std methods.
/// @param report by default report variable is set to true to generate report after finishing the benchmarking.
///

int appManager::startBenchmarking(bool directMode, bool report)
{
    /// Required Parm.
    unsigned int counter = 0;
    StartStopWatch watch;
    AveragedRate TxBytesPerBlock(10);
    std::string MainDIR, FilePath;
    double rate = 0.0;
    unsigned long long StartBlockSize, StopBlockSize, CurrentFileSize;
    unsigned long CurrentBlockSize;
    int BS_Start_Idx, BS_Stop_Idx;
    bool CheckData;

    /// clear the old measured vectors
    measuredBlockSizeVec.clear();
    measuredReadRateVec.clear();
    measuredWriteRateVec.clear();

    /// get the start IO block index sie sleected by the user.
    BS_Start_Idx =  gui_interface->blockSizeStartIndex();
    /// get the end IO block index sie sleected by the user.
    BS_Stop_Idx =  gui_interface->blockSizeEndIndex();
    /// check if user wants to validade the write data.
    CheckData = gui_interface->isValidateChecked();
    /// get the sizes.
    StartBlockSize = blockSizeVec[static_cast<size_t>(BS_Start_Idx)];
    StopBlockSize = blockSizeVec[static_cast<size_t>(BS_Stop_Idx)];
    CurrentFileSize = FileSizeVec[static_cast<size_t>(gui_interface->fileSizeComboIndex())];


    if(StartBlockSize > StopBlockSize)
    {
        gui_interface->updateStatusMessage("Please Start With Smaller IO Block Size.");
        finishedBenchmarking(); return 0;
    }

    gui_interface->updateStatusMessage("Initilizing the file for operation.");

    /// Get the specified directory
    MainDIR = gui_interface->rootDirectory();
    /// append the binary file name to the path
    FilePath = MainDIR + "//" + "rateCheck_temp_file.bin";
    /// remove file if exist
    remove(FilePath.c_str());

    /// define the read/write buffers
    unsigned int maxBlockSize = 64*Meg;
    int *ReadData = new int[maxBlockSize];
    int *WriteData = new int[maxBlockSize];
    /// fill random data to the write buffer
    fillRandomly(maxBlockSize, WriteData);

    gui_interface->updateStatusMessage("Benchmarking is in the process...");

    /// get the number of runs needed
    float number_of_runs = BS_Stop_Idx-BS_Start_Idx;
    /// loop throght the I/O blocks and perform benchmarking
    for (int idx =BS_Start_Idx;idx <=BS_Stop_Idx;++idx) {

        size_t idx_t = static_cast<size_t>(idx);
        CurrentBlockSize = static_cast<unsigned long>(blockSizeVec[idx_t]);

        // append the current block size to the GUI control
        //gui_interface->appendToBlockSize(IoSizeTagsVec[idx_t]);
        /// store the current block size to the vectors
        measuredBlockSizeVec.push_back(IoSizeTagsVec[idx_t]);

        /// Starting from a disk write.
        {

            /// create our file object
            FileManager file(FilePath, !directMode);

            /// try to create the file
            if(file.Create() == false)
            {
                gui_interface->updateStatusMessage("Cannot create the write file.");
                finishedBenchmarking();
                delete[] ReadData;
                delete[] WriteData;
                return 0;
            }

            counter = 0;
            unsigned long long IOCount = CurrentFileSize / CurrentBlockSize;
            IOCount = std::max(IOCount, static_cast<unsigned long long>(10));
            IOCount = std::min(IOCount, static_cast<unsigned long long>(30000));


            /// get the current time frame
            watch.Start();
            /// start writing to the file
            while(counter < IOCount){
                unsigned int __bytes = file.Write(reinterpret_cast<char*>(WriteData), CurrentBlockSize);
                if(__bytes == 0)
                {
                    gui_interface->updateStatusMessage("Failed to write to the file.");
                    finishedBenchmarking();
                    delete[] ReadData;
                    delete[] WriteData;
                    return 0;
                }
                counter+=1;

            }

            /// stop the time and get the different in time
            double timediff = watch.Stop();

            /// calculate the rate
            rate = (IOCount*CurrentBlockSize) / (timediff*1.0e6);

            /// store the current write rate to the vectors
            measuredWriteRateVec.push_back(attachTag(rate));

            /// append the current block size to the GUI control
            gui_interface->appendToWriteRate(attachTag(rate));

            /// wait for a little bit and try to close the file
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            file.Close();
        }

        /// Moving to a disk read.
        {
            /// create the file object
            FileManager file(FilePath, !directMode);
            /// try to open the file
            if(file.Open() == false)
            {
                gui_interface->appendToWriteRate("Cannot create the read file.");
                finishedBenchmarking();
                delete[] ReadData;
                delete[] WriteData;
                return 0;
            }

            counter = 0;
            long __bytes;

            /// get the current time frame
            watch.Start();

            /// Start reading from the file
            while(true){
                __bytes = file.Read(reinterpret_cast<char*>(ReadData), CurrentBlockSize);
                if(__bytes <= 0){
                    break;
                }
                if(CheckData)
                {
                    bool result = memcmp(ReadData,WriteData,CurrentBlockSize);
                    if(result != 0)
                    {
                        gui_interface->appendToWriteRate("Failed the data validation.");
                        finishedBenchmarking();
                        return 0;
                    }
                }

                counter+=1;
            }

            /// stop the time and get the different in time
            double timediff = watch.Stop();

            /// calculate the rate
            long long num1 = (counter*(CurrentBlockSize<1000? CurrentBlockSize : CurrentBlockSize/1000));
            double num2 =  (timediff*1.0e6);
            rate =  CurrentBlockSize<1000? (num1/num2): (num1/num2)*1000;

            /// store the current write rate to the vectors
            measuredReadRateVec.push_back(attachTag(rate));
            /// append the current block size to the GUI control
            gui_interface->appendToReadRate(attachTag(rate));

            /// wait for a little bit and try to close the file
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            file.Close();
        }
        /// calculate benchmark progress
        BenchmarkProgress = float(float(idx)/float(number_of_runs)) * 100;

        gui_interface->updateStatusMessage("Benchmarking is in the process...");

        /// remove the file
        remove(FilePath.c_str());
    }

    /// remove and delete buffer objects
    delete[] ReadData;
    delete[] WriteData;

    remove(FilePath.c_str());

    /// generate the report if user wants
    if(report)
        generateReport();

    /// flag the GUI benchmarking is done
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    gui_interface->updateStatusMessage("Finished Benchmarking.");
    finishedBenchmarking();

    return 1;
}

///
///  appManager::FinishedBenchmarking().
///
/// Flag some GUI controls that the benchmarking process is finished.
///

void appManager::finishedBenchmarking()
{
    gui_interface->restrictGUIElements(true);
}
