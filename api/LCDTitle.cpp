#include "LCDTitle.h"
#include <sstream>

using namespace std;

LCDTitle::LCDTitle(LCDElement *parent, const string &id) : LCDWidget(id, parent, "title"), _text()
{
}

LCDTitle::LCDTitle(const string &text, LCDElement *parent, const string &id) : LCDWidget(id, parent, "title"), _text(text)
{
  set(text);
}

void LCDTitle::notifyChanged()
{
  ostringstream params;

  params << '"'
         << _text
         << '"';

  setWidgetParameters(params.str());
}

void LCDTitle::set(string text)
{
  _text = text;
  notifyChanged();
}

string LCDTitle::get() const
{
  return _text;
}

void LCDTitle::valueCallback(std::string value)
{
  set(value);
}
