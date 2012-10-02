#include "LCDUtils.h"

#include <sstream>

namespace lcdapi {

using namespace std;

namespace LCDUtils {
  string toString(int value)
  {
    ostringstream ss;
    ss << value;
    return ss.str();
  }
}

} // end of lcdapi namespace
