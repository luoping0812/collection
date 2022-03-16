
#include "Connection.h"
#include "System.h"
#include "Log.h"

namespace net
{

Connection::Connection(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrPeerAddr)
    : m_ptrEventLoop(ptrEventLoop)
    , m_ptrSock(ptrSock)
    , m_bConnected(true)
    , m_ptrPeerAddr(ptrPeerAddr)
{
    m_ptrChannel = std::make_shared<Channel>(ptrSock);
    m_ptrChannel->addListenEvent(EPOLLIN | EPOLLET);
    m_ptrChannel->setEventCallback(std::bind(&Connection::handleEvent, this));
    m_ptrEventLoop->updateChannel(m_ptrChannel);

    LOG_DEBUG();
}


Connection::~Connection()
{
    LOG_DEBUG();
}

void Connection::handleEvent()
{
    char buf[1024];
    while (true)
    {
        utils::memZero(buf, sizeof(buf));
        ssize_t bytes = m_ptrSock->read(buf, sizeof(buf));
        if (bytes > 0)
        {
            m_strReadBuffer.append(buf);
        }
        else if (bytes == 0)
        {
            m_bConnected = false;
            LOG_FMT_WARN("client %s disconnected", m_ptrPeerAddr->getIpPort().c_str());
            break;
        }
        else if (bytes == -1 && errno == EINTR) // 客户端正常中断，继续读取
        {

        }
        else if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) //非阻塞io，这个表示数据读取完毕
        {
            break;
        }
        else
        {
            LOG_WARN() << "other error";
            break;
        }
    }

    m_handCB(shared_from_this());    
}
   
void Connection::read(std::string& str)
{
    str = m_strReadBuffer;
    m_strReadBuffer.clear();
}

void Connection::write(const std::string& str)
{
    m_strWriteBuffer.append(str);
}

void Connection::close()
{
    m_delCB(m_ptrSock);
}

IPAddress::ptr Connection::getPeerAddress()
{
    if (!m_ptrPeerAddr)
    {
        m_ptrPeerAddr = m_ptrSock->getPeerAddress();
    }
    return m_ptrPeerAddr;
}

} // namespace net