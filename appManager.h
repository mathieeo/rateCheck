///
/// appManager.h
///

#ifndef APPMANAGER_H
#define APPMANAGER_H

// include
#include <vector>
#include <string>

// const prams
const long long Kay = 1024;
const long long Meg = 1024*1024;
const long long Geg = 1024*1024*1024;
const long long AlignedBlockSize = 512;


///
///  Class GUI_Interface
/// Abstract class for accessing the GUI controls.
///

class GUI_Interface{
public:
     GUI_Interface() { }
    virtual ~GUI_Interface() { }

    virtual unsigned int blockSizeStartIndex() = 0;
    virtual unsigned int blockSizeEndIndex() = 0;
    virtual unsigned int fileSizeComboIndex() = 0;
    virtual bool isValidateChecked() = 0;
    virtual std::string rootDirectory() = 0;
    virtual void updateStatusMessage(std::string msg) = 0;
    virtual void appendToBlockSize(std::string size) = 0;
    virtual void appendToWriteRate(std::string size) = 0;
    virtual void appendToReadRate(std::string size) = 0;
    virtual void restrictGUIElements(bool state) = 0;
    virtual void updateProgressBar(int value) = 0;
};


///
///  Class appManager;
/// This class handles the file managements and benchmarking routines.
///

class appManager {

public:

    ///< Constractor
    appManager(GUI_Interface* _gui_interface);
    ~appManager();

    ///< Start benchmarking is the main process to start benchmarking, the function takes two booloan prams.
    ///< directMode - avoid caching the file to the host RAM usually done by the std methods.
    ///< report - by default report variable is set to true to generate report after finishing the benchmarking.
    int startBenchmarking(bool directMode, bool report=true);
    ///< Flag some GUI controls that the benchmarking process is finished.
    void finishedBenchmarking();
    ///< Fill random data to the buffer.
    void fillRandomly(unsigned int size, int *ptr);
    ///< helper function to attach the rate tag next to the rate for example 11234 B/S rate will be 111.234 GB/S
    std::string attachTag(double rate);
    ///< Generate report function; creates a txt file with the details.
    std::string generateReport();


    ///< vector for storing the measured read rates used when generating the report file.
    std::vector<std::string> measuredReadRateVec;
    ///< vector for storing the measured write rates used when generating the report file.
    std::vector<std::string> measuredWriteRateVec;
    ///< vector for storing the measured I/O block size used when generating the report file.
    std::vector<std::string> measuredBlockSizeVec;

    ///< vector for all the supported I/O block sizes.
    std::vector<unsigned long long> blockSizeVec;
    ///< vector for all the supported file sizes.
    std::vector<unsigned long long> FileSizeVec;
    ///< vector for the I/O block count.
    std::vector<unsigned long long> IoCountVec;
    ///< vector for all the supported I/O block sizes.
    std::vector<std::string>    IoSizeTagsVec;


    ///< a local getter function for accessing the benchmark progress.
    float benchmarkProgress() { return BenchmarkProgress; }
private:
    GUI_Interface *gui_interface;
    ///< a local public pram for accessing the benchmark progress.
    float BenchmarkProgress;

};

#endif // APPMANAGER_H
