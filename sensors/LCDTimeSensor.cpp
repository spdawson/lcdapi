#include "LCDTimeSensor.h"

#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <string>

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
