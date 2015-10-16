/* Elcd.ino - Example for Elcd library.
   Created by Hugues D. on 2015, June.
   Released into the public domain.
*/

#include <Elcd.h>

Elcd lcd(19200, 20, 4);

void setup() {
  lcd.init();
  lcd.csroff();
  lcd.locate(4, 1);
  lcd.print("ELCD Library");
  lcd.locate(13, 3);
  lcd.println("v. 0.2");
  delay(1000);
}

void loop() {
  lcd.clear();
  lcd.csron();
  lcd.logging("[info] just a word");
  delay(500); // To understand what happens
  lcd.logging("[info] take care, this is too long for the screen");
  delay(500); // To understand what happens
  lcd.logging("what's now?");
  delay(500); // To understand what happens
  lcd.logging("May I fill the 4th line?");
  delay(500); // To understand what happens
  lcd.logging("Next page...");
  while(true);  // End of example.
}
