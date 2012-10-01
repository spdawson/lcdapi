#include "LCDSystemSensor.h"

#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <string>

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
