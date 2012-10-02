#include "LCDIcon.h"
#include <sstream>

using namespace std;

LCDIcon::LCDIcon(LCDElement *parent, const string &id) : LCDWidget(id, parent, "icon"), _type()
{
}

LCDIcon::LCDIcon(const string &type, int x, int y, LCDElement *parent, const string &id) : LCDWidget(id, parent, "string"), _type(type)
{
  set(type, x, y);
}

void LCDIcon::set(const string &type, int x, int y)
{
  _type = type;
  _x = x;
  _y = y;
  notifyChanged();
}
void LCDIcon::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _y
         << " "
         << _type;

  setWidgetParameters(params.str());
}

void LCDIcon::setIcon(const string &type)
{
  _type = type;
  notifyChanged();
}

const string& LCDIcon::getIcon() const
{
  return _type;
}
