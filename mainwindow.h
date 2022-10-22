#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <appManager.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GUI_Interface_Impl;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_pushButton_2_clicked();

    void on_StartStopButton_clicked();

public:

    friend class GUI_Interface_Impl;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool SelectFileDialog(std::string & file, const std::string & filter);

    unsigned int blockSizeStartIndex();
    unsigned int blockSizeEndIndex() ;
    unsigned int fileSizeComboIndex() ;
    bool isValidateChecked() ;
    std::string rootDirectory() ;
    void updateStatusMessage(std::string msg) ;
    void appendToBlockSize(std::string size) ;
    void appendToWriteRate(std::string size) ;
    void appendToReadRate(std::string size) ;
    void restrictGUIElements(bool state);
    void updateProgressBar(int value);


    GUI_Interface_Impl * UI;
    appManager *manager;

    Ui::MainWindow *ui;

   // HANDLE WriteFileHandle;
  //  HANDLE ReadFileHandle;

};


class GUI_Interface_Impl : public GUI_Interface
{
public:
    GUI_Interface_Impl(MainWindow * form)
        : Form(form)
    { }

    virtual ~GUI_Interface_Impl() { }

    virtual unsigned int blockSizeStartIndex() { return Form->blockSizeStartIndex(); }
    virtual unsigned int blockSizeEndIndex() { return Form->blockSizeEndIndex(); }
    virtual unsigned int fileSizeComboIndex() { return Form->fileSizeComboIndex(); }
    virtual bool isValidateChecked() { return Form->isValidateChecked(); }
    virtual std::string rootDirectory() { return Form->rootDirectory(); }
    virtual void updateStatusMessage(std::string msg) { Form->updateStatusMessage(msg); }
    virtual void appendToBlockSize(std::string size) { Form->appendToBlockSize(size); }
    virtual void appendToWriteRate(std::string size){ Form->appendToWriteRate(size); }
    virtual void appendToReadRate(std::string size) { Form->appendToReadRate(size); }
    virtual void restrictGUIElements(bool state) { Form->restrictGUIElements(state); }
    virtual void updateProgressBar(int value) { Form->updateProgressBar(value); }

protected:
    MainWindow *  Form;
};

#endif // MAINWINDOW_H
