#include "LCDTimeSensor.h"

#include <unistd.h>

using namespace std;

LCDTimeSensor::LCDTimeSensor(const string &format)
  : LCDSensor(), _format(format)
{
}

LCDTimeSensor::~LCDTimeSensor()
{
}

void LCDTimeSensor::waitForChange()
{
  sleep(1);
}

string LCDTimeSensor::getCurrentValue()
{
  return executeCommand("date " + _format);
}
