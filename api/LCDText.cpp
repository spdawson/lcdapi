#include "LCDText.h"
#include <sstream>

namespace lcdapi {

using namespace std;

LCDText::LCDText(LCDElement *parent, const string &id) : LCDWidget(id, parent, "string"), _text()
{
}

LCDText::LCDText(const string &text, int x, int y, LCDElement *parent, const string &id) : LCDWidget(id, parent, "string"), _text(text)
{
  set(text, x, y);
}

void LCDText::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _y
         << " \""
         << _text
         << '"';

  setWidgetParameters(params.str());
}

void LCDText::set(const string &text, int x, int y)
{
  _x = x;
  _y = y;
  _text = text;
  notifyChanged();
}

void LCDText::setText(const string &text)
{
  _text = text;
  notifyChanged();
}

const string& LCDText::getText() const
{
  return _text;
}

void LCDText::valueCallback(const string& value)
{
  setText(value);
}

} // end of lcdapi namespace
