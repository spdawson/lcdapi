#ifndef _LCD_UTILS_H_
#define _LCD_UTILS_H_

#include <cstdio>
#include <string>

namespace LCDUtils {
  static std::string toString(int value)
  {
    char buf[64];
    sprintf(buf, "%d", value );
    return buf;
  }
}

#endif
