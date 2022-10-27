///
/// mainwindow.h
///

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// include
#include <QMainWindow>
#include <vector>
#include <appManager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// friend class to implement the GUI abstract class defined in appManager.h
class GUI_Interface_Impl;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:

    /// browse to the directory to perform benchmarking
    void on_dirBrowseBtn_clicked();
    /// start performing the benchmark
    void on_StartBtn_clicked();
    /// go to the website
    void on_AboutBtn_clicked();

public:

    /// friend class to implement the GUI abstract class defined in appManager.h
    friend class GUI_Interface_Impl;

    /// constructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /// push the directory browse view
    bool SelectFileDialog(std::string & file, const std::string & filter);

    /// get the start I/O block size index from the GUI combobox
    unsigned int blockSizeStartIndex();
    /// get the end IO block size index from the GUI combobox
    unsigned int blockSizeEndIndex() ;
    /// get the file size index from the GUI combobox
    unsigned int fileSizeComboIndex() ;
    /// user want to validate the write data?
    bool isValidateChecked() ;
    /// get the root directory
    std::string rootDirectory() ;
    /// update the status message on the GUI
    void updateStatusMessage(std::string msg) ;
    /// append the new I/O block size to the GUI
    void appendToBlockSize(std::string size) ;
    /// append the new write rate to the GUI
    void appendToWriteRate(std::string size) ;
    /// append the new read rate to the GUI
    void appendToReadRate(std::string size) ;
    /// enable or disable the GUI controls
    void restrictGUIElements(bool state);
    /// update the GUI progreess bar
    void updateProgressBar(int value);
    /// go to the website function
    void goToWebsite();

    /// GUI interface object
    GUI_Interface_Impl * UI;
    /// appManager object
    appManager *manager;

    /// Ui Mainwindow object
    Ui::MainWindow *ui;

};

///
///  Class GUI_Interface_Impl driven from the abstract class GUI_Interface.
///
/// class for accessing the GUI controls.
///
class GUI_Interface_Impl : public GUI_Interface
{
public:
    /// construction takes a reference from the GUI object so we can call the GUI setters and getters
    GUI_Interface_Impl(MainWindow * form)
        : Form(form)
    { }

    virtual ~GUI_Interface_Impl() { }

    /// get the start I/O block size index from the GUI combobox
    virtual unsigned int blockSizeStartIndex() { return Form->blockSizeStartIndex(); }
    /// get the end IO block size index from the GUI combobox
    virtual unsigned int blockSizeEndIndex() { return Form->blockSizeEndIndex(); }
    /// get the file size index from the GUI combobox
    virtual unsigned int fileSizeComboIndex() { return Form->fileSizeComboIndex(); }
    /// user want to validate the write data?
    virtual bool isValidateChecked() { return Form->isValidateChecked(); }
    /// get the root directory
    virtual std::string rootDirectory() { return Form->rootDirectory(); }
    /// update the status message on the GUI
    virtual void updateStatusMessage(std::string msg) { Form->updateStatusMessage(msg); }
    /// append the new I/O block size to the GUI
    virtual void appendToBlockSize(std::string size) { Form->appendToBlockSize(size); }
    /// append the new write rate to the GUI
    virtual void appendToWriteRate(std::string size){ Form->appendToWriteRate(size); }
    /// append the new read rate to the GUI
    virtual void appendToReadRate(std::string size) { Form->appendToReadRate(size); }
    /// enable or disable the GUI controls
    virtual void restrictGUIElements(bool state) { Form->restrictGUIElements(state); }
    /// update the GUI progreess bar
    virtual void updateProgressBar(int value) { Form->updateProgressBar(value); }

protected:
    MainWindow *  Form;
};

#endif // MAINWINDOW_H
