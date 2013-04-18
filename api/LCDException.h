#ifndef _LCDAPI_API_LCDEXCEPTION_H_
#define _LCDAPI_API_LCDEXCEPTION_H_

#include <string>

namespace lcdapi {

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

  explicit LCDException(const std::string& desc);

  ~LCDException();

  LCDException(const LCDException& original);
  const LCDException& operator=(const LCDException& rhs);

  /**
   * \brief Get a textual description of the problem that occured.
   *
   * When an exception is caught, this method can be called to have a description of the problem.
   * \return A string containing the error description.
   */
  std::string what() const;
};

} // end of lcdapi namespace

#endif
