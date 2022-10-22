#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const long long Kay = 1024;
const long long Meg = 1024*1024;
const long long Geg = 1024*1024*1024;
const long long AlignedBlockSize = 512;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_pushButton_2_clicked();

    void on_StartStopButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void StartWorking();
    bool SelectFileDialog(std::string & file, const std::string & filter);
    void FinishedBenchmarking();
    void fillRandomly(unsigned int size, int *ptr);
    std::string AttachTag(double rate);


    vector<unsigned long long> blockSizeVec;
    vector<unsigned long long> FileSizeVec;
    vector<unsigned long long> IoCountVec;
    vector<string>    IoSizeTagsVec;
    Ui::MainWindow *ui;
   // HANDLE WriteFileHandle;
  //  HANDLE ReadFileHandle;

};
#endif // MAINWINDOW_H
