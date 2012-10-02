#ifndef _LCD_CALLBACK_H_
#define _LCD_CALLBACK_H_

#include <string>
#include <map>

namespace lcdapi {

/**
 * \defgroup keys Keys handling
 *
 *  To assign a callback to a key event, there is the need to create
 *   a new class inheriting from LCDCallback.
 *
 *  The operator() should then be overriden to do actions. It will
 *   be called when the key event occurs.
 *  
 *  To define only a single function, there are some useful macros (see below).
 *
 *  Then the callback is associated to the event
 *   with the method LCDClient::assignKey()
 *
 */

/**
 * \ingroup keys
 * A macro that can be used when only a function is needed
 *  and not a real class.
 * Use it with the name of the pseudo function you want to create
 *  and then you can define your function code (between braces)
 */
#define LCD_CALLBACK_FUNCTION_BEGIN(fname) class LCDClass_fname : public LCDCallback \
{ \
public: \
  void operator()(KeyEvent lcdKey)

/**
 * \ingroup keys
 * A macro that can be used when only a function is needed
 *  and not a real class.
 * It has to be used after the function code and match the name
 *  that was used for LCD_CALLBACK_FUNCTION_BEGIN
 */
#define LCD_CALLBACK_FUNCTION_END(fname) \
}; \
LCDClass_fname fname;

/**
  \ingroup keys
  The type used to define a key event.
 */

typedef char KeyEvent;

/** \class LCDCallback LCDCallback.h "api/LCDCallback.h"
 *  \brief Main class to create new callback for key events.
 *  \ingroup keys
 *  To create a new key handler, one should create a derivated class
 *  from this one and implement operator ().
 */

class LCDCallback
{
 public:
  LCDCallback()
  {
  }
  virtual ~LCDCallback()
  {
  }

  /**
   * \brief Called when key event occurs.
   *
   * This method should be overrided by classes used to handle key event.
   *  It will be called when the key is pressed.
   * @param lcdKey The key that was pressed.
  */

  virtual void operator()(KeyEvent lcdKey) = 0;

  static std::string toString(KeyEvent t)
  {
    std::string s(1, static_cast<char>(t));
    return s;
  }
};

typedef std::map<KeyEvent, LCDCallback *> CallbackMap;

} // end of lcdapi namespace

#endif
