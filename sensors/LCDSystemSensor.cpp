#include "LCDSystemSensor.h"

#include <unistd.h>

using namespace std;

LCDSystemSensor::LCDSystemSensor(const string &command)
{
  _command = command;
}

void LCDSystemSensor::waitForChange()
{
  sleep(1);
}

string LCDSystemSensor::getCurrentValue()
{
  return executeCommand(_command);
}
