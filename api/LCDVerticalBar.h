#ifndef _LCD_VERTICAL_BAR_H_
#define _LCD_VERTICAL_BAR_H_

#include "LCDBar.h"
#include <string>

/** \class LCDVerticalBar LCDVerticalBar.h "api/LCDVerticalBar.h"
 *  \brief A widget to display a vertical bar.
 *  \ingroup widgets
 * This widget is used to display a vertical bar somewhere on screen.
 */
class LCDVerticalBar : public LCDBar
{
 public:
  /**
   * \brief Default Constructor.
   *
   * This constructor can be used without parameter in most cases.
   * But the widget will have to be added to a parent (screen or frame).
   * @param parent A pointer to parent of this screen. It should be a LCDClient object.
   * @param id A string with the identifier for the screen. If not provided, a unique one will be generated automatically.
   */
  LCDVerticalBar(LCDElement *parent = 0, const std::string &id = "");
  /**
   * \brief Constructor with widget values specified.
   *
   * This construct can be used to specify the values for the widget while building it.
   * @param length The length of the bar in pixels.
   * @param x Integer containing 1-based value for column number.
   * @param y Integer containing 1-based value for row number.
   * @param parent A pointer to parent of this screen. It should be a LCDClient object.
   * @param id A string with the identifier for the screen. If not provided, a unique one will be generated automatically.
   */
  LCDVerticalBar(int length, int x=1, int y=1, LCDElement *parent = 0, const std::string &id = "");
};

#endif
