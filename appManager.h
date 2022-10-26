#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <vector>
#include <string>

const long long Kay = 1024;
const long long Meg = 1024*1024;
const long long Geg = 1024*1024*1024;
const long long AlignedBlockSize = 512;


///
///  Class GUI_Interface
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
///  Class appManager
///

class appManager {

public:
    appManager(GUI_Interface* _gui_interface);
    ~appManager();

    int StartWorking(bool directMode, bool report=true);
    void FinishedBenchmarking();
    void fillRandomly(unsigned int size, int *ptr);
    std::string AttachTag(double rate);
    std::string generateReport();


    std::vector<std::string> measuredReadRateVec;
    std::vector<std::string> measuredWriteRateVec;
    std::vector<std::string> measuredBlockSizeVec;
    std::vector<unsigned long long> blockSizeVec;
    std::vector<unsigned long long> FileSizeVec;
    std::vector<unsigned long long> IoCountVec;
    std::vector<std::string>    IoSizeTagsVec;

    float BenchmarkProgress;

private:
    GUI_Interface *gui_interface;

};

#endif // APPMANAGER_H
