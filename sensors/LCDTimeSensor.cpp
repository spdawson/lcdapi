#include "LCDTimeSensor.h"

namespace lcdapi {

using namespace std;

LCDTimeSensor::LCDTimeSensor(const string &format)
  : LCDSystemSensor(string("date ") + format)
{
}

LCDTimeSensor::~LCDTimeSensor()
{
}

} // end of lcdapi namespace
