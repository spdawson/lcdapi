#ifndef _LCDAPI_SENSORS_LCDSYSTEMSENSOR_H_
#define _LCDAPI_SENSORS_LCDSYSTEMSENSOR_H_

#include <lcdapi/sensors/LCDSensor.h>
#include <string>

namespace lcdapi {

/** \class LCDSystemSensor LCDSystemSensor.h "api/LCDSystemSensor.h"
 *  \brief A sensor that executes a shell command.
 *  \ingroup sensors
 *  This sensor takes a shell command (that can call external programs) and returns first line of its output.
 */
class LCDSystemSensor : public LCDSensor
{
 private:
    std::string _command;

 public:
  virtual void waitForChange();
  virtual std::string getCurrentValue();

  /**
   * \brief Default constructor.
   *
   * Used to build such a sensor.
   * @param command A string containing the shell command to execute.
   */
  explicit LCDSystemSensor(const std::string &command);
  virtual ~LCDSystemSensor();
};

} // end of lcdapi namespace

#endif
