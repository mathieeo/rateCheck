
// TCPStream_Mb.h
//
//    INNOVATIVE INTEGRATION CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or nondisclosure
//  agreement with Innovative Integration Corporation and may not be copied or
//  disclosed except in accordance with the terms of that agreement.
//  Copyright (c) 2000..2012 Innovative Integration Corporation.
//  All Rights Reserved.
//

#ifndef TCPStream_MbH
#define TCPStream_MbH

#include "Poco/Net/TCPServer.h"
#include <Events_Mb.h>
#include <ProcessEvents_Mb.h>
#include <BufferHeader_Mb.h>
#include <BufferDatagrams_Mb.h>
#include <StartStopThread_Mb.h>

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Exception.h"
#include "Poco/Net/NetException.h"
#include <iostream>

using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;

using Poco::AutoPtr;

namespace   Innovative
{

#ifdef __CLR_VER
#pragma managed(push, off)
#endif

//===========================================================================
//  CLASS  BufferReceivedEvent   ---
//===========================================================================

class BufferReceivedEvent : public OpenWire::NotifyEvent
{
public:
    const class Buffer Data;

    BufferReceivedEvent(const Buffer & data)
        : Data(data)
        {  }
};

//===========================================================================
//  CLASS  ITCPStream  ---
//===========================================================================

class ITCPStream
{
public:
   ITCPStream()
   {}
   virtual ~ITCPStream()
   {}

    // Support Methods
    virtual bool Open() = 0;
    virtual void Close() = 0;

    virtual bool Opened() const = 0;
    virtual bool Connected() const = 0;

    virtual int Write(const Buffer & buffer) = 0;

    virtual void SetSendBufferSize(int bytes) = 0;
    virtual void SetReceiveBufferSize(int bytes) = 0;
    virtual int  GetSendBufferSize() = 0;
    virtual int  GetReceiveBufferSize() = 0;
};

//===========================================================================
//  CLASS  TCPStreamBase   ---
//===========================================================================

class TCPStreamBase
{
public:

    // Ctor
    TCPStreamBase(bool server);
    ~TCPStreamBase();

    // Support Methods
    void    Close();

    bool    Opened() const;
    bool    Connected() const;

    int     Write(short PeriphId, const Buffer & buffer);
    int     Write(const Buffer & buffer);
    int     Write(const std::string & msg);
    int     Write(unsigned short PeriphId, const std::string &msg);

    void    SetSendBufferSize(int bytes);   //set send buffer size in bytes
    void    SetReceiveBufferSize(int bytes); //set receive buffer size in bytes
    int     GetSendBufferSize();
    int     GetReceiveBufferSize();

    // Properties
    OpenWire::EventHandler<BufferReceivedEvent>     OnRead;
    OpenWire::EventHandler<ProcessStatusEvent>      OnMessage;
    OpenWire::EventHandler<ProcessCompletionEvent>  OnConnect;
    OpenWire::EventHandler<ProcessStatusEvent>      OnError;

protected:
    bool    OpenServer(unsigned short port);
    bool    OpenClient(unsigned short port, const std::string & ip);

    // Fields
    bool        _server;
    ITCPStream *_pimpl;
};

//===========================================================================
//  CLASS  TCPStreamServer   ---
//===========================================================================

class TCPStreamServer : public TCPStreamBase
{
public:
   enum
           {
                   DEFAULT_INNOVATIVE_SERVER_PORT = 9977
           };

   // Methods
   TCPStreamServer() : TCPStreamBase(true)
   {}
   bool Open(unsigned short port = DEFAULT_INNOVATIVE_SERVER_PORT);
};

//===========================================================================
//  CLASS  TCPServer   ---
//===========================================================================

class TCPStreamClient : public TCPStreamBase
{
public:
    enum
            {
                    DEFAULT_INNOVATIVE_SERVER_PORT = 9977
            };

    // Methods
    TCPStreamClient() : TCPStreamBase(false)
    {}

    bool Open(unsigned short port = DEFAULT_INNOVATIVE_SERVER_PORT, const std::string & ip = "127.0.0.1");
};

//==============================================================================
//  CLASS INotify
//==============================================================================

class INotify
{
public:
    virtual void NotifyConnected(class ApplicationServerConnection *server)  	= 0;
    virtual void NotifyTextReceived(const std::string & msg)					= 0;
    virtual void NotifyBufferReceived(const Buffer & buffer)					= 0;
    virtual void NotifyError(const std::string & msg)							= 0;
};

//===========================================================================
//  CLASS  TCPStreamClient   ---
//===========================================================================
class TCPStreamClientImpl : public INotify, public ITCPStream
{

    class ReceiverThread : public StartStopThread
    {
            typedef StartStopThread  inherited;

    public:
            // Ctor
            ReceiverThread(class TCPStreamClientImpl * owner)
                    : inherited("ReceiverThread"), _owner(owner)
                    {  }

    protected:
            //
            class TCPStreamClientImpl *_owner;

            //  do one iteration of main process
            virtual void SingleExecution()
                    {
                    _owner->Receive();
                    Stop();
                    }
    };

    friend class ReceiverThread;

public:
        TCPStreamClientImpl(TCPStreamBase *owner, unsigned short port, const std::string & ip) :
         _thread(0), _socket(0), _sockAddr(0), _owner(owner), _port(port), _ip(ip), _connected(false), _opened(false)
        {
        }

        ~TCPStreamClientImpl()
        {
            delete _socket;
            _socket = 0;

            delete _thread;
            _thread = 0;
            delete _sockAddr;
            _sockAddr = 0;
        }

    // Methods
    bool Open();
    void Close();

    int  Write(const Buffer & buffer);
    void Receive();

    void SetSendBufferSize(int bytes);
    void SetReceiveBufferSize(int bytes);
    int  GetSendBufferSize();
    int  GetReceiveBufferSize();

    bool Connected() const
        { return _connected; }
    bool Opened() const
        { return _opened; }


private:
    virtual void NotifyConnected(class ApplicationServerConnection *server);
    virtual void NotifyTextReceived(const std::string & msg);
    virtual void NotifyBufferReceived(const Buffer & buffer);
    virtual void NotifyError(const std::string & msg);

    Innovative::Buffer	 _data;
    ReceiverThread		*_thread;
    StreamSocket		*_socket;
    SocketAddress       *_sockAddr;
    TCPStreamBase		*_owner;
    unsigned short		_port;
    std::string			_ip;
    bool                _connected;
    bool                _opened;
};

//==============================================================================
//  CLASS TCPStreamServerImpl
//==============================================================================

class TCPStreamServerImpl : public INotify, public ITCPStream
{
        friend class ApplicationServerConnection;
public:
    TCPStreamServerImpl(TCPStreamBase *owner, unsigned short port);
    ~TCPStreamServerImpl();

    // Methods
    bool Open();
    void Close();

    int  Write(const Buffer & buffer);

    void SetSendBufferSize(int bytes);
    void SetReceiveBufferSize(int bytes);
    int  GetSendBufferSize();
    int  GetReceiveBufferSize();

    bool Connected() const;
    bool Opened() const;

private:
    virtual void NotifyConnected(class ApplicationServerConnection *server);
    virtual void NotifyTextReceived(const std::string & msg);
    virtual void NotifyBufferReceived(const Buffer & buffer);
    virtual void NotifyError(const std::string & msg);

    ServerSocket    *_svs;
    TCPServer       *_srv;
    TCPStreamBase   *_owner;
    class ApplicationServerConnection *_connection;
    bool            _connected;
    bool            _opened;
    unsigned short  _port;
};

//==============================================================================
//  CLASS ApplicationServerConnection
//==============================================================================

class ApplicationServerConnection: public TCPServerConnection
{

public:
     ApplicationServerConnection(const StreamSocket& s, INotify *owner);
     ~ApplicationServerConnection();

     int write(const Buffer & buffer);
     void run();

private:
     INotify    *_owner;
     Buffer      _data;
};

//==============================================================================
//  CLASS ApplicationConnectionFactory
//==============================================================================

class ApplicationConnectionFactory: public TCPServerConnectionFactory
        /// A factory.
{
public:
    ApplicationConnectionFactory(TCPStreamServerImpl *owner):
            _owner(owner)
    {
    }

    TCPServerConnection* createConnection(const StreamSocket& socket)
    {
            return new ApplicationServerConnection(socket, _owner);
    }

private:
    TCPStreamServerImpl *_owner;
};

#ifdef __CLR_VER
#pragma managed(pop)
#endif

} // namespace Innovative

#endif
