#include "LCDHorizontalBar.h"
#include <sstream>

using namespace std;

LCDHorizontalBar::LCDHorizontalBar(LCDElement *parent, const string &id) : LCDBar("hbar", id, parent)
{
}

LCDHorizontalBar::LCDHorizontalBar(int length, int x, int y, LCDElement *parent, const string &id) : LCDBar("hbar", length, x, y, id, parent)
{
}
