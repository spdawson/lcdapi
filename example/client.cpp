#include "LCDHeaders.h"
#include <iostream>
#include <signal.h>

using namespace std;


LCD_CALLBACK_FUNCTION_BEGIN(forA)
{
  cout << " I got " << lcdKey << endl;
}
LCD_CALLBACK_FUNCTION_END(forA)

class TitleSwitcher: public LCDCallback
{
 private:
  LCDTitle *_title;
  string _firstText, _secondText;
 public:
  TitleSwitcher(LCDTitle *title, string secondText)
  {
    _title = title;
    _firstText = _title->get();
    _secondText = secondText;
  }
  void operator()(KeyEvent key)
  {
    if (_title->get() == _firstText)
    {
      _title->set(_secondText);
    }
    else
    {
      _title->set(_firstText);
    }
  }
};

bool thisIsTheEnd;
void intHandler(int sig)
{
  thisIsTheEnd = true;
}

int main(char **argv, int argc)
{
  try
  {

    LCDClient client("localhost", 13666);

    cout << "Server information" << endl
         << "  Version :\t" << client.getServerVersion() << endl
         << "  Protocol :\t" << client.getProtocolVersion() << endl
         << "  Width :\t" << client.getWidth() << endl
         << "  Height :\t" << client.getHeight() << endl
         << "  Char Width :\t" << client.getCharWidth() << endl
         << "  Char Height :\t" << client.getCharHeight() << endl;

    client.setBackLight(LCD_BACKLIGHT_ON);

    /* First screen */

    LCDScreen screen1(&client);
    screen1.setDuration(32);

    LCDTitle title("Current Song");
    screen1.add(&title);

    LCDScroller scroll(&screen1);
    scroll.setWidth(20);
    scroll.setSpeed(3);
    scroll.move(1, 3);

    LCDKdeMultimediaSensor myMM("No title");
    myMM.addOnChangeWidget(&scroll);

    /* Second screen */

    LCDScreen screen2(&client);
    screen2.setDuration(32);

    LCDBigNumber num1(&screen2);
    num1.set(0,1);
    num1.setNumberPosition(5);
    LCDBigNumber num2(&screen2);
    num2.set(0,5);
    num2.setNumberPosition(4);
    LCDBigNumber num3(&screen2);
    num3.set(0,13);
    num3.setNumberPosition(2);
    LCDBigNumber num4(&screen2);
    num4.set(0,17);
    num4.setNumberPosition(1);


    LCDTimeSensor myTime;
    myTime.addOnChangeWidget(&num1);
    myTime.addOnChangeWidget(&num2);
    myTime.addOnChangeWidget(&num3);
    myTime.addOnChangeWidget(&num4);

    /* Third screen */

    LCDText title2("CPU usage");

    LCDCpuSensor myCpu;

    LCDHorizontalBar bar;
    bar.move(1,3);
    bar.setPercentageMax(client.getWidth() * client.getCharWidth());

    LCDText cpuText;
    cpuText.move(16,4);
    LCDText percent("%", 19, 4);
 
    myCpu.addOnChangeWidget(&bar);
    myCpu.addOnChangeWidget(&cpuText);

    LCDScreen screen3(&client);
    screen3.add(&bar);
    screen3.add(&title2);
    screen3.add(&cpuText);
    screen3.add(&percent);
    screen3.setDuration(32);

    client.assignKey('A', &forA);

    TitleSwitcher ts(&title, "Titre courant");
    client.assignKey('B', &ts);

    thisIsTheEnd = false;

    signal(SIGINT, intHandler);

    while (!thisIsTheEnd)
    {
      sleep(10);
    }
    
    cout << "Ending" << endl;

  }
  catch (LCDException e)
  {
    cerr << e.what() << endl;
  }
}
