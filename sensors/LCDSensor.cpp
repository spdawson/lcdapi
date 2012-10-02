#include "LCDSensor.h"
#include "LCDWidget.h"
#include "LCDUtils.h"

#include <cstring>
#include <unistd.h>

namespace lcdapi {

using namespace std;

void *updateWhenChanged(void *);
void *updateEach(void *);

const int LCDSensor::MAX_CMD_RESULT_LINE_SIZE = 255;

LCDSensor::LCDSensor()
  : _exist(true),
    _onChangeThreadStarted(false),
    _onChangeThread(static_cast<pthread_t>(-1)),
    _onChangeList(),
    _onTimeOutList()
{
}

LCDSensor::~LCDSensor()
{
  _exist = false;
  if (_onChangeThreadStarted)
  {
    if (::pthread_cancel(_onChangeThread) == 0)
    {
      ::pthread_join(_onChangeThread, 0);
    }
    _onChangeThreadStarted = false;
  }

  WidgetTimeOutList::iterator it;
  for (it = _onTimeOutList.begin(); it != _onTimeOutList.end(); it++)
  {
    if (::pthread_cancel(it->second._thread) == 0)
    {
      ::pthread_join(it->second._thread, 0);
    }
  }
}

bool LCDSensor::exists()
{
  return _exist;
}

void LCDSensor::fireChanged()
{
  string value = getCurrentValue();
  WidgetList::iterator it;
  for (it = _onChangeList.begin(); it != _onChangeList.end(); it++)
  {
    if (LCDElement::exists(it->first))
    {
      it->second->valueCallback(value);
    }
    else
    {
      removeOnChangeWidget(it->first);
    }
  }
}

const LCDWidgetTimeOut &LCDSensor::getThreadWidgetInfo(const ::pthread_t &thread)
{
  WidgetTimeOutList::iterator it;

  for (it = _onTimeOutList.begin(); it != _onTimeOutList.end(); it++)
  {
    if (::pthread_equal(thread, it->second._thread))
    {
      return it->second;
    }
  }

  static LCDWidgetTimeOut dummy;
  dummy._timeOut=0;
  dummy._widget = 0;

  return dummy;
}

string LCDSensor::intToString(int value)
{
  return LCDUtils::toString(value);
}

string LCDSensor::executeCommand(const string &cmd)
{
  string silentCmd = cmd + " 2>/dev/null";
  char buf[MAX_CMD_RESULT_LINE_SIZE + 1];
  buf[0]='\0';
  FILE *ptr;

  if ((ptr = popen(silentCmd.c_str(), "r")) != NULL)
  {
    fgets(buf, MAX_CMD_RESULT_LINE_SIZE, ptr);
    pclose(ptr);
  }

  int len = strlen(buf);

  string result(buf, (len > 0) ? (len - 1) : 0);

  return result;
}

void LCDSensor::addOnChangeWidget(LCDWidget *widget)
{
  if (!_onChangeThreadStarted)
  {
    ::pthread_create(&_onChangeThread, 0, &updateWhenChanged, this);
    _onChangeThreadStarted = true;
  }

  _onChangeList[widget->getId()] = widget;
}

void LCDSensor::removeOnChangeWidget(LCDWidget *widget)
{
  removeOnChangeWidget(widget->getId());
}

void LCDSensor::removeOnChangeWidget(const string& id)
{
  _onChangeList.erase(id);
  if (_onChangeList.empty() && _onChangeThreadStarted)
  {
    if (::pthread_cancel(_onChangeThread) == 0)
    {
      ::pthread_join(_onChangeThread, 0);
    }
    _onChangeThreadStarted = false;
  }
}

void LCDSensor::addOnTimeOutWidget(LCDWidget *widget, int timeout)
{
  LCDWidgetTimeOut tmpWidget;

  tmpWidget._timeOut = timeout;
  tmpWidget._widget = widget;
  tmpWidget._widgetId = widget->getId();

  _onTimeOutList[widget->getId()] = tmpWidget;

  ::pthread_create(&(_onTimeOutList[widget->getId()]._thread), 0, &updateEach, this);
}

void LCDSensor::removeOnTimeOutWidget(LCDWidget *widget)
{
  removeOnTimeOutWidget(widget->getId());
}

void LCDSensor::removeOnTimeOutWidget(const string& id)
{
  if (::pthread_cancel(_onTimeOutList[id]._thread) == 0)
  {
    ::pthread_join(_onTimeOutList[id]._thread, 0);
  }
  _onTimeOutList.erase(id);
}

void *updateWhenChanged(void *param)
{
  ::pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);

  LCDSensor *daddy = static_cast<LCDSensor*>(param);

  while (daddy->exists())
  {
    daddy->waitForChange();
    daddy->fireChanged();
  }

  return NULL;
}

void *updateEach(void *param)
{
  ::pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);

  LCDSensor *daddy = static_cast<LCDSensor*>(param);

  LCDWidgetTimeOut widgetInfo;

  while (!widgetInfo.isValid())
  {
    widgetInfo = daddy->getThreadWidgetInfo(::pthread_self());
    usleep(10);
  }

  while (daddy->exists())
  {
    if (LCDElement::exists(widgetInfo._widgetId))
    {
      widgetInfo._widget->valueCallback(daddy->getCurrentValue());
      usleep(widgetInfo._timeOut * 100000);
      ::pthread_testcancel();
    }
    else
    {
      daddy->removeOnTimeOutWidget(widgetInfo._widgetId);
    }
  }

  return NULL;
}

} // end of lcdapi namespace
