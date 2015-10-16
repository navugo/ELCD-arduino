#include "Arduino.h"
#include "Elcd.h"

/* Initiate the class with the speed rate and LCD size.
   With 4x20 ELCD from COMFILE (Lextronic), usual settings are:
   - rate = 19200
   - pixelX = 200
   - pixelY = 4
*/
Elcd::Elcd(int rate, int pixelX, int pixelY) {
  _rate = rate;
  _maxIndexX = pixelX -1; // Starts at 0.
  _maxIndexY = pixelY -1;
  _indexY =0;
}

/* Initialize Serial interface & LCD.
   It has to be called only once in setup().
*/
void Elcd::init() {
  Serial.begin(_rate);
  Serial.write(0xA0);
  delay(200);
}

/* Clear LCD display. */
void Elcd::clear() {
  Serial.write(0xA3);
  Serial.write(0x01);
  Elcd::locate(0, 0);  // This should not be necessary.
//  delay(200);
}

/* Locate the cursor on position x (horizontal), y (vertical). */
void Elcd::locate(int indexX, int indexY) {
  Serial.write(0xA1);
  Serial.write(indexX);
  Serial.write(indexY);
}

/* Switch the cursor off. */
void Elcd::csroff() {
  Serial.write(0xA3);
  Serial.write(0x0C);
}

/* Switch on LCD a full cell cursor. */
void Elcd::csrfc() {
  Serial.write(0xA3);
  Serial.write(0x0D);
}

/* Switch on LCD an underscore cursor. */
void Elcd::csron() {
  Serial.write(0xA3);
  Serial.write(0x0E);
}

/* Switch on LCD a combined cursor. */
void Elcd::csrcb() {
  Serial.write(0xA3);
  Serial.write(0x0F);
}

/* Print *str, starting at the last position of cursor. */
void Elcd::print(char *chr) {
  Serial.write(0xA2);
  while(*chr) Serial.write(*chr++);
  Serial.write(0);
}

/* Idem as Elcd:print, except it adds a \r\n at the end of the message,
   for the computer console.
   */
void Elcd::println(char *chr) {
  Serial.write(0xA2);
  while(*chr) Serial.write(*chr++);
  Serial.write(0);
  Serial.write(0x0A);
}

/* Create a new character,and store it in memory and/or print it.
   Characters can be stored in 8 (0x08) to 15 (0x0F) memory space
   of the LCD. Then it will have to be call with the print function
   and its relative memory number.
   */
void Elcd::mkchar(byte index, byte newChar[], byte showAfter) {
  if(showAfter)
    Serial.write(0xA4);
  else
    Serial.write(0xA5);
  Serial.write(index);
  Serial.write(newChar[0] & 0x1F);
  Serial.write(newChar[1] & 0x1F);
  Serial.write(newChar[2] & 0x1F);
  Serial.write(newChar[3] & 0x1F);
  Serial.write(newChar[4] & 0x1F);
  Serial.write(newChar[5] & 0x1F);
  Serial.write(newChar[6] & 0x1F);
  Serial.write(newChar[7] & 0x1F);
}

/* Almost like println, but it allows to take care automatically of
   the position of the sentence on the LCD screen, by incrementing
   the line location, and erasing the screen when necessary.
   Usefull for application logs.
   */
void Elcd::logging(char *chr) {
  // Firstly, clear screen if cursor is back to first line.
  if (_indexY == 0) { Elcd::clear(); }
  Elcd::locate(0, _indexY);
  Serial.write(0xA2);
  while(*chr) Serial.write(*chr++);
  Serial.write(0);
  Serial.write(0x0A);
  if (_indexY >= _maxIndexY) {
    _indexY =0;
  } else {
    _indexY +=1;
  }
}
