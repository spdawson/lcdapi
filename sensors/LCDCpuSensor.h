#ifndef _LCD_CPU_SENSOR_H_
#define _LCD_CPU_SENSOR_H_

#include "LCDSensor.h"
#include <string>

/** \class LCDCpuSensor LCDCpuSensor.h "api/LCDCpuSensor.h"
 *  \brief A sensor for CPU usage.
 *  \ingroup sensors
 *  This sensor will return the current CPU usage.
 */

class LCDCpuSensor : public LCDSensor
{
 private:
  std::string _cpuName;
  long _userTicks;
  long _sysTicks;
  long _niceTicks;
  long _idleTicks;
  int _load;
  
  void getTicks(long &u,long &s,long &n,long &i);

 public:
  virtual void waitForChange();
  virtual std::string getCurrentValue();

  /**
   * \brief Default constructor.
   *
   * Used to build such a sensor.
   * @param cpuName The CPU this sensor should monitor. Use "cpu" for total CPU usage. "cpu0" for first CPU on an SMP machine, "cpu1" for second one,...
   */
  LCDCpuSensor(std::string cpuName = "cpu");
};

#endif
