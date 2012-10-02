#include "LCDTimeSensor.h"

#include <unistd.h>

using namespace std;

LCDTimeSensor::LCDTimeSensor(const string &format)
{
  _format = format;
}

void LCDTimeSensor::waitForChange()
{
  sleep(1);
}

string LCDTimeSensor::getCurrentValue()
{
  return executeCommand("date " + _format);
}
