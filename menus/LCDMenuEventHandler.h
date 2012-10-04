#ifndef _LCD_MENUEVENTHANDLER_H_
#define _LCD_MENUEVENTHANDLER_H_

#include <string>
#include <map>

namespace lcdapi {

/**
 * \defgroup menus Menu event handling
 *
 *  To assign a handler to a menu event, there is the need to create
 *   a new class inheriting from LCDMenuEventHandler.
 *
 *  The operator() should then be overriden to do actions. It will
 *   be called when the menu event occurs.
 *  
 *  To define only a single function, there are some useful macros (see below).
 *
 *  Then the handler is associated to a specific menu and event type
 *   with the method LCDClient::registerMenuEventHandler()
 *
 */

/**
 * \ingroup menus
 * A macro that can be used when only a function is needed
 *  and not a real class.
 * Use it with the name of the pseudo function you want to create
 *  and then you can define your function code (between braces)
 */
#define LCD_MENUEVENTHANDLER_FUNCTION_BEGIN(fname) class LCDClass_fname : public LCDMenuEventHandler \
{ \
public: \
  void operator()(const std::string& menu_event, const std::string& value)

/**
 * \ingroup menus
 * A macro that can be used when only a function is needed
 *  and not a real class.
 * It has to be used after the function code and match the name
 *  that was used for LCD_MENUEVENTHANDLER_FUNCTION_BEGIN
 */
#define LCD_MENUEVENTHANDLER_FUNCTION_END(fname) \
}; \
LCDClass_fname fname;

/**
  \ingroup menus
  The type used to define a menu event.
 */

/** \class LCDMenuEventHandler LCDMenuEventHandler.h "menus/LCDMenuEventHandler.h"
 *  \brief Main class to create new handler for menu events.
 *  \ingroup menus
 *  To create a new menu event handler, one should create a derivated class
 *  from this one and implement operator ().
 */

class LCDMenuEventHandler
{
 public:
  LCDMenuEventHandler()
  {
  }
  virtual ~LCDMenuEventHandler()
  {
  }

  /**
   * \brief Called when menu event occurs.
   *
   * This method should be overrided by classes used to handle menu event.
   *  It will be called when the menu event occurs.
   * @param menu_event The menu event type.
   * @param value The updated menu value (always empty for some event types).
  */

  virtual void operator()(const std::string& menu_event, const std::string& value) = 0;
};

typedef std::map<std::string, std::map<std::string, LCDMenuEventHandler *> >
  MenuEventHandlerMap;

} // end of lcdapi namespace

#endif
