/* Elcd.h - Library to use ELCD screen with arduino.
   Created by Hugues D. on 2015 June.
   Released into the public domain.
   */

#ifndef Elcd_h
#define Elcd_h

#include "Arduino.h"

class Elcd {
public:
  Elcd(int rate, int pixelX, int pixelY);
  void init();
  void clear();
  void locate(int indexX, int indexY);
  void csroff();
  void csrfc();
  void csron();
  void csrcb();
  void print(char *chr);
  void println(char *chr);
  void mkchar(byte index, byte newChar[], byte showAfter);
  void logging(char *chr);
private:
  int _rate;
  int _maxIndexX;
  int _maxIndexY;
  int _indexY;
};

#endif
