#ifndef _LCD_CONNECTION_H_
#define _LCD_CONNECTION_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


class LCDConnection
{
 private:
  bool _isConnected;
  int _sock;
  sockaddr_in _addr;

 public:
  LCDConnection();
  LCDConnection(const std::string &host, const int port);
  explicit LCDConnection(const LCDConnection &source);
  virtual ~LCDConnection();

  bool isValid() const;

  void connect(const std::string &host, const int port);
  void disconnect();

  void send(const std::string &toSend);
  std::string recv();

  LCDConnection & operator = (const LCDConnection &copy);
  const LCDConnection & operator << (const std::string &s);
  const LCDConnection & operator >> (std::string &s);

};


#endif

