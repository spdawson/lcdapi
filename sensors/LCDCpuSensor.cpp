#include "LCDCpuSensor.h"

#include <fstream>
#include <unistd.h>

using namespace std;

LCDCpuSensor::LCDCpuSensor(const string& cpuName)
  : LCDSensor(),
    _cpuName("cpu"),
    _userTicks(0),
    _sysTicks(0),
    _niceTicks(0),
    _idleTicks(0),
    _load(0)
{
}

LCDCpuSensor::~LCDCpuSensor()
{
}

void LCDCpuSensor::waitForChange()
{
  sleep(1);
}

string LCDCpuSensor::getCurrentValue()
{
  long uTicks, sTicks, nTicks, iTicks;

  getTicks(uTicks, sTicks, nTicks, iTicks);

  const long totalTicks = ((uTicks - _userTicks) +
                           (sTicks - _sysTicks) +
                           (nTicks - _niceTicks) +
                           (iTicks - _idleTicks));

  int load  = (totalTicks == 0) ? 0 : int( 100.0 * ( (uTicks+sTicks+nTicks) - (_userTicks+_sysTicks+_niceTicks))/( totalTicks+0.001) + 0.5 );

  _userTicks = uTicks;
  _sysTicks = sTicks;
  _niceTicks = nTicks;
  _idleTicks = iTicks;

  return intToString(load);
}

void LCDCpuSensor::getTicks (long &u,long &s,long &n,long &i) const
{
    fstream file;
    string item = "";

    file.open("/proc/stat", ios::in);

    if (file.is_open())
    {
      while (item != _cpuName)
      {
        file >> item;
      }
      file >> u >> s >> n >> i;
      
      file.close();
    }
    else
    {
        u = 0;
        s = 0;
        n = 0;
        i = 0;
    }

}
