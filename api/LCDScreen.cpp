#include "LCDScreen.h"
#include "LCDUtils.h"

using namespace std;

LCDScreen::LCDScreen(LCDElement *parent, string name, string id) : LCDElement(id, "screen_add", "", parent)
{
  if (name != "")
  {
    setName(name);
  }
  _elementDel = "screen_del";
}

string LCDScreen::valueToString(string value)
{
  return value;
}

string LCDScreen::valueToString(int value)
{
  return LCDUtils::toString(value);
}

template <typename T> void LCDScreen::setScreenOption(string optName, T value)
{
  sendCommand("screen_set", string("-") + optName + " " + LCDScreen::valueToString(value));
}

void LCDScreen::setName(string name)
{
  setScreenOption("name", name);
}

void LCDScreen::setWidth(int width)
{
  setScreenOption("wid", width);
}

void LCDScreen::setHeight(int height)
{
  setScreenOption("hgt", height);
}

void LCDScreen::setPriority(string priority)
{
  setScreenOption("priority", priority);
}

void LCDScreen::setHeartBeat(string heartbeat)
{
  setScreenOption("heartbeat", heartbeat);
}

void LCDScreen::setBackLight(string backlight)
{
  setScreenOption("backlight", backlight);
}

void LCDScreen::setDuration(int secondEights)
{
  setScreenOption("duration", secondEights);
}

void LCDScreen::setTimeOut(int secondEights)
{
  setScreenOption("timeout", secondEights);
}

void LCDScreen::setCursor(string cursor)
{
  setScreenOption("cursor", cursor);
}

void LCDScreen::setCursorX(int x)
{
  setScreenOption("cursor_x", x);
}

void LCDScreen::setCursorY(int y)
{
  setScreenOption("cursor_y", y);
}

void LCDScreen::setCursorPosition(int x, int y)
{
  setCursorX(x);
  setCursorY(y);
}
