#ifndef _LCD_BAR_H_
#define _LCD_BAR_H_

#include "LCDWidget.h"
#include <string>

/** \class LCDBar LCDBar.h "api/LCDBar.h"
 *  \brief A widget to display a bar.
 *  \ingroup widgets
 * This widget is used as a base class for horizontal and vertical bars.
 */
class LCDBar : public LCDWidget
{
 protected:
  int _length;
  int _max;  
 public:
  LCDBar(const std::string &widgetType, const std::string &id, LCDElement *parent);
  LCDBar(const std::string &widgetType, int length, int x, int y, const std::string &id, LCDElement *parent);

  virtual void notifyChanged();
  /**
   * \brief Set the values for the widget.
   *
   * Set or change the useful values for this widget.
   * @param length The length of the bar in pixels.
   * @param x Integer containing 1-based value for column number.
   * @param y Integer containing 1-based value for row number.
   */
  void set(int length, int x=1, int y=1);

  /**
   * \brief Set a percentage value.
   *
   * Set or change the percentage value (0-100).
   *  - The 0 value will be represented by a bar with a 0 length.
   *  - The 100 value will be represented by a bar which length is the one specified by setPercentageMax.
   * @param value The percentage value.
   */
  void setPercentage(int value);

  /**
   * \brief Get the percentage value.
   *
   * Get the percentage value (0-100).
   * @return The percentage value.
   */
  int getPercentage();

  /**
   * \brief Set the maximum percentage value.
   *
   * Set or change the maximum percentage value.
   * It is the length for a bar with a 100% percentage.
   * @param max The maximum value in pixels.
   */
  void setPercentageMax(int max);

  virtual void valueCallback(const std::string& value);
};

#endif
