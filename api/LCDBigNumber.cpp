#include "LCDBigNumber.h"
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

const int LCDBigNumber::LCD_COLON = 10;

LCDBigNumber::LCDBigNumber(LCDElement *parent, const string &id) : LCDWidget(id, parent, "num")
{
  _position = 1;
  _number = 0;
}

LCDBigNumber::LCDBigNumber(int number, int x, LCDElement *parent, const string &id) : LCDWidget(id, parent, "num")
{
  _position = 1;
  set(number, x);
}

void LCDBigNumber::setNumberPosition(int position)
{
  _position = position;
}

void LCDBigNumber::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _number;

  setWidgetParameters(params.str());
}

void LCDBigNumber::set(int number, int x)
{
  _number = number;
  _x = x;
  notifyChanged();
}

void LCDBigNumber::setNumber(int number)
{
  _number = number;
  notifyChanged();
}

int LCDBigNumber::getNumber() const
{
  return _number;
}

void LCDBigNumber::valueCallback(string value)
{
  int max = value.size();
  int position = max - _position;
  if (position < 0)
  {
    _number = 0;
  }
  else
  {
    _number = atoi(value.substr(position,1).c_str());
  }
  notifyChanged();
}
