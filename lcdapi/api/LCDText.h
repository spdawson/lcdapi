#ifndef _LCDAPI_API_LCDTEXT_H_
#define _LCDAPI_API_LCDTEXT_H_

#include <lcdapi/api/LCDWidget.h>
#include <string>

namespace lcdapi {

/** \class LCDText LCDText.h "api/LCDText.h"
 *  \brief A widget to display some text.
 *  \ingroup widgets
 * This widget is used to display a line of text somewhere on screen.
 */
class LCDText : public LCDWidget
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
  explicit LCDText(LCDElement *parent = 0, const std::string &id = "");
  /**
   * \brief Constructor with widget values specified.
   *
   * This construct can be used to specify the values for the widget while building it.
   * @param text A string containing the text that will be displayed.
   * @param x Integer containing 1-based value for column number.
   * @param y Integer containing 1-based value for row number.
   * @param parent A pointer to parent of this screen. It should be a LCDClient object.
   * @param id A string with the identifier for the screen. If not provided, a unique one will be generated automatically.
   */
  explicit LCDText(const std::string &text, int x=1, int y=1, LCDElement *parent = 0, const std::string &id = "");

  virtual void notifyChanged();
  /**
   * \brief Set the values for the widget.
   *
   * Set or change the useful values for this widget.
   * @param text A string containing the text that will be displayed.
   * @param x Integer containing 1-based value for column number.
   * @param y Integer containing 1-based value for row number.
   */
  void set(const std::string &text, int x, int y);

  /**
   * \brief Set the displayed text.
   *
   * Set or change the text displayed on the LCD by this widget.
   * @param text A string containing the text that will be displayed.
   */
  void setText(const std::string &text);

  /**
   * \brief Get the displayed text.
   *
   * Get the text displayed on the LCD by this widget.
   * @return A string containing the text that is displayed.
   */
  const std::string& getText() const;

  virtual void valueCallback(const std::string& value);
};

} // end of lcdapi namespace

#endif
