#ifndef _LCDAPI_SENSORS_LCDKDEMULTIMEDIASENSOR_H_
#define _LCDAPI_SENSORS_LCDKDEMULTIMEDIASENSOR_H_

#include <lcdapi/sensors/LCDSensor.h>
#include <string>

namespace lcdapi {

/** \class LCDKdeMultimediaSensor LCDKdeMultimediaSensor.h "api/LCDKdeMultimediaSensor.h"
 *  \brief A sensor for KDE multimedia stuff.
 *  \ingroup sensors
 *  This sensor looks if noatun is running and get the title of the current song.
 *  If it doesn't, it will try to take the current track played by kscd, the audio CD player.
 *  A default string can be used if nothing appropriate is found.
 */
class LCDKdeMultimediaSensor : public LCDSensor
{
 private:
  std::string _previousValue;
  std::string _defaultValue;
 public:
  virtual void waitForChange();
  virtual std::string getCurrentValue();
  /**
   * \brief Default constructor.
   *
   * Used to build such a sensor.
   * @param defaultValue A string containing the value that will be used if both noatun and kscd return nothing.
   */
  explicit LCDKdeMultimediaSensor(const std::string& defaultValue = "");
  virtual ~LCDKdeMultimediaSensor();
};

} // end of lcdapi namespace

#endif