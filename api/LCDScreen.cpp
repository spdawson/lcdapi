#include <lcdapi/api/LCDScreen.h>
#include <lcdapi/api/LCDUtils.h>

namespace lcdapi {

using namespace std;

LCDScreen::LCDScreen(LCDElement *parent, const string& name, const string& id) : LCDElement(id, "screen_add", "", parent)
{
  if (!name.empty())
  {
    setName(name);
  }
  _elementDel = "screen_del";
}

string LCDScreen::valueToString(const string& value)
{
  return value;
}

string LCDScreen::valueToString(int value)
{
  return LCDUtils::toString(value);
}

template <typename T> void LCDScreen::setScreenOption(const string& optName, T value)
{
  sendCommand("screen_set", string("-") + optName + " " + LCDScreen::valueToString(value));
}

void LCDScreen::setName(const string& name)
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

void LCDScreen::setPriority(const string& priority)
{
  setScreenOption("priority", priority);
}

void LCDScreen::setHeartBeat(const string& heartbeat)
{
  setScreenOption("heartbeat", heartbeat);
}

void LCDScreen::setBackLight(const string& backlight)
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

void LCDScreen::setCursor(const string& cursor)
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

} // end of lcdapi namespace
