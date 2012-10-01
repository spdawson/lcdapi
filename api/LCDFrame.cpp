#include "LCDFrame.h"
#include <sstream>

using namespace std;

LCDFrame::LCDFrame(LCDElement *parent, const string &id) : LCDWidget(id, parent, "frame")
{
}

void LCDFrame::set(int left, int top, int right, int bottom, int width, int height, Direction direction, int speed)
{
  _left = left;
  _top = top;
  _right = right;
  _bottom = bottom;
  _width = width;
  _height = height;
  _direction = direction;
  _speed = speed;

  notifyChanged();
}
void LCDFrame::notifyChanged()
{
  ostringstream params;

  params << _left
         << " "
         << _top
         << " "
         << _right
         << " "
         << _bottom
         << " "
         << _width
         << " "
         << _height
         << " "
         << (char)_direction
         << " "
         << _speed;

  setWidgetParameters(params.str());
}

void LCDFrame::sendCommand(const std::string &cmd, const std::string &parameters)
{
  if (_parent)
  {
    string realParams;
    if (cmd == "widget_add")
    {
      if (parameters == "frame")
      {
        realParams =  _id + " " + parameters; 
      }
      else
      {
        realParams = parameters + " " + "-in " + _id;
      }
    }
    else
    {
      realParams = parameters;
    }
    _parent->sendCommand(cmd, realParams);
  }
  else
  {
    _commandBuffer.push_back(Command(cmd, parameters));
  }
}
