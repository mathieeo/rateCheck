#ifndef file_managerbH
#define file_managerbH

#include <string>
#include <stdio.h>

#ifndef LINUX
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#endif

namespace rateCheckApp
{

typedef uint64_t int64;

class IFileManagerImpl;

///
///  CLASS FileManager.
///  Disk file access support class
///

class FileManager
{
public:
    // Ctors
    FileManager(bool useStdioFile = true);
    FileManager(const std::string & filename, bool useStdioFile = true);
    FileManager(const FileManager & other);
    ~FileManager();

    // Assignment
    FileManager & operator = (const FileManager & other);

    // Methods
    bool            Open();
    bool            Opened() const;
    bool            Create();
    bool            Append();
    bool            Close();

    int    Write(const char * buffer, unsigned int size);
    int Read(char * buffer, unsigned int size);

    // Properties
    void            WriteThrough(bool state);
    bool            WriteThrough() const;

    void            Size(int64 size);
    int64            Size() const;

    void            FileName(const std::string & name);
    std::string     FileName() const;

    bool            Position(int64 value);
    int64            Position() const;

    bool            isStdioFile() const { return _useStdioFile; }
private:
    bool _useStdioFile;
    IFileManagerImpl *   Impl;
};



//=============================================================================
//  CLASS IFileManager  --
//=============================================================================

class IFileManagerImpl
{

public:
    virtual ~IFileManagerImpl() { }

    virtual bool            Open() = 0;
    virtual bool            Opened() const = 0;
    virtual bool            Append() = 0;
    virtual bool            Create() = 0;
    virtual bool            Close() = 0;

    virtual int    Write(const char * buffer, unsigned int size) = 0;
    virtual int    Read(char * buffer, unsigned int size) = 0;

    virtual void            Size(int64 size) = 0;
    virtual int64            Size() const = 0;

    virtual void            FileName(const std::string & name) = 0;
    virtual std::string     FileName() const = 0;

    virtual bool            Position(int64 value) = 0;
    virtual int64            Position() const = 0;

};


//=============================================================================
//  CLASS StdFileManager  --
//=============================================================================


class StdFileManager : public IFileManagerImpl
{
public:
    StdFileManager();
    // Assignment
    StdFileManager(const StdFileManager & other);
    StdFileManager & operator = (const StdFileManager & other);
    ~StdFileManager();

    virtual bool            Open();
    virtual bool            Opened() const
    {  return Handle != NULL;  }
    virtual bool            Append() ;
    virtual bool            Create() ;
    virtual bool            Close() ;

    virtual int    Write(const char * buffer, unsigned int size) ;
    virtual int    Read(char * buffer, unsigned int size) ;

    virtual void            Size(int64 size) ;
    virtual int64            Size() const ;

    virtual void            FileName(const std::string & name) ;
    virtual std::string     FileName() const ;

    virtual bool            Position(int64 value) ;
    virtual int64            Position() const ;

protected:

    // Data
    FILE *	    Handle;
    std::string     FFileName;
    int64            FPosition;
    int64            FSize;

    void            GetSize();
};


#ifndef LINUX
//=============================================================================
//  CLASS FileAPIFileManager  --
//=============================================================================


class FileAPIFileManager : public IFileManagerImpl
{
public:
    FileAPIFileManager();
    // Assignment
    FileAPIFileManager(const FileAPIFileManager & other);
    FileAPIFileManager & operator = (const FileAPIFileManager & other);
    ~FileAPIFileManager();

    virtual bool            Open();
    virtual bool            Opened() const
    { return isOpen;   }
    virtual bool            Append() ;
    virtual bool            Create() ;
    virtual bool            Close() ;

    virtual int    Write(const char * buffer, unsigned int size) ;
    virtual int    Read(char * buffer, unsigned int size) ;

    virtual void            Size(int64 size) ;
    virtual int64            Size() const ;

    virtual void            FileName(const std::string & name) ;
    virtual std::string     FileName() const ;

    virtual bool            Position(int64 value) ;
    virtual int64            Position() const ;

protected:

    // Data
    //
    HANDLE          Handle;
    std::string     FFileName;
    long long       FPosition;
    long long       FSize;
    bool            isOpen;

    void            GetSize();
};
#else

class FileAPIFileManager : public IFileManagerImpl
{
public:
    FileAPIFileManager();
    // Assignment
    FileAPIFileManager(const FileAPIFileManager & /*other*/);
    FileAPIFileManager & operator = (const FileAPIFileManager & /*other*/);
    ~FileAPIFileManager();

    virtual bool            Open();
    virtual bool            Opened() const;
    virtual bool            Append();
    virtual bool            Create();
    virtual bool            Close();

    virtual int Write(const char * /*buffer*/, unsigned int /*size*/);
    virtual int    Read(char * /*buffer*/, unsigned int /*size*/);

    virtual void            Size(int64 /*size*/) ;
    virtual int64            Size() const;

    virtual void            FileName(const std::string & /*name*/);
    virtual std::string     FileName() const;

    virtual bool            Position(int64 /*value*/);
    virtual int64            Position() const;

protected:

    // Data
    //
    int          Handle;
    std::string     FFileName;
    long long       FPosition;
    long long       FSize;
    bool            isOpen;

    void            GetSize();
};
#endif

}  // namespace

#endif
