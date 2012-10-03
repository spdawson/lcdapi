#include "LCDConnection.h"
#include "LCDConstants.h"
#include "LCDException.h"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <iostream>

namespace lcdapi {

using namespace std;

LCDConnection::LCDConnection()
  : _isConnected(false), _sock(socket (AF_INET, SOCK_STREAM, 0)), _addr()
{
  initialize();
}

LCDConnection::LCDConnection(const string &host, const int port)
  : _isConnected(false), _sock(socket (AF_INET, SOCK_STREAM, 0)), _addr()
{
  initialize();
  connect(host, port);
}

LCDConnection::~LCDConnection()
{
  disconnect();
}

void LCDConnection::initialize()
{
  memset(&_addr, 0, sizeof (_addr));

  if (!isValid())
  {
    throw LCDException(LCD_SOCKET_CREATION_ERROR);   
  }

  const int on = 1;
  if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&on), sizeof (on)) == -1)
  {
    throw LCDException(LCD_SOCKET_CREATION_ERROR);   
  }
}

bool LCDConnection::isValid() const
{
  return _sock != -1;
}

void LCDConnection::connect(const string &host, const int port)
{
  if (!isValid())
  {
    throw LCDException(LCD_SOCKET_CREATION_ERROR);
  }

  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(port);

  int status = inet_pton(AF_INET, host.c_str(), &_addr.sin_addr);

  if (errno == EAFNOSUPPORT)
  {
    throw LCDException(LCD_SOCKET_NOT_SUPPORTED);
  }

  status = ::connect(_sock, reinterpret_cast<struct sockaddr*>(&_addr), sizeof(_addr) );

  if (status != 0)
  {
    throw LCDException(LCD_SOCKET_CONNECTION_ERROR);
  }

  _isConnected = true;
}

void LCDConnection::disconnect()
{
  if (isValid())
  {
    ::close(_sock);
  }
}

void LCDConnection::send(const string &toSend)
{
  string s = toSend + "\r\n";

#ifdef DEBUG
  cerr << "Sending : " << s << endl;
#endif // DEBUG

  if (!_isConnected)
  {
    throw LCDException(LCD_SOCKET_NOT_CONNECTED);
  }

  const int total = s.size();
  int offset = 0;

  while (offset != total)
  {
    const int sent = ::send(_sock, s.c_str() + offset, s.size() - offset, 0);
    if ( ((sent == -1) && (errno != EAGAIN)) || (sent == 0) )
    {
      throw LCDException(LCD_SOCKET_SEND_ERROR);
    }
    else
    {
      offset += sent;
    }
  }
}

string LCDConnection::recv()
{
  if (!_isConnected)
  {
    throw LCDException(LCD_SOCKET_NOT_CONNECTED);
  }

  char buf[LCD_MAXRECV + 1];
  memset (buf, 0, LCD_MAXRECV + 1);
  char *current = buf - 1;

  do
  {
    current++;
    const int status = ::recv(_sock, current, 1, 0);
    if (status == -1)
    {
      throw LCDException(LCD_SOCKET_RECV_ERROR);
    }
  } while ( (*current != '\0' ) && (*current != '\r' ) && (*current != '\n' ) && ((current - buf) < LCD_MAXRECV) );

  *current = '\0';

  const string result(buf);

#ifdef DEBUG
  cerr << "Receiving : " << result << endl;
#endif // DEBUG

  return result;
}

const LCDConnection& LCDConnection::operator << (const string &s)
{
  send(s);
  return *this;
}

const LCDConnection& LCDConnection::operator >> (string &s)
{
  s = recv();
  return *this;
}

} // end of lcdapi namespace
