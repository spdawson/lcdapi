#ifndef _LCD_TITLE_H_
#define _LCD_TITLE_H_

#include "LCDWidget.h"
#include <string>

/** \class LCDTitle LCDTitle.h "api/LCDTitle.h"
 *  \brief A widget to display a title.
 *  \ingroup widgets
 * This widget is used to display a title on first line of the LCD.
 */
class LCDTitle : public LCDWidget
{
 private:
  std::string _text;
 public:
  /**
   * \brief Default Constructor.
   *
   * This constructor can be used without parameter in most cases.
   * But the widget will have to be added to a parent (screen or frame).
   * @param parent A pointer to parent of this screen. It should be a LCDClient object.
   * @param id A string with the identifier for the screen. If not provided, a unique one will be generated automatically.
   */
  LCDTitle(LCDElement *parent = 0, const std::string &id = "");
  /**
   * \brief Constructor with widget values specified.
   *
   * This construct can be used to specify the values for the widget while building it.
   * @param text A string containing the text that will be displayed.
   * @param parent A pointer to parent of this screen. It should be a LCDClient object.
   * @param id A string with the identifier for the screen. If not provided, a unique one will be generated automatically.
   */
  LCDTitle(const std::string &text, LCDElement *parent = 0, const std::string &id = "");

  virtual void notifyChanged();
  virtual void valueCallback(const std::string& value);

  /**
   * \brief Set the text for the widget.
   *
   * Set or change the text used for the title.
   * @param text A string containing the title that will be displayed.
   */

  void set(const std::string& text);
  /**
   * \brief Get the text for the widget.
   *
   * G the text used for the title.
   * @return A string containing the title that is displayed.
   */
  std::string get() const;
};

#endif
