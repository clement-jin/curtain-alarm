#ifndef DISPLAY_H // if this hasn't been defined yet
#define DISPLAY_H // then define it

#include "Arduino.h"
#include "SevSeg.h"

void update_display(int display_digits[4]);
void refresh_display();
extern int arduino_common_pins[4];
//SevSeg sevseg;

/*
class Digit {
  public:

  int common_pin;

  Digit(int new_common_pin); // declaring the constructor function
  void update_digit(int new_digit);
  void test();


  private:
};

void update_display(int display_digits[4]);

extern int arduino_common_pins[4];

*/

#endif
