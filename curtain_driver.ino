#include "display.h"
#include "alarm.h"
#include "clock.h"
#include "UI.h"
#include "SevSeg.h"

SevSeg sevseg;

// these are the pins for the buttons that will control various configurations
int next_digit_pin = A1;
int add_one_pin = A2;
int change_mode_pin = A3;

// initial previous values for the pins
bool next_digit_previous = 1;
bool add_one_previous = 1;
bool change_mode_previous = 1;

void setup() {
  Serial.begin(9600);

  // this is for the transistor_pin in alarm.cpp
  pinMode(transistor_pin, OUTPUT);

  // this is for the arduino_common_pins in display.cpp
  for (int i = 0; i < 4; i++) {
    pinMode(arduino_common_pins[i], OUTPUT);
    digitalWrite(arduino_common_pins[i], HIGH);
  }

    // seting configuration options for the SevSeg library
  byte numDigits = 4;
  byte digitPins[] = {13, 10, 9, 7};
  byte segmentPins[] = {12, 8, 5, 3, 2, 11, 6, 4};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = true; // this retains leading zeros
  bool disableDecPoint = false; // we still account for the decimal point 
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(30);

  // we make the pins for the buttons all pullup. i.e. they will register as high if the button is not pushed,
  // and will register as low if the button is pushed
  pinMode(next_digit_pin, INPUT_PULLUP);
  pinMode(add_one_pin, INPUT_PULLUP);
  pinMode(change_mode_pin, INPUT_PULLUP);
  
  pinMode(mode_LED, OUTPUT);

  update_display(display_digits); // initially, we manually update the display so it turns on

  //  Serial.println(String("milliseconds_till_alarm") + milliseconds_till_alarm);

}

void loop() {

  // runs the code corresponding to what mode the alarm is in. This will most often be display_on or display_off.
  if (mode == 0) {
    display_on();
  } else if (mode == 1) {
    display_off();
  } else if (mode == 2) {
    change_current_time();
  } else if (mode == 3) {
    change_alarm_time();
  } else {
    Serial.println("ERROR: UNKNOWN MODE NUMBER: " + String(mode));
  }

  if (is_pressed(next_digit_pin, next_digit_previous)) {
    next_digit();
  } else if (is_pressed(add_one_pin, add_one_previous)) {
    // editing_digit = 0; // reset the editing digit to the first digit
    add_one();
  } else if (is_pressed(change_mode_pin, change_mode_previous)) {
    // editing_digit = 0; // reset the editing digit to the first digit
    change_mode();
  };

  // sets previous value of the button. This ensures that holding the button does not run the same function many times
  next_digit_previous = digitalRead(next_digit_pin);
  add_one_previous = digitalRead(add_one_pin);
  change_mode_previous = digitalRead(change_mode_pin);


// comparing the 2 arrays. If the wakeup_time is equal to the current time (i.e. display_digits), then lift the curtain
// this uses the voodoo function memcmp. Find more info at https://forum.arduino.cc/t/how-to-compare-arrays/76556/7
  if (memcmp( (const void *)display_digits, (const void *)wakeup_time, sizeof(display_digits)) == 0 and mode == 0) { // only lift the curtain if we are in display mode
    // Serial.println("lifting curtain!!!");
    lift_curtain();
  }

}
