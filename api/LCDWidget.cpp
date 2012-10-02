#include "LCDWidget.h"

#include <sstream>

using namespace std;

LCDWidget::LCDWidget(const string &id, LCDElement *parent, const string &widgetType) : LCDElement(id, "widget_add", widgetType, parent), _x(1), _y(1), _widgetType(widgetType)
{
  _elementDel = "widget_del";
}

LCDWidget::LCDWidget(const string &widgetType) : LCDElement("", 0), _x(1), _y(1), _widgetType(widgetType)
{
  _x = 1;
  _y = 1;
  _widgetType = widgetType;
}

void LCDWidget::move(int x, int y)
{
  _x = x;
  _y = y;
  notifyChanged();
}

void LCDWidget::setWidgetParameters(const std::string &properties)
{
  sendCommand("widget_set", properties);
}

void LCDWidget::set(const ParameterList &pList)
{
  ParameterList::const_iterator it;
  ostringstream params;
  for (it = pList.begin(); it != pList.end(); it++)
  {
    params << *it << " ";
  }

  setWidgetParameters(params.str());
}

