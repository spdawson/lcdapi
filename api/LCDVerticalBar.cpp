#include "LCDVerticalBar.h"

using namespace std;

LCDVerticalBar::LCDVerticalBar(LCDElement *parent, const string &id) : LCDBar("vbar", id, parent)
{
}

LCDVerticalBar::LCDVerticalBar(int length, int x, int y, LCDElement *parent, const string &id) : LCDBar("vbar", length, x, y, id, parent)
{
}
