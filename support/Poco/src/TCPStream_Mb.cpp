
// TCPStream_Mb.cpp
//
//    ISI LLC PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or nondisclosure
//  agreement with ISI LLC and may not be copied or
//  disclosed except in accordance with the terms of that agreement.
//  Copyright (c) 2000..2012 ISI LLC.
//  All Rights Reserved.
//

#include "Poco/Net/TCPStream_Mb.h"
#include "Poco/Net/NetException.h"
#include "Poco/RegularExpression.h"

using Poco::RegularExpression;
using Poco::Net::NetException;
namespace   Innovative
{

//---------------------------------------------------------------------------
//  TCPStreamBase::TCPStreamBase() --
//---------------------------------------------------------------------------

 TCPStreamBase::TCPStreamBase(bool server)
    : _server(server), _pimpl(0)
{
}

//---------------------------------------------------------------------------
//  TCPStreamBase::~TCPStreamBase() --
//---------------------------------------------------------------------------

 TCPStreamBase::~TCPStreamBase()
{
     delete _pimpl;
    _pimpl = 0;
    Close();
}

//---------------------------------------------------------------------------
//  TCPStreamBase::Opened() --
//---------------------------------------------------------------------------

bool TCPStreamBase::Opened() const
{
    return _pimpl && _pimpl->Opened();
}

//---------------------------------------------------------------------------
//  TCPStreamBase::Connected() --
//---------------------------------------------------------------------------

bool TCPStreamBase::Connected() const
{
    return _pimpl && _pimpl->Connected();
}

//---------------------------------------------------------------------------
//  TCPStreamBase::OpenServer() --
//---------------------------------------------------------------------------

bool TCPStreamBase::OpenServer(unsigned short port)
{
    if (Opened())
        Close();

    _pimpl = new TCPStreamServerImpl(this, port);

    _pimpl->Open();
    return _pimpl->Opened();
}

//---------------------------------------------------------------------------
//  TCPStreamBase::OpenClient() --
//---------------------------------------------------------------------------

bool TCPStreamBase::OpenClient(unsigned short port, const std::string & ip)
{
    if (Opened())
        Close();

    _pimpl = new TCPStreamClientImpl(this, port, ip);

    return _pimpl->Open();
}

//---------------------------------------------------------------------------
//  TCPStreamBase::Close() --
//---------------------------------------------------------------------------

void TCPStreamBase::Close()
{
    if (_pimpl)
        {
        _pimpl->Close();


        }
}

//---------------------------------------------------------------------------
//  TCPStreamBase::Write() --
//---------------------------------------------------------------------------

int TCPStreamBase::Write(const Buffer & buffer)
{
    //  Make sure packet size is correct...
    PacketBufferHeader headerDG(buffer);
    headerDG.PacketSize(buffer.FullSizeInInts());

    if (!_pimpl)
        return 0;

    return _pimpl->Write(buffer);
}

//---------------------------------------------------------------------------
//  TCPStreamBase::Write() --
//---------------------------------------------------------------------------

int TCPStreamBase::Write(short PeriphId, const Buffer & buffer)
{
    //
    //  Load Peripheral ID
    PacketBufferHeader headerDG(buffer);
    headerDG.PeripheralId(PeriphId);

    return Write(buffer);
}
//---------------------------------------------------------------------------
//  TCPStreamBase::Write() --
//---------------------------------------------------------------------------

int TCPStreamBase::Write(unsigned short PeriphId, const std::string & msg)
{
    if (!Connected())
        return 0;

    Buffer txt;

    CharDG Msg(txt);
    size_t size = msg.size()+1;
    Msg.Resize(size + 3);

    for (size_t i = 0; i < size; ++i)
        Msg[i] = msg[i];

    PacketBufferHeader Head(txt);
    Head.PeripheralId(PeriphId);

    return Write(txt);
}

//---------------------------------------------------------------------------
//  TCPStreamBase::Write() --
//---------------------------------------------------------------------------

int TCPStreamBase::Write(const std::string & msg)
{
    if (!Connected())
        return 0;

    Buffer txt;

    CharDG Msg(txt);
    size_t size = msg.size()+1;
    Msg.Resize(size + 3);

    for (size_t i = 0; i < size; ++i)
        Msg[i] = msg[i];

    PacketBufferHeader Head(txt);
    Head.PeripheralId(0xff);

    return Write(txt);
}

//---------------------------------------------------------------------------
//  TCPStreamBase::SetSendBufferSize() -- Set send buffer size in bytes
//---------------------------------------------------------------------------

void TCPStreamBase::SetSendBufferSize(int bytes)
{
    return _pimpl->SetSendBufferSize(bytes);
}

//---------------------------------------------------------------------------
//  TCPStreamBase::SetReceiveBufferSize() -- Set receive buffer size in bytes
//---------------------------------------------------------------------------

void TCPStreamBase::SetReceiveBufferSize(int bytes)
{
    return _pimpl->SetReceiveBufferSize(bytes);
}

//---------------------------------------------------------------------------
//  TCPStreamBase::GetSendBufferSize() -- Get send buffer size in bytes
//---------------------------------------------------------------------------

int TCPStreamBase::GetSendBufferSize()
{
    return _pimpl->GetSendBufferSize();
}

//---------------------------------------------------------------------------
//  TCPStreamBase::SetReceiveBufferSize() -- Get receive buffer size in bytes
//---------------------------------------------------------------------------

int TCPStreamBase::GetReceiveBufferSize()
{
    return _pimpl->GetReceiveBufferSize();
}

//---------------------------------------------------------------------------
//  TCPStreamServer::Open() --
//---------------------------------------------------------------------------

bool TCPStreamServer::Open(unsigned short port)
{
    return OpenServer(port);
}

//---------------------------------------------------------------------------
//  TCPStreamClient::Open() --
//---------------------------------------------------------------------------

bool TCPStreamClient::Open(unsigned short port, const std::string & ip)
{
    return OpenClient(port, ip);
}


//---------------------------------------------------------------------------
//  TCPStreamServerImpl::TCPStreamServerImpl() --
//---------------------------------------------------------------------------

TCPStreamServerImpl::TCPStreamServerImpl(TCPStreamBase *owner, unsigned short port)
    :_svs(0), _srv(0), _owner(owner), _connected(false), _opened(false), _port(port)
{
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::~TCPStreamServerImpl() --
//---------------------------------------------------------------------------

TCPStreamServerImpl::~TCPStreamServerImpl()
{
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::Open() --
//---------------------------------------------------------------------------

bool TCPStreamServerImpl::Open()
{
    _svs = new ServerSocket(_port); // bind + listen
    // set-up a TCPServer instance

    //_params = new TCPServerParams;
    //_params->setMaxQueued(1);
    //_params->setMaxThreads(1);

    _srv = new TCPServer(new ApplicationConnectionFactory(this), *_svs);
    // start the TCPServer
    _srv->start();

    _opened = true;

    return true;
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::Close() --
//---------------------------------------------------------------------------

void TCPStreamServerImpl::Close()
{
    try
        {
        // Stop the TCPServer
        _srv->stop();
        // Close the Socket
        _svs->close();
        }
    catch(Poco::Net::NetException &exc)
        {
        NotifyError(exc.name());
        }

    _opened = false;

    delete _srv;

    delete _svs;
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::Write() --
//---------------------------------------------------------------------------

int TCPStreamServerImpl::Write(const Buffer & buffer)
{
    return _connection->write(buffer);
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::SetSendBufferSize() --
//---------------------------------------------------------------------------

void TCPStreamServerImpl::SetSendBufferSize(int bytes)
{
    _svs->setSendBufferSize(bytes);
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::SetReceiveBufferSize() --
//---------------------------------------------------------------------------

void TCPStreamServerImpl::SetReceiveBufferSize(int bytes)
{
    _svs->setReceiveBufferSize(bytes);
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::GetSendBufferSize() --
//---------------------------------------------------------------------------

int TCPStreamServerImpl::GetSendBufferSize()
{
    return _svs->getSendBufferSize();
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::GetReceiveBufferSize() --
//---------------------------------------------------------------------------

int TCPStreamServerImpl::GetReceiveBufferSize()
{
    return _svs->getReceiveBufferSize();
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::Connected() --
//---------------------------------------------------------------------------

bool TCPStreamServerImpl::Connected() const
{
    return _connected;
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::Opened() --
//---------------------------------------------------------------------------

bool TCPStreamServerImpl::Opened() const
{
    return _opened;
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::NotifyConnected() --
//---------------------------------------------------------------------------
void TCPStreamServerImpl::NotifyConnected(class ApplicationServerConnection *connection)
{
    _connection = connection;

    _connected = (_connection != 0);

    ProcessCompletionEvent event(_connected);
    _owner->OnConnect.Execute(event);
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::NotifyError() --
//---------------------------------------------------------------------------
void TCPStreamServerImpl::NotifyError(const std::string & msg)
{
    ProcessStatusEvent e(msg);
    _owner->OnError.Execute(e);
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::NotifyBufferReceived() --
//---------------------------------------------------------------------------
void TCPStreamServerImpl::NotifyBufferReceived(const Buffer & buffer)
{
    BufferReceivedEvent b(buffer);
    _owner->OnRead.Execute(b);
}

//---------------------------------------------------------------------------
//  TCPStreamServerImpl::NotifyTextReceived() --
//---------------------------------------------------------------------------
void TCPStreamServerImpl::NotifyTextReceived(const std::string & msg)
{
    ProcessStatusEvent m(msg);
    _owner->OnMessage.Execute(m);
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::Open() --
//---------------------------------------------------------------------------
bool TCPStreamClientImpl::Open()
{
    //Check for valid IP address format
    RegularExpression re("\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");

    if (!re.match(_ip))
        throw Poco::Net::InvalidAddressException();

    try
        {
        // create address for connection
        _sockAddr = new SocketAddress(_ip, _port);
        // create socket
        Poco::Timespan Timeout(3000000); //3 seconds
        _socket = new StreamSocket();
        _socket->connect(*_sockAddr, Timeout);
        // create the receving thread
        _thread	  = new ReceiverThread(this);

        _thread->Resume();
        _thread->Start();

        _opened = _connected = true;
        }
    catch (const Poco::Net::NetException &exc)
        {
        _opened = _connected = false;
        NotifyError(exc.name());
        }
    catch (Poco::TimeoutException &exc)
        {
        _opened = _connected = false;
        NotifyError(exc.name());
        NotifyError("Could not open. Please check IP address and make sure server is running.");
        }
    catch (...)
        {
        _opened = _connected = false;
        NotifyError("Error: could not open");
        }

    return _opened;
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::Close() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::Close()
{
    try
    {
        _socket->shutdown();
    }
    catch(Poco::Net::NetException &exc)
    {
        NotifyError(exc.name());
    }

    if (_thread)
        {
    _thread->Resume();
    _thread->Stop();
    _thread->WaitForStopped();
        }



    _opened = _connected = false;
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::Write() --
//---------------------------------------------------------------------------
int TCPStreamClientImpl::Write(const Buffer & buffer)
{
    try
        {
        // Send header
        PacketBufferHeader Head(buffer);
        int totalSent = _socket->sendBytes(&Head[0], Head.SizeInBytes());
        // Send body
        CharDG Body(buffer);
        totalSent += _socket->sendBytes(&Body[0], Body.SizeInBytes());

        return totalSent;
        }
    catch(Poco::Net::NetException &exc)
        {
        NotifyError(exc.name());
        }

    return 0;
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::SetSendBufferSize() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::SetSendBufferSize(int bytes)
{
    _socket->setSendBufferSize(bytes);
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::SetReceiveBufferSize() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::SetReceiveBufferSize(int bytes)
{
    _socket->setReceiveBufferSize(bytes);
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::GetSendBufferSize() --
//---------------------------------------------------------------------------
int TCPStreamClientImpl::GetSendBufferSize()
{
    return _socket->getSendBufferSize();
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::GetReceiveBufferSize() --
//---------------------------------------------------------------------------
int TCPStreamClientImpl::GetReceiveBufferSize()
{
    return _socket->getReceiveBufferSize();
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::NotifyError() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::NotifyError(const std::string & msg)
{
    ProcessStatusEvent e(msg);
    _owner->OnError.Execute(e);
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::NotifyBufferReceived() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::NotifyBufferReceived(const Buffer & buffer)
{
    BufferReceivedEvent b(buffer);
    _owner->OnRead.Execute(b);
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::NotifyTextReceived() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::NotifyConnected(class ApplicationServerConnection * /*server*/)
{
    //_connected = true;
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::NotifyTextReceived() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::NotifyTextReceived(const std::string & msg)
{
    ProcessStatusEvent m(msg);
    _owner->OnMessage.Execute(m);
}

//---------------------------------------------------------------------------
//  TCPStreamClientImpl::Receive() --
//---------------------------------------------------------------------------
void TCPStreamClientImpl::Receive()
{
    try
    {
    for (;;)
        {
        // Receive header
        PacketBufferHeader Head(_data);
        int n =_socket->receiveBytes(&Head[0], Head.SizeInBytes());

        // Receive body
        CharDG Body(_data);
        Body.Resize( CouldHold<char>(Head.DataSize()) );

        size_t BufferIndex = 0;
        do{
            n = _socket->receiveBytes(&Body[BufferIndex], Body.SizeInBytes() - BufferIndex);
            BufferIndex += n;
        } while (BufferIndex != 0 && BufferIndex < Body.SizeInBytes());

        if (n == 0) // Connnection closed
            break;

        if (Head.PeripheralId() == 0xff)
            {
            // Upack the string from the buffer
            CharDG Msg(_data);
            std::string msg(&Msg[0], Msg.size());

            NotifyTextReceived(msg);
            }
        if (Head.PeripheralId() == 0xfd)
            {

            }
        else
            {
            Buffer temp(_data);
            temp.MakeUnique();
            temp.MakeUniqueHeader();

            NotifyBufferReceived(temp);
            }
        }
    }
    catch (const Poco::Net::NetException &exc)
    {
        NotifyError(exc.name() + std::string(" : ")  + exc.message());
    }

}
//---------------------------------------------------------------------------
//  ApplicationServerConnection::ApplicationServerConnection() --
//---------------------------------------------------------------------------
ApplicationServerConnection::ApplicationServerConnection(const StreamSocket& s, INotify *owner):
    TCPServerConnection(s), _owner(owner)
{
    _owner->NotifyConnected(this);
}

//---------------------------------------------------------------------------
//  ApplicationServerConnection::~ApplicationServerConnection() --
//---------------------------------------------------------------------------
ApplicationServerConnection::~ApplicationServerConnection()
{
    _owner->NotifyConnected(0);
}

//---------------------------------------------------------------------------
//  ApplicationServerConnection::write() --
//---------------------------------------------------------------------------
int ApplicationServerConnection::write(const Buffer & buffer)
{
    try
        {
        // Send header
        PacketBufferHeader Head(buffer);
        int totalSent = socket().sendBytes(&Head[0], Head.SizeInBytes());
        // Send body
        CharDG Body(buffer);
        totalSent += socket().sendBytes(&Body[0], Body.SizeInBytes());

        return totalSent;
        }
    catch(Poco::Net::NetException &exc)
        {
        _owner->NotifyError(exc.name());
        }

    return 0;
}

//---------------------------------------------------------------------------
//  ApplicationServerConnection::run() --
//---------------------------------------------------------------------------
void ApplicationServerConnection::run()
{
    try
    {
    for (;;)
        {
        // Receive header
        PacketBufferHeader Head(_data);
        int n = socket().receiveBytes(&Head[0], Head.SizeInBytes());
        // Receive body
        CharDG Body(_data);
        Body.Resize( CouldHold<char>(Head.DataSize()) );

        size_t BufferIndex = 0;
        do{
            n = socket().receiveBytes(&Body[BufferIndex], Body.SizeInBytes() - BufferIndex);
            BufferIndex += n;
        } while (BufferIndex != 0 && BufferIndex < Body.SizeInBytes());

        if (n == 0) // Connnection closed
            break;

        if (Head.PeripheralId() == 0xff)
            {
            // Upack the string from the buffer
            CharDG Msg(_data);
            std::string msg(&Msg[0], Msg.size());

            _owner->NotifyTextReceived(msg);
            }
        else
            {
            Buffer temp(_data);
            temp.MakeUnique();
            temp.MakeUniqueHeader();

            _owner->NotifyBufferReceived(temp);
            }
        }
    }
    catch (const Poco::Net::NetException &exc)
    {
        _owner->NotifyError(exc.name() + std::string(" : ")  + exc.message());
    }

}

}   // Innovative
