#include <lcdapi/sensors/LCDSystemSensor.h>

#include <unistd.h>

namespace lcdapi {

using namespace std;

LCDSystemSensor::LCDSystemSensor(const string &command)
  : LCDSensor(), _command(command)
{
}

LCDSystemSensor::~LCDSystemSensor()
{
}

void LCDSystemSensor::waitForChange()
{
  sleep(1);
}

string LCDSystemSensor::getCurrentValue()
{
  return executeCommand(_command);
}

} // end of lcdapi namespace
