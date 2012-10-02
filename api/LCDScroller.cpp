#include "LCDScroller.h"
#include <sstream>

namespace lcdapi {

using namespace std;

LCDScroller::LCDScroller(LCDElement *parent, const string &id) : LCDWidget(id, parent, "scroller"),
                                                                 _text(),
                                                                 _right(10),
                                                                 _bottom(1),
                                                                 _speed(8),
                                                                 _direction(Horizontal)

{
  _x = 1;
  _y = 1;
}

void LCDScroller::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _y
         << " "
         << _right
         << " "
         << _bottom
         << " "
         << static_cast<char>(_direction)
         << " "
         << _speed
         << " \""
         << _text
         << '"';

  setWidgetParameters(params.str());  
}

void LCDScroller::set(const string &text, int left, int top, int right, int bottom, int speed, Direction direction)
{
  _text = text;
  _x = left;
  _y = top;
  _right = right;
  _bottom = bottom;
  _speed = speed;
  _direction = direction;
  notifyChanged();
}

void LCDScroller::setText(const string &text)
{
  _text = text;
  notifyChanged();
}
const string& LCDScroller::getText() const
{
  return _text;
}
void LCDScroller::setWidth(int width)
{
  _right = _x + width - 1;
  notifyChanged();
}
void LCDScroller::setHeight(int height)
{
  _bottom = _y + height - 1;
  notifyChanged();
}
void LCDScroller::setSpeed(int speed)
{
  _speed = speed;
  notifyChanged();
}

void LCDScroller::valueCallback(const std::string& value)
{
  setText(value);
}

} // end of lcdapi namespace
