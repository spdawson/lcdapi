#include "LCDException.h"

namespace lcdapi {

LCDException::LCDException(const std::string& desc)
  : _desc(desc)
{
}

LCDException::~LCDException()
{
}

LCDException::LCDException(const LCDException& original)
  : _desc(original._desc)
{
}

const LCDException& LCDException::operator=(const LCDException& rhs)
{
  if (&rhs != this) {
    _desc = rhs._desc;
  }

  return *this;
}

std::string LCDException::what() const
{
  return std::string("LCD Error : ") + _desc;
}

} // end of lcdapi namespace
