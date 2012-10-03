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
    if (0 == token.compare("LCDproc"))
    {
      response >> _serverVersion;
    }
    else if (0 == token.compare("protocol"))
    {
      response >> _protocolVersion;
    }
    else if (0 == token.compare("wid"))
    {
      response >> _width;
    }
    else if (0 == token.compare("hgt"))
    {
      response >> _height;
    }
    else if (0 == token.compare("cellwid"))
    {
      response >> _charWidth;
    }
    else if (0 == token.compare("cellhgt"))
    {
      response >> _charHeight;
    }
  }

  ::pthread_create(&_mainThread, 0, &mainRepliesLoop, this);
}

LCDClient::~LCDClient()
{
  // It is polite to let the server know that we are disconnecting
  {
    const LCDLock l(&_sendMutex);
    _serverConnection << "bye";
  }

  if (::pthread_cancel(_mainThread) == 0)
  {
    ::pthread_join(_mainThread, 0);
  }
  ::pthread_mutex_destroy(&_sendMutex);
  ::pthread_cond_destroy(&_gotAnswer);
}

void LCDClient::sendCommand(const std::string &cmd, const std::string &parameters)
{
  if (!cmd.empty())
  {
    const LCDLock l(&_sendMutex);

    const string command = cmd + " " + parameters;

    _serverConnection << command;

    while (_answer.empty())
    {
      ::pthread_cond_wait(&_gotAnswer, &_sendMutex);
    }

    if (0 == _answer.find("huh?"))
    {
      throw LCDException(_answer.substr(5));
    }
    _answer.clear();
  }
}

void LCDClient::notifyCreated()
{
}

void LCDClient::notifyDestroyed()
{
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

void LCDClient::deleteKey(KeyEvent key)
{
  _callbacks.erase(key);
  sendCommand("client_del_key", LCDCallback::toString(key));
}

void LCDClient::mainLoop()
{
  ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);
  string reply;
  while(true)
  {
    _serverConnection >> reply;

    if ( (0 == reply.find("huh?")) || (0 == reply.compare("success")) )
    {
      const LCDLock l(&_sendMutex);
      _answer = reply;
      ::pthread_cond_signal(&_gotAnswer);
    }
    else
    {
      if (0 == reply.find("key"))
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
      else if (0 == reply.find("listen"))
      {
        _currentScreen = reply.substr(7);
      }
      else if (0 == reply.find("ignore"))
      {
        if (_currentScreen == reply.substr(7))
        {
          _currentScreen.clear();
        }
      }
      else if (0 == reply.find("menuevent"))
      {
        istringstream response(reply.substr(10));
        string menu_event_type;
        string menu_event_id;
        string menu_event_value; // N.B. Not for all event types
        response >> menu_event_type >> menu_event_id;
        if (0 == menu_event_type.compare("select"))
        {
        }
        else if (0 == menu_event_type.compare("update"))
        {
          response >> menu_event_value;
        }
        else if (0 == menu_event_type.compare("plus"))
        {
          response >> menu_event_value;
        }
        else if (0 == menu_event_type.compare("minus"))
        {
          response >> menu_event_value;
        }
        else if (0 == menu_event_type.compare("enter"))
        {
        }
        else if (0 == menu_event_type.compare("leave"))
        {
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
