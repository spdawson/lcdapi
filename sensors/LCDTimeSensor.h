#ifndef _LCD_TIME_SENSOR_H_
#define _LCD_TIME_SENSOR_H_

#include "LCDSensor.h"
#include <string>

const std::string LCD_TIME_HOUR_MINUTE = "+%H:%M";
const std::string LCD_TIME_HOUR_MINUTE_SECOND = "+%H:%M:%S";

/** \class LCDTimeSensor LCDTimeSensor.h "api/LCDTimeSensor.h"
 *  \brief A sensor for current time.
 *  \ingroup sensors
 *  This sensor will return the current time in specified format.
 *  The format is the one used by date(1)
 */
class LCDTimeSensor : public LCDSensor
{
 private:
    std::string _format;

 public:
  virtual void waitForChange();
  virtual std::string getCurrentValue();

  /**
   * \brief Default constructor.
   *
   * Used to build such a sensor.
   * @param format A string containing the format to use, as defined by date(1). The default value makes this sensor return current hour and minute seperated by a colon.
   */
  LCDTimeSensor(const std::string &format = LCD_TIME_HOUR_MINUTE);
};

#endif
