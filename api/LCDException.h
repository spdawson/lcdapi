#ifndef _LCD_EXCEPTION_H_
#define _LCD_EXCEPTION_H_

#include "LCDConstants.h"
#include <exception>
#include <string>

/** \class LCDException LCDException.h "api/LCDException.h"
 *  \brief The exceptions thrown by this API.
 *  \ingroup main
 * This class is for the exceptions thrown by the API if a problem occurs.
 */
class LCDException
{
 private:
  std::string _desc;

 public:

  LCDException(std::string desc)
  {
    _desc = desc;
  }

  ~LCDException()
  {
  }

  /**
   * \brief Get a textual description of the problem that occured.
   *
   * When an exception is caught, this method can be called to have a description of the problem.
   * \return A string containing the error description.
   */
  std::string what()
  {
    return std::string("LCD Error : ") + _desc;
  }
};

#endif
