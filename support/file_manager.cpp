#include <file_manager.h>
#include <iostream>
#include <malloc.h>

#if defined(LINUX)
#undef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS	64
#endif

namespace rateCheckApp
{


//=============================================================================
//  CLASS StdFileManager  --
//=============================================================================

//---------------------------------------------------------------------------
//  StdFileManager::StdFileManager() --  Ctor
//---------------------------------------------------------------------------

StdFileManager::StdFileManager()
    : Handle(nullptr),
      FFileName(std::string("")), FPosition(0), FSize(0)
{
}

//---------------------------------------------------------------------------
// StdFileManager::FileManagerImpl() --
//---------------------------------------------------------------------------

StdFileManager::StdFileManager(const StdFileManager & other)
    : Handle(nullptr),
      FFileName(other.FFileName),
      FPosition(other.FPosition),
      FSize(other.FSize)
{
}

//---------------------------------------------------------------------------
//  StdFileManager::operator = --  Assignment operator
//---------------------------------------------------------------------------

StdFileManager & StdFileManager::operator = (const StdFileManager & other)
{
    // protect against invalid self-assignment
    if (this != &other)
    {
        Handle = nullptr;
        FFileName = other.FFileName;
        FPosition = other.FPosition;
        FSize = other.FSize;
    }

    // by convention, always return *this
    return *this;
}

//---------------------------------------------------------------------------
//  StdFileManager::~StdFileManager() --  Set file buffer mode state
//---------------------------------------------------------------------------

StdFileManager::~StdFileManager()
{
    Close();
}


//---------------------------------------------------------------------------
//  StdFileManager::GetSize() --  Get current file size
//---------------------------------------------------------------------------

void StdFileManager::GetSize()
{
    off_t offset = 0;
    fseek(Handle, offset, SEEK_END);
    clearerr(Handle);
    FSize = static_cast<int64>(ftell(Handle));
}

//---------------------------------------------------------------------------
//  StdFileManager::Open() --  Open file for reading
//---------------------------------------------------------------------------

bool StdFileManager::Open()
{
    if (Opened())
        return false;

    Handle = fopen(FFileName.c_str(), "rb");

    if (!Opened())
        throw std::string("Unable to open file");

    // Cache file size
    GetSize();
    Position(0);

    return true;
}

//---------------------------------------------------------------------------
//  StdFileManager::Create() --  Create file for writing
//---------------------------------------------------------------------------

bool StdFileManager::Create()
{
    if (Opened())
        return false;

    remove(FileName().c_str());

    Handle = fopen(FFileName.c_str(), "w+b");

    if (!Opened())
        throw std::string("Unable to create file");

    Position(0);

    return true;
}

//---------------------------------------------------------------------------
//  StdFileManager::Append() --  Open file for append
//---------------------------------------------------------------------------

bool StdFileManager::Append()
{
    if (Opened())
        return false;

    Handle = fopen(FFileName.c_str(), "r+b");

    if (!Opened())
        throw std::string("Unable to append file");

    // Cache file size
    GetSize();
    Position(FSize);

    return true;
}

//---------------------------------------------------------------------------
//  StdFileManager::Close() --
//---------------------------------------------------------------------------

bool StdFileManager::Close()
{
    if (!Opened())
    { return true;}

    bool Result = fclose(Handle);
    Handle = nullptr;

    FSize = 0;
    FPosition = 0;

    return Result;
}

//---------------------------------------------------------------------------
//  StdFileManager::Read() --
//---------------------------------------------------------------------------

int StdFileManager::Read(char * buffer, unsigned int size)
{
    if (!Opened())
        return 0;

    size_t result;
    result = fread(buffer, 1, static_cast<size_t>(size), Handle);
    FPosition += result;

    return static_cast<unsigned int>(result);
}

//---------------------------------------------------------------------------
//  StdFileManager::Write() --
//---------------------------------------------------------------------------

int StdFileManager::Write(const char * buffer, unsigned int size)
{
    if (!Opened())
        return 0;

    size_t result;
    result = fwrite(buffer, 1, size, Handle);
    FPosition += result;
    FSize = std::max<int64>(FPosition, FSize);

    return static_cast<unsigned int>(result);
}

//---------------------------------------------------------------------------
//  StdFileManager::FileName() --  Set file name
//---------------------------------------------------------------------------

void StdFileManager::FileName(const std::string & name)
{
    FFileName = name;
}

//---------------------------------------------------------------------------
//  StdFileManager::FileName() --  Get file name
//---------------------------------------------------------------------------

std::string StdFileManager::FileName() const
{
    return FFileName;
}

//---------------------------------------------------------------------------
//  StdFileManager::Position() --
//---------------------------------------------------------------------------

bool StdFileManager::Position(int64 offset)
{
    if (!Opened())
    { return false;}

    off_t position = static_cast<off_t>(offset);
    int result = fseek(Handle, position, SEEK_SET);

    return (result == 0);
}

//---------------------------------------------------------------------------
//  StdFileManager::Position() --
//---------------------------------------------------------------------------

int64 StdFileManager::Position() const
{
    return FPosition;
}

//---------------------------------------------------------------------------
//  StdFileManager::Size() --  Set file size
//---------------------------------------------------------------------------

void StdFileManager::Size(int64 size)
{
    Position(size);
    Write("\0", 1);

    FSize = size;
}

//---------------------------------------------------------------------------
//  StdFileManager::Size() --  Get file size
//---------------------------------------------------------------------------

int64 StdFileManager::Size() const
{
    return FSize;
}


#ifndef LINUX
//=============================================================================
//  CLASS FileAPIFileManager  --
//=============================================================================

//---------------------------------------------------------------------------
//  FileAPIFileManager::FileAPIFileManager() --  Ctor
//---------------------------------------------------------------------------

FileAPIFileManager::FileAPIFileManager()
    : FFileName(std::string("")), FPosition(0), FSize(0), isOpen(false)
{
}

//---------------------------------------------------------------------------
// FileAPIFileManager::FileAPIFileManager() --
//---------------------------------------------------------------------------

FileAPIFileManager::FileAPIFileManager(const FileAPIFileManager & other)
{
    FFileName = other.FFileName;
    FPosition = other.FPosition;
    FSize = other.FSize;
    isOpen = other.isOpen;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::operator = --  Assignment operator
//---------------------------------------------------------------------------

FileAPIFileManager & FileAPIFileManager::operator = (const FileAPIFileManager & other)
{
    // protect against invalid self-assignment
    if (this != &other)
    {
        Handle = nullptr;
        FFileName = other.FFileName;
        FPosition = other.FPosition;
        FSize = other.FSize;
        isOpen = other.isOpen;
    }

    // by convention, always return *this
    return *this;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::~FileAPIFileManager() --  Set file buffer mode state
//---------------------------------------------------------------------------

FileAPIFileManager::~FileAPIFileManager()
{
    Close();
}


//---------------------------------------------------------------------------
//  FileAPIFileManager::GetSize() --  Get current file size
//---------------------------------------------------------------------------

void FileAPIFileManager::GetSize()
{
    unsigned long  high = 0;

    DWORD size = GetFileSize(Handle, &high);
    FSize = size;

    if(high!=0){
        long long newHigh = high;
        newHigh = newHigh << 32;
        FSize = newHigh + size;
    }

}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Open() --  Open file for reading
//---------------------------------------------------------------------------

bool FileAPIFileManager::Open()
{
    Handle = CreateFileA(FFileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , nullptr);
    if (Handle == INVALID_HANDLE_VALUE)
    {
        throw std::string("Unable to open file");
    }

    // Cache file size
    GetSize();
    Position(0);
    isOpen = true;
    return true;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Create() --  Create file for writing
//---------------------------------------------------------------------------

bool FileAPIFileManager::Create()
{
    remove(FileName().c_str());

    Handle = CreateFileA(FFileName.c_str(), GENERIC_ALL, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING , nullptr);

    if (Handle == INVALID_HANDLE_VALUE)
        throw std::string("Unable to create file");

    Position(0);
    isOpen = true;

    return true;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Append() --  Open file for append
//---------------------------------------------------------------------------

bool FileAPIFileManager::Append()
{
    return false;
    //    if (Opened())
    //        return false;

    //    Handle = CreateFileA(FFileName.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , nullptr);

    //    if (!Opened())
    //        throw MalibuException("Unable to append file");

    //    // Cache file size
    //    GetSize();
    //    Position(FSize);

    //    return true;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Close() --
//---------------------------------------------------------------------------

bool FileAPIFileManager::Close()
{
    try {
        if(Opened())
            CloseHandle(Handle);
        FSize = 0;
        FPosition = 0;
        isOpen = false; //if not closed properly the result is zero

        return true;
    } catch (...) {
        return false;
    }


}

//---------------------------------------------------------------------------
//  StdFileManager::FileAPIFileManager() --
//---------------------------------------------------------------------------

int FileAPIFileManager::Read(char * buffer, unsigned int size)
{
    unsigned long result = 0;

    ReadFile(Handle, buffer, size, &result, nullptr);
    FPosition += result;

    return static_cast<int>(result);
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Write() --
//---------------------------------------------------------------------------

int FileAPIFileManager::Write(const char * buffer, unsigned int size)
{
    unsigned long result;
    WriteFile(Handle, buffer, size, &result, nullptr);
    FPosition += result;
    FSize = std::max<long long>(FPosition, FSize);

    return static_cast<int>(result);
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::FileName() --  Set file name
//---------------------------------------------------------------------------

void FileAPIFileManager::FileName(const std::string & name)
{
    FFileName = name;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::FileName() --  Get file name
//---------------------------------------------------------------------------

std::string FileAPIFileManager::FileName() const
{
    return FFileName;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Position() --
//---------------------------------------------------------------------------

bool FileAPIFileManager::Position(int64 offset)
{
    if(offset > 2)
        return false;
    /*
FILE_BEGIN 0
FILE_CURRENT 1
FILE_END 2
*/
    LONG position = static_cast<LONG>(offset);

    bool result = SetFilePointer(Handle, position, nullptr, FILE_BEGIN);

    FPosition = position;

    return (result == 0);
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Position() --
//---------------------------------------------------------------------------

int64 FileAPIFileManager::Position() const
{
    return FPosition;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Size() --  Set file size
//---------------------------------------------------------------------------

void FileAPIFileManager::Size(int64 size)
{
    Position(size);
    Write("\0", 1);

    FSize = size;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Size() --  Get file size
//---------------------------------------------------------------------------

int64 FileAPIFileManager::Size() const
{
    return FSize;
}
#else
//=============================================================================
//  CLASS FileAPIFileManager  --
//=============================================================================

//---------------------------------------------------------------------------
//  FileAPIFileManager::FileAPIFileManager() --  Ctor
//---------------------------------------------------------------------------

FileAPIFileManager::FileAPIFileManager()
    : FFileName(std::string("")), FPosition(0), FSize(0), isOpen(false)
{
}

//---------------------------------------------------------------------------
// FileAPIFileManager::FileAPIFileManager() --
//---------------------------------------------------------------------------

FileAPIFileManager::FileAPIFileManager(const FileAPIFileManager & other)
{
    Handle = other.Handle;
    FFileName = other.FFileName;
    FPosition = other.FPosition;
    FSize = other.FSize;
    isOpen = other.isOpen;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::operator = --  Assignment operator
//---------------------------------------------------------------------------

FileAPIFileManager & FileAPIFileManager::operator = (const FileAPIFileManager & other)
{
    // protect against invalid self-assignment
    if (this != &other)
    {
        Handle = other.Handle;
        FFileName = other.FFileName;
        FPosition = other.FPosition;
        FSize = other.FSize;
        isOpen = other.isOpen;
    }

    // by convention, always return *this
    return *this;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::~FileAPIFileManager() --  Set file buffer mode state
//---------------------------------------------------------------------------

FileAPIFileManager::~FileAPIFileManager()
{
    Close();
}


//---------------------------------------------------------------------------
//  FileAPIFileManager::GetSize() --  Get current file size
//---------------------------------------------------------------------------

void FileAPIFileManager::GetSize()
{
    // unsigned long  high = 0;

    //DWORD size = GetFileSize(Handle, &high);
    //    FSize = size;

    //    if(high!=0){
    //        long long newHigh = high;
    //        newHigh = newHigh << 32;
    //        FSize = newHigh + size;
    //    }

}
#ifdef MAC_OS
    #define O_DIRECT F_NOCACHE
#endif
//---------------------------------------------------------------------------
//  FileAPIFileManager::Open() --  Open file for reading
//---------------------------------------------------------------------------

bool FileAPIFileManager::Open()
{
    Handle = ::open(FFileName.c_str(), O_DIRECT | O_LARGEFILE, S_IRWXO | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if ( Handle == -1 ) {

        // check if value of errno same as value of EDOM i.e. 33

            std::cout << " Value of errno is : " << errno << '\n';
            std::cout << " log(-1) is not valid : "
                 << strerror(errno) << '\n';


        throw std::string("can't open input file!");
    }

    // Cache file size
    GetSize();
    Position(0);
    isOpen = true;
    return isOpen;
}

bool FileAPIFileManager::Opened() const
{
    return isOpen;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Create() --  Create file for writing
//---------------------------------------------------------------------------

bool FileAPIFileManager::Create()
{
    remove(FileName().c_str());
    Handle = ::creat(FFileName.c_str(), S_IRWXO | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if(Handle == -1){
        throw std::string("Unable to create file");
    }

    Position(0);
    isOpen = true;

    return isOpen;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Append() --  Open file for append
//---------------------------------------------------------------------------

bool FileAPIFileManager::Append()
{
    return false;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Close() --
//---------------------------------------------------------------------------

bool FileAPIFileManager::Close()
{
    try {
        bool Result = true;

        Result = ::close(Handle);
        FSize = 0;
        FPosition = 0;
        isOpen = false; //if not closed properly the result is zero

        return Result;
    } catch (...) {
        return false;
    }


}

//---------------------------------------------------------------------------
//  StdFileManager::FileAPIFileManager() --
//---------------------------------------------------------------------------

int FileAPIFileManager::Read(char * buffer, unsigned int size)
{
    long result;

#if defined(LINUX) && !defined(MAC_OS)
    int alignment = 4096;

    buffer = reinterpret_cast<char *>(memalign(alignment * 2, size + alignment));
    if (buffer == NULL)
        throw std::string("memalign");

    buffer += alignment;
#endif

    result = ::read(Handle,buffer, size);

    if(result == -1){
//        std::cout << " Value of errno is : " << errno << '\n';
//        std::cout << " function : " << strerror(errno) << '\n';
        throw std::string("Error reading from the file. " + FFileName);
    }

    FPosition += result;
    return static_cast<int>(result);
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Write() --
//---------------------------------------------------------------------------

int FileAPIFileManager::Write(const char * buffer, unsigned int size)
{
    long result = 0;

    result = ::write(Handle, buffer, size);

    if(result == -1)
        throw std::string("Error writing to the file. " + FFileName);

    FPosition += result;
    FSize = std::max<long long>(FPosition, FSize);

    return static_cast<int>(result);
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::FileName() --  Set file name
//---------------------------------------------------------------------------

void FileAPIFileManager::FileName(const std::string & name)
{
    FFileName = name;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::FileName() --  Get file name
//---------------------------------------------------------------------------

std::string FileAPIFileManager::FileName() const
{
    return FFileName;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Position() --
//---------------------------------------------------------------------------

bool FileAPIFileManager::Position(int64 offset)
{
    if (!Opened())
    { return false;}

    off_t position = static_cast<off_t>(offset);
    int result = ::lseek(Handle, position, SEEK_SET);

    return (result == 0);
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Position() --
//---------------------------------------------------------------------------

int64 FileAPIFileManager::Position() const
{
    return FPosition;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Size() --  Set file size
//---------------------------------------------------------------------------

void FileAPIFileManager::Size(int64 size)
{
    Position(size);
    Write("\0", 1);

    FSize = size;
}

//---------------------------------------------------------------------------
//  FileAPIFileManager::Size() --  Get file size
//---------------------------------------------------------------------------

int64 FileAPIFileManager::Size() const
{
    return FSize;
}
#endif

//===========================================================================
//  CLASS  FileManager   ---  Large disk file access support class
//===========================================================================

//---------------------------------------------------------------------------
//  FileManager::FileManager() --  Ctor
//---------------------------------------------------------------------------

FileManager::FileManager(bool useStdioFile) : _useStdioFile(useStdioFile)
{
    if(useStdioFile)
        Impl = new StdFileManager();
    else {
        Impl = new FileAPIFileManager();
    }
}

//---------------------------------------------------------------------------
//  FileManager::FileManager() --  Ctor
//---------------------------------------------------------------------------

FileManager::FileManager(const std::string & filename,bool useStdioFile) :
    _useStdioFile(useStdioFile)
{
    if(useStdioFile)
        Impl = new StdFileManager();
    else {
        Impl = new FileAPIFileManager();
    }
    FileName(filename);
}

//---------------------------------------------------------------------------
// FileManager::FileManager() --  Copy ctor
//---------------------------------------------------------------------------

FileManager::FileManager(const FileManager & other) :
    _useStdioFile(other.isStdioFile())
{
    if(other.isStdioFile())
        Impl = new StdFileManager();
    else {
        Impl = new FileAPIFileManager();
    }
    *Impl = *other.Impl;
}

//---------------------------------------------------------------------------
//  FileManager::FileManager() --  Dtor
//---------------------------------------------------------------------------

FileManager::~FileManager()
{
    delete Impl;
    Impl = nullptr;
}

//---------------------------------------------------------------------------
//  FileManager::operator = --
//---------------------------------------------------------------------------

FileManager & FileManager::operator = (const FileManager & other)
{
    // protect against invalid self-assignment
    if (this != &other)
        *Impl = *other.Impl;

    // by convention, always return *this
    return *this;
}

//---------------------------------------------------------------------------
//  FileManager::Open() --  Open file for reading
//---------------------------------------------------------------------------

bool FileManager::Open()
{
    return Impl->Open();
}

//---------------------------------------------------------------------------
//  FileManager::Create() --  Create file for writing
//---------------------------------------------------------------------------

bool FileManager::Create()
{
    return Impl->Create();
}

//---------------------------------------------------------------------------
//  FileManager::Append() --  Open file for append
//---------------------------------------------------------------------------

bool FileManager::Append()
{
    return Impl->Append();
}

//---------------------------------------------------------------------------
//  FileManager::Close() --
//---------------------------------------------------------------------------

bool FileManager::Close()
{
    return Impl->Close();
}

//---------------------------------------------------------------------------
//  FileManager::Read() --
//---------------------------------------------------------------------------

int FileManager::Read(char * buffer, unsigned int size)
{
    return Impl->Read(buffer, size);
}

//---------------------------------------------------------------------------
//  FileManager::Write() --
//---------------------------------------------------------------------------

int FileManager::Write(const char * buffer, unsigned int size)
{
    return Impl->Write(buffer, size);
}

//---------------------------------------------------------------------------
//  FileManager::Opened() --
//---------------------------------------------------------------------------

bool FileManager::Opened() const
{
    return Impl->Opened();
}

//---------------------------------------------------------------------------
//  FileManager::Position() --
//---------------------------------------------------------------------------

bool FileManager::Position(int64 offset)
{
    return Impl->Position(offset);
}

//---------------------------------------------------------------------------
//  FileManager::Position() --
//---------------------------------------------------------------------------

int64 FileManager::Position() const
{
    return Impl->Position();
}

//---------------------------------------------------------------------------
//  FileManager::FileName() --  Set file name
//---------------------------------------------------------------------------

void FileManager::FileName(const std::string & name)
{
    Impl->FileName(name);
}

//---------------------------------------------------------------------------
//  FileManager::FileName() --  Get file name
//---------------------------------------------------------------------------

std::string FileManager::FileName() const
{
    return Impl->FileName();
}

//---------------------------------------------------------------------------
//  FileManager::Size() --  Set file size
//---------------------------------------------------------------------------

void FileManager::Size(int64 size)
{
    Impl->Size(size);
}

//---------------------------------------------------------------------------
//  FileManager::Size() --  Get file size
//---------------------------------------------------------------------------

int64 FileManager::Size() const
{
    return Impl->Size();
}

//---------------------------------------------------------------------------
//  FileManager::WriteThrough() --
//---------------------------------------------------------------------------

void FileManager::WriteThrough(bool)
{
}

//---------------------------------------------------------------------------
//  FileManager::WriteThrough() --
//---------------------------------------------------------------------------

bool FileManager::WriteThrough() const
{
    return false;
}


}  // namespace

// Undefining _FILE_OFFSET_BITS macro, so that other classes are not affected.
#if defined(LINUX)
#undef _FILE_OFFSET_BITS
#endif
