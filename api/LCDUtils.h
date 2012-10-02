#ifndef _LCD_UTILS_H_
#define _LCD_UTILS_H_

#include <cstdio>
#include <string>

namespace lcdapi {

namespace LCDUtils {
  static std::string toString(int value)
  {
    char buf[64];
    sprintf(buf, "%d", value );
    return buf;
  }
}

} // end of lcdapi namespace

#endif
