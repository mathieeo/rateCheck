///
/// appManager.h
///

#ifndef APPMANAGER_H
#define APPMANAGER_H

/// include
#include <vector>
#include <string>

/// const prams
const long long AlignedBlockSize = 512;

constexpr unsigned long long kB = 1024;
constexpr unsigned long long MB = 1024 * 1024;
constexpr unsigned long long GB = 1024 * 1024 * 1024;

enum class BlockSize {
  bs512B = 512,
  bs1KB = 1 * kB,
  bs2KB = 2 * kB,
  bs4KB = 4 * kB,
  bs8KB = 8 * kB,
  bs16KB = 16 * kB,
  bs32KB = 32 * kB,
  bs64KB = 64 * kB,
  bs128KB = 128 * kB,
  bs256KB = 256 * kB,
  bs512KB = 512 * kB,
  bs1MB = 1 * MB,
  bs2MB = 2 * MB,
  bs4MB = 4 * MB,
  bs8MB = 8 * MB,
  bs16MB = 16 * MB,
  bs32MB = 32 * MB,
  bs64MB = 64 * MB,
  bs128MB = 128 * MB,
  bs256MB = 256 * MB,
};

///
///  Class GUI_Interface
///
/// Abstract class for accessing the GUI controls.
///

class GUI_Interface{
public:
     GUI_Interface() { }
    virtual ~GUI_Interface() { }

    /// get the start I/O block size index from the GUI combobox
    virtual unsigned int blockSizeStartIndex() = 0;
    /// get the end IO block size index from the GUI combobox
    virtual unsigned int blockSizeEndIndex() = 0;
     /// get the file size index from the GUI combobox
    virtual unsigned int fileSizeComboIndex() = 0;
     /// user want to validate the write data?
    virtual bool isValidateChecked() = 0;
     /// get the root directory
    virtual std::string rootDirectory() = 0;
     /// update the status message on the GUI
    virtual void updateStatusMessage(std::string msg) = 0;
     /// append the new I/O block size to the GUI
    virtual void appendToBlockSize(std::string size) = 0;
     /// append the new write rate to the GUI
    virtual void appendToWriteRate(std::string size) = 0;
     /// append the new read rate to the GUI
    virtual void appendToReadRate(std::string size) = 0;
     /// enable or disable the GUI controls
    virtual void restrictGUIElements(bool state) = 0;
     /// update the GUI progreess bar
    virtual void updateProgressBar(int value) = 0;
};


///
///  Class appManager;
///
/// This class handles the file managements and benchmarking routines.
///

class appManager {

public:

    /// Constractor
    appManager(GUI_Interface* _gui_interface);
    ~appManager();

    /// Start benchmarking is the main process to start benchmarking, the function takes two booloan prams.
    /// directMode - avoid caching the file to the host RAM usually done by the std methods.
    /// report - by default report variable is set to true to generate report after finishing the benchmarking.
    int startBenchmarking(bool directMode, bool report=true);
    /// Flag some GUI controls that the benchmarking process is finished.
    void finishedBenchmarking();
    /// Fill random data to the buffer.
    void fillRandomly(unsigned int size, int *ptr);
    /// helper function to attach the rate tag next to the rate for example 11234 B/S rate will be 111.234 GB/S
    std::string attachTag(double rate);
    /// Generate report function; creates a txt file with the details.
    std::string generateReport();


    /// vector for storing the measured read rates used when generating the report file.
    std::vector<std::string> measuredReadRateVec;
    /// vector for storing the measured write rates used when generating the report file.
    std::vector<std::string> measuredWriteRateVec;
    /// vector for storing the measured I/O block size used when generating the report file.
    std::vector<std::string> measuredBlockSizeVec;

    /// vector for all the supported I/O block sizes.
    std::vector<unsigned long long> blockSizeVec;
    /// vector for all the supported file sizes.
    std::vector<unsigned long long> FileSizeVec;
    /// vector for the I/O block count.
    std::vector<unsigned long long> IoCountVec;
    /// vector for all the supported I/O block sizes.
    std::vector<std::string>    IoSizeTagsVec;


    /// a local getter function for accessing the benchmark progress.
    float benchmarkProgress() { return BenchmarkProgress; }
private:
    GUI_Interface *gui_interface;
    /// a local public pram for accessing the benchmark progress.
    float BenchmarkProgress;

};

#endif // APPMANAGER_H
