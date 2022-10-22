#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <vector>

using namespace std;

const long long Kay = 1024;
const long long Meg = 1024*1024;
const long long Geg = 1024*1024*1024;
const long long AlignedBlockSize = 512;


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


class appManager {

public:
    appManager(GUI_Interface* _gui_interface);
    ~appManager();

    int StartWorking(bool directMode);
    void FinishedBenchmarking();
    void fillRandomly(unsigned int size, int *ptr);
    std::string AttachTag(double rate);


    vector<unsigned long long> blockSizeVec;
    vector<unsigned long long> FileSizeVec;
    vector<unsigned long long> IoCountVec;
    vector<string>    IoSizeTagsVec;

private:
    GUI_Interface *gui_interface;

};

#endif // APPMANAGER_H
