#ifndef _LCD_WIDGET_H_
#define _LCD_WIDGET_H_

/**
 * \defgroup widgets Widgets
 *  The widgets are the graphical components that can be displayed
 *   on the LCD. Each of them correspond to a different element, 
 *   so they have different properties that can be set. They share some
 *   methods, defined in the LCDWidget class.
 */

#include "LCDElement.h"
#include <string>

namespace lcdapi {

/** \class LCDWidget LCDWidget.h "api/LCDWidget.h"
 *  \brief Main class for all widgets of the API.
 *  \ingroup widgets
 *  All the widgets in this API have LCDWidget as their base class.
 *   It contains common methods. But it should not be used directly.
 */

class LCDWidget : public LCDElement
{
 protected:
  int _x, _y;
  LCDWidget(const std::string &id, LCDElement *parent, const std::string &widgetType);
  std::string _widgetType;
  void setWidgetParameters(const std::string &properties);

 public:
  enum Direction
  {
    Horizontal = 'h',
    Vertical = 'v'
  };

  virtual void notifyChanged() = 0;
  /**
   * \brief Move the widget to a new location.
   *
   * Change the coordinate of a widget.
   * Even if all the widgets have this method, it won't have an effect on all of them.
   * @param x Integer containing 1-based value for column number.
   * @param y Integer containing 1-based value for row number.
   * \see LCDScreen::setCursorPosition
   */
  void move(int x, int y = 1);

  virtual void valueCallback(const std::string& value) = 0;
};

} // end of lcdapi namespace

#endif
