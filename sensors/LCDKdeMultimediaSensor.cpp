#include <lcdapi/sensors/LCDKdeMultimediaSensor.h>

#include <unistd.h>

namespace lcdapi {

using namespace std;

LCDKdeMultimediaSensor::LCDKdeMultimediaSensor(const std::string& defaultValue)
  : LCDSensor(),
    _previousValue("NO"),
    _defaultValue(defaultValue)
{
}

LCDKdeMultimediaSensor::~LCDKdeMultimediaSensor()
{
}

void LCDKdeMultimediaSensor::waitForChange()
{
  while (_previousValue == getCurrentValue())
  {
    sleep(1);
  }
  _previousValue = getCurrentValue();
}

string LCDKdeMultimediaSensor::getCurrentValue()
{
  string value;

  const string noatunId = executeCommand("dcop | grep noatun");

  if (!noatunId.empty())
  {
    value = executeCommand("dcop " + noatunId + " Noatun title");
  }
  else
  {
    const string kscdTitle =
      executeCommand("dcop kscd CDPlayer currentTrackTitle");
    if (!kscdTitle.empty())
    {
      value = kscdTitle;
    }
  }

  if (value.empty())
  {
    value = _defaultValue;
  }

  return value;
}

} // end of lcdapi namespace
