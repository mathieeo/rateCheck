#ifndef file_managerbH
#define file_managerbH

#include <string>
#include <stdio.h>

#ifndef LINUX
#include <windows.h>
#endif

namespace rateCheckApp
{
#ifdef __CLR_VER
#pragma managed(push, off)
#endif

typedef unsigned long ii64;
//===========================================================================
//  CLASS  FileManager   ---  Large disk file access support class
//===========================================================================

class IFileManagerImpl;

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

    unsigned int    Write(const char * buffer, unsigned int size);
    unsigned int    Read(char * buffer, unsigned int size);

    // Properties
    void            WriteThrough(bool state);
    bool            WriteThrough() const;

    void            Size(ii64 size);
    ii64            Size() const;

    void            FileName(const std::string & name);
    std::string     FileName() const;

    bool            Position(ii64 value);
    ii64            Position() const;

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

    virtual unsigned int    Write(const char * buffer, unsigned int size) = 0;
    virtual unsigned int    Read(char * buffer, unsigned int size) = 0;

    virtual void            Size(ii64 size) = 0;
    virtual ii64            Size() const = 0;

    virtual void            FileName(const std::string & name) = 0;
    virtual std::string     FileName() const = 0;

    virtual bool            Position(ii64 value) = 0;
    virtual ii64            Position() const = 0;

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

    virtual unsigned int    Write(const char * buffer, unsigned int size) ;
    virtual unsigned int    Read(char * buffer, unsigned int size) ;

    virtual void            Size(ii64 size) ;
    virtual ii64            Size() const ;

    virtual void            FileName(const std::string & name) ;
    virtual std::string     FileName() const ;

    virtual bool            Position(ii64 value) ;
    virtual ii64            Position() const ;

protected:

    // Data
    FILE *	    Handle;
    std::string     FFileName;
    ii64            FPosition;
    ii64            FSize;

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

    virtual unsigned int    Write(const char * buffer, unsigned int size) ;
    virtual unsigned int    Read(char * buffer, unsigned int size) ;

    virtual void            Size(ii64 size) ;
    virtual ii64            Size() const ;

    virtual void            FileName(const std::string & name) ;
    virtual std::string     FileName() const ;

    virtual bool            Position(ii64 value) ;
    virtual ii64            Position() const ;

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
    FileAPIFileManager() { }
    // Assignment
    FileAPIFileManager(const FileAPIFileManager & /*other*/) { }
    //FileAPIFileManager & operator = (const FileAPIFileManager & /*other*/){  }
    ~FileAPIFileManager(){ }

    virtual bool            Open(){ return false; }
    virtual bool            Opened() const
     { return false;   }
    virtual bool            Append() { return false; }
    virtual bool            Create() { return false; }
    virtual bool            Close(){ return false; }

    virtual unsigned int    Write(const char * /*buffer*/, unsigned int /*size*/) { return 0; }
    virtual unsigned int    Read(char * /*buffer*/, unsigned int /*size*/){ return 0; }

    virtual void            Size(ii64 /*size*/) { }
    virtual ii64            Size() const { return 0; }

    virtual void            FileName(const std::string & /*name*/) { }
    virtual std::string     FileName() const { return ""; }

    virtual bool            Position(ii64 /*value*/) { return false; }
    virtual ii64            Position() const { return 0; }
};
#endif


#ifdef __CLR_VER
#pragma managed(pop)
#endif
}  // namespace Innovative

#endif
