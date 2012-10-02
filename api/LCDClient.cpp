#include "LCDClient.h"
#include "LCDLock.h"
#include "LCDException.h"
#include <sstream>

namespace lcdapi {

using namespace std;

void *mainRepliesLoop(void *);
void *handleKeyEvent(void *);

struct KeyEventInfo
{
  KeyEvent kev;
  LCDCallback *callback;
};

LCDClient::LCDClient(const string &server, int port) : LCDElement("", ""),
                                                       _sendMutex(),
                                                       _gotAnswer(),
                                                       _mainThread(),
                                                       _serverConnection(),
                                                       _answer(),
                                                       _currentScreen(),
                                                       _connectionString(),
                                                       _serverVersion(),
                                                       _protocolVersion(),
                                                       _width(0),
                                                       _height(0),
                                                       _charWidth(0),
                                                       _charHeight(0),
                                                       _callbacks()
{
  ::pthread_mutex_init(&_sendMutex, 0);
  ::pthread_cond_init(&_gotAnswer, 0);

  _serverConnection.connect(server, port);
  _serverConnection << "hello";
  _serverConnection >> _connectionString;

  string token;
  istringstream response(_connectionString);

  while (response >> token)
  {
    if (token == "LCDproc")
    {
      response >> _serverVersion;
    }
    else if (token == "protocol")
    {
      response >> _protocolVersion;
    }
    else if (token == "wid")
    {
      response >> _width;
    }
    else if (token == "hgt")
    {
      response >> _height;
    }
    else if (token == "cellwid")
    {
      response >> _charWidth;
    }
    else if (token == "cellhgt")
    {
      response >> _charHeight;
    }
  }

  ::pthread_create(&_mainThread, 0, &mainRepliesLoop, this);
}

LCDClient::~LCDClient()
{
  if (::pthread_cancel(_mainThread) == 0)
  {
    ::pthread_join(_mainThread, 0);
  }
  ::pthread_mutex_destroy(&_sendMutex);
}

void LCDClient::sendCommand(const std::string &cmd, const std::string &parameters)
{
  if (cmd.size() > 0)
  {
    const LCDLock l(&_sendMutex);

    const string command = cmd + " " + parameters;

    _serverConnection << command;

    while (_answer.empty())
    {
      ::pthread_cond_wait(&_gotAnswer, &_sendMutex);
    }

    if (_answer.substr(0, 4) == "huh?")
    {
      throw LCDException(_answer.substr(5));
    }
    _answer.clear();
  }
}

void LCDClient::setClientOption(const string& optName, const string& value)
{
  sendCommand("client_set", string("-") + optName + " " + value);
}

void LCDClient::setName(const string& name)
{
  setClientOption("name", name);
}
/*
void LCDClient::setHeartBeat(const string& heartbeat)
{
  setClientOption("heartbeat", heartbeat);
}
*/
void LCDClient::setBackLight(const string& backlight)
{
  sendCommand("backlight", backlight);
}

void LCDClient::assignKey(KeyEvent key, LCDCallback *callback)
{
  _callbacks[key] = callback;
  sendCommand("client_add_key", LCDCallback::toString(key));
}

void LCDClient::mainLoop()
{
  ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);
  string reply;
  while(true)
  {
    _serverConnection >> reply;

    if ( (reply.substr(0, 4) == "huh?") || (reply == "success") )
    {
      const LCDLock l(&_sendMutex);
      _answer = reply;
      ::pthread_cond_signal(&_gotAnswer);
    }
    else
    {
      if (reply.substr(0, 3) == "key")
      {
        const KeyEvent key = reply[4];
        if (_callbacks.end() != _callbacks.find(key))
        {
          KeyEventInfo *kevI = new KeyEventInfo;
          kevI->kev = key;
          kevI->callback = _callbacks[key];

          ::pthread_t tid;
          ::pthread_create(&tid, 0, &handleKeyEvent, kevI);
        }

      }
      else if (reply.substr(0, 6) == "listen")
      {
        _currentScreen = reply.substr(7);
      }
      else if (reply.substr(0, 6) == "ignore")
      {
	if (_currentScreen == reply.substr(7))
	{
	  _currentScreen.clear();
	}
      }
    }
  }
}

void *mainRepliesLoop(void *param)
{
  LCDClient *client = static_cast<LCDClient*>(param);
  client->mainLoop();

  return NULL;
}

void *handleKeyEvent(void *param)
{
  KeyEventInfo *kevI = static_cast<KeyEventInfo*>(param);

  (*(kevI->callback))(kevI->kev);

  delete kevI;

  return NULL;
}

} // end of lcdapi namespace
