#include "display.h"


int arduino_common_pins[4] = {13, 10, 9, 7};

void update_display(int digits[4]) {

//  Serial.print("array to be printed: ");
//  print_array(digits);

  int powers_of_10[4] = {1, 10, 100, 1000}; // the pow function was unreliable (see "double-int-conversionTest.ino")
  int input = 0;

  // we have to change the array into an integer for the sevseg.setNumber function
  for (int i=0; i < 4; i++){
    input += digits[3-i] * powers_of_10[i];
  }

//  Serial.println("number that is displayed: " + String(input));
//  Serial.println(String(input));

  sevseg.setNumber(input);
}

void refresh_display() {
  sevseg.refreshDisplay();
}


/*
int arduino_segment_pins[8] = {12, 8, 5, 3, 2, 11, 6, 4}; // The pin numbers of segments {A, B, C, D, E, F, G, .} respectively ON THE ARDUINO.
int arduino_common_pins[4] = {13, 10, 9, 7}; // the same principle works behind these as the "actual_segment_pins" and "arduino_segment_pins"


// =============================== DIGIT CONFIGURATION ARRAY BELOW ================================================================
// row n of digit_configs[10][8] represents which segments to light up for the digit n.
// row n contains an array a of 8 values of either 1 or 0. The first value of a represents whether segment A should be
// turned on (1) or off (0), the second value of a represents whether segment B should be turned on or off, etc. all
// the way to the last value representing whether the segment reprenting the "." should be turned on or off.

int digit_configs[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1, 0},
  {1, 1, 1, 1, 0, 0, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 0, 1, 1, 0, 1, 1, 0},
  {1, 0, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0, 1, 1, 0}
};

// =============================== DIGIT CONFIGURATION ARRAY ABOVE ================================================================

// ---------------------------------------- DIGITS ARE INSTANTIATED BELOW -----------------------------------------------------------
Digit d1(arduino_common_pins[0]);
Digit d2(arduino_common_pins[1]);
Digit d3(arduino_common_pins[2]);
Digit d4(arduino_common_pins[3]);
Digit digits[4] = {d1, d2, d3, d4};
// adding references instead of hard coding pin numbers is more resilient to modifications
// ---------------------------------------- DIGITS ARE INSTANTIATED ABOVE -----------------------------------------------------------


Digit::Digit(int new_common_pin) {
  common_pin = new_common_pin;
};

void Digit::update_digit(int new_digit) {

  // Serial.println("printing digit: " + String(new_digit));

  // turn off all other digits
  for (int i = 0; i < 4; i++) {
    digitalWrite(arduino_common_pins[i], HIGH);
  }

  // turn on the common pin of this digit
  digitalWrite(common_pin, LOW);


  // turn on the relevant segments
  for (int i = 0; i < 8; i++) {
    int arduino_segment_pin = arduino_segment_pins[i]; // this is the pin corresponding to the segment: i=0 -> segment A, i=1 -> segment B, etc.
    int use_pin = digit_configs[new_digit][i]; // if use_pin is 1, light up segment 'arduino_segment_pin'. otherwise, do nothing.

    if (use_pin) {
      // Serial.println(arduino_segment_pin);
      digitalWrite(arduino_segment_pin, HIGH); // light up that segment
    } else {
      digitalWrite(arduino_segment_pin, LOW);
    }

  }

  // digitalWrite(common_pin, HIGH);

};


void update_display(int display_digits[4]) {
  for (int i = 0; i < 4; i++) {
    delay(20);
    // Serial.println(String(i) + " " + String(display_digits[i]));
    digits[i].update_digit(display_digits[i]);
  }

};


void Digit::test() {

}

*/
