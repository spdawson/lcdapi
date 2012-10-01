#include "LCDKdeMultimediaSensor.h"
#include "LCDUtils.h"

#include <string>
#include <unistd.h>

using namespace std;

LCDKdeMultimediaSensor::LCDKdeMultimediaSensor(std::string defaultValue)
{
  _previousValue = "NO";
  _defaultValue = defaultValue;
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

  string noatunId = executeCommand("dcop | grep noatun");

  if (noatunId != "")
  {
    value = executeCommand("dcop " + noatunId + " Noatun title");
  }
  else
  {
    string kscdTitle = executeCommand("dcop kscd CDPlayer currentTrackTitle");
    if (kscdTitle != "")
    {
      value = kscdTitle;
    }
  }

  if (value == "")
  {
    value = _defaultValue;
  }

  return value;
}
