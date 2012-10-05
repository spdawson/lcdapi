#ifndef _LCD_CLIENT_H_
#define _LCD_CLIENT_H_

#include "LCDConnection.h"
#include "LCDElement.h"
#include "../keys/LCDCallback.h"
#include "../menus/LCDMenuEventHandler.h"

#include <pthread.h>
#include <string>

namespace lcdapi {

/** \class LCDClient LCDClient.h "api/LCDClient.h"
 *  \brief This is the class used to connect to LCDproc server.
 *  \ingroup main
 *  This class let a client program connect to the LCDproc server and get information from it.
 *  It will also contain information about the current LCD such as dimension.
 */

class LCDClient : public LCDElement
{
 private:
  ::pthread_mutex_t _sendMutex;
  ::pthread_cond_t _gotAnswer;
  ::pthread_t _mainThread;
  LCDConnection _serverConnection;
  std::string _answer;
  std::string _currentScreen;
  std::string _connectionString;
  std::string _serverVersion;
  std::string _protocolVersion;
  int _width;
  int _height;
  int _charWidth;
  int _charHeight;
  CallbackMap _callbacks;
  MenuEventHandlerMap _handlers;
  void mainLoop();

 protected:
  void setClientOption(const std::string& optName, const std::string& value);

 public:
  friend void *mainRepliesLoop(void *param);
  /**
   * \brief Constructor.
   *
   * This constructor needs information to connect to the LCDproc server.
   * @param server Name or IP of the machine where the server runs. If it is on the same machine, you can use "localhost".
   * @param port Port number to connect to. For a classic LCDproc configuration, it should be 13666 (default value).
   */
  explicit LCDClient(const std::string &server, int port = 13666);

  /**
   * \brief Destructor.
   *
   */
  ~LCDClient();

  /**
   * \brief Send raw commands to server.
   *
   * With this method, user can send raw commands to the server.
   * @param cmd The command to be sent.
   * @param parameters All the parameters for the command as a space separated string.
   */
  void sendCommand(const std::string &cmd, const std::string &parameters = "");

  virtual void notifyCreated();
  virtual void notifyDestroyed();

  /**
   * \brief Returns connected server version.
   *
   * Useful to know the version of the LCDproc server the object is connected to.
   * @return A string containing the server version.
   */
  const std::string &getServerVersion() const {return _serverVersion;}

  /**
   * \brief Returns protocol version used by the server.
   *
   * Useful to know the protocol version the LCDproc server (LCDd) is using.
   * @return A string containing the protocol version.
   */
  const std::string &getProtocolVersion() const {return _protocolVersion;}

  /**
   * \brief Returns LCD width.
   *
   * Returns the width (in number of characters) of the physical LCD the server is using.
   * @return An integer containing the number of characters per LCD row.
   */
  int getWidth() const {return _width;}

  /**
   * \brief Returns LCD height.
   *
   * Returns the height (in number of characters) of the physical LCD the server is using.
   * @return An integer containing the number of characters per LCD column.
   */
  int getHeight() const {return _height;}

  /**
   * \brief Get width of a character on LCD.
   *
   * Returns the maximum width (in number of pixels) of a displayed char on the LCD.
   * @return An integer containing the number of pixel used in a row of a character.
   */
  int getCharWidth() const {return _charWidth;}

  /**
   * \brief Get height of a character on LCD.
   *
   * Returns the maximum height (in number of pixels) of a displayed char on the LCD.
   * @return An integer containing the number of pixel used in a column of a character.
   */
  int getCharHeight() const {return _charHeight;}

  /**
   * \brief Change the name of the client.
   *
   * Sets the client's name as visible to a user. 
   * @param name A string containing the new name.
   */
  void setName(const std::string& name);

  /**
   * \brief Assign a callback to a key.
   *
   * Used to call a user function when a key is pressed.
   * @param key The key to assign to the function.
   * @param callback The function to call. It has to be a class inherited from LCDCallback defining the operator(). You can also use the LCD_CALLBACK_FUNCTION_BEGIN and LCD_CALLBACK_FUNCTION_END macros to define only a function.
   * \see LCDClient::deleteKey
   */
  void assignKey(KeyEvent key, LCDCallback *callback);

  /**
   * \brief Delete the callback for a key.
   *
   * Used to unregister a callback function previously registered by
   * assignKey().
   * @param key The key for which to unregister the callback function.
   * \see LCDClient::assignKey
   */
  void deleteKey(KeyEvent key);

  /**
   * \brief Register a handler for a specific event type on a specific menu.
   *
   * Used to call a user function when a menu event occurs.
   * @param menu_id The menu for which to register the handler.
   * @param menu_event The menu event type which is to be handled.
   * @param handler The handler to call. It has to be a class inherited from LCDMenuEventHandler defining the operator(). You can also use the LCD_MENUEVENTHANDLER_FUNCTION_BEGIN and LCD_MENUEVENTHANDLER_FUNCTION_END macros to define only a function.
   * \see LCDClient::unregisterMenuEventHandler
   */
  void registerMenuEventHandler(const std::string& menu_id, const std::string& menu_event, LCDMenuEventHandler* handler);

  /**
   * \brief Unregister the handler for a specific event type on a specific
   * menu.
   *
   * Used to unregister a handler previously registered by
   * registerMenuEventHandler().
   * @param menu_id The menu for which to unregister the handler.
   * @param menu_event The menu event type for which to unregister the handler.
   * \see LCDClient::registerMenuEventHandler
   */
  void unregisterMenuEventHandler(const std::string& menu_id, const std::string& menu_event);

  /**
   * \brief Change current menu to that specified.
   *
   * Used to unregister a callback function previously registered by
   * assignKey().
   * @param id The ID of the menu to use.
   */
  void menuGoto(const std::string& id = "");

  /**
   * \brief Set the entry point into the menu system.
   *
   * Used to set the specified menu as the entry point into the menu system.
   * @param id The ID of the menu to use.
   */
  void menuSetMain(const std::string& id = "");
};

} // end of lcdapi namespace

#endif
