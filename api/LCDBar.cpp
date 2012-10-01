#include "LCDBar.h"
#include <cstdlib>
#include <sstream>
#include <stdlib.h>

using namespace std;

LCDBar::LCDBar(const string &widgetType, const string &id, LCDElement *parent) : LCDWidget(id, parent, widgetType)
{
  _length = 0;  
  _max = 100;
}

LCDBar::LCDBar(const string &widgetType, int length, int x, int y, const string &id, LCDElement *parent) : LCDWidget(id, parent, widgetType)
{
  set(length, x, y);
}

void LCDBar::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _y
         << " "
         << _length;

  setWidgetParameters(params.str());
}

void LCDBar::set(int length, int x, int y)
{
  _length = length;
  _x = x;
  _y =y;
  notifyChanged();
}

void LCDBar::setPercentage(int value)
{
  _length = (value * _max) / 100;
  notifyChanged();
}

int LCDBar::getPercentage()
{
  return ((_length * 100) / _max);

}

void LCDBar::setPercentageMax(int max)
{
  _max = max;
}

void LCDBar::valueCallback(string value)
{
  setPercentage(atoi(value.c_str()));
}
