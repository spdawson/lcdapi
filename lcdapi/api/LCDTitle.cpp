#include <lcdapi/api/LCDTitle.h>
#include <sstream>

namespace lcdapi {

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

void LCDTitle::set(const string& text)
{
  if (_text != text) {
    _text = text;
    notifyChanged();
  }
}

const string& LCDTitle::get() const
{
  return _text;
}

void LCDTitle::valueCallback(const std::string& value)
{
  set(value);
}

} // end of lcdapi namespace