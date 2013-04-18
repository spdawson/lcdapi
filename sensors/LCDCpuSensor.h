#ifndef _LCDAPI_SENSORS_LCDCPUSENSOR_H_
#define _LCDAPI_SENSORS_LCDCPUSENSOR_H_

#include <lcdapi/sensors/LCDSensor.h>
#include <string>

namespace lcdapi {

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
  
  void getTicks(long &u,long &s,long &n,long &i) const;

 public:
  virtual void waitForChange();
  virtual std::string getCurrentValue();

  /**
   * \brief Default constructor.
   *
   * Used to build such a sensor.
   * @param cpuName The CPU this sensor should monitor. Use "cpu" for total CPU usage. "cpu0" for first CPU on an SMP machine, "cpu1" for second one,...
   */
  explicit LCDCpuSensor(const std::string& cpuName = "cpu");
  virtual ~LCDCpuSensor();
};

} // end of lcdapi namespace

#endif
