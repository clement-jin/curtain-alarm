/*
 * Code to control the buttons and UI that will modify the time of the alarm and the clock. 
 * 
 */
#include "UI.h"

// mode_names[4] = {"display_on", "display_off", "change_current_time", "change_alarm_time"};
int mode = 0;
int mode_LED = A5;

int wakeup_time[4] = {0, 7, 0, 0}; // default wakeup time set to 7:00 WARNING: do not set this to 0000 as this will immediately trigger the alarm
int editing_digit = 0;

int digit_mods[4] = {3, 10, 6, 10}; // this specifies the largest value of each digit (e.g. the alarm clock cannot read 25:72). The digit d is taken mod digit_mods[d] to ensure this

bool is_pressed(int pin, int previous_value) {
  if (digitalRead(pin) == 0 and previous_value == 1) {
    return true;
  } else {
    return false;
  }
}

void blink_LED() {
  // blink the LED to signify change of mode
  digitalWrite(mode_LED, HIGH);
  delay(20); // modify this as this stops the display from updating!!!
  digitalWrite(mode_LED, LOW);
}

void next_digit(){
  blink_LED();
  editing_digit = (editing_digit + 1) % 4;
  Serial.println("Editing digit: " + String(editing_digit));
}

void add_one(){
  blink_LED();
  
  int modulus = digit_mods[editing_digit]; // the alarm clock cannot read certain values, e.g. 25:72 The digit d in the display is taken mod digit_mods[d] to ensure this

  
  if (mode == 3) { // if we are editing the alarm time

    // if the time reads "2xxx", and we are editing the second digit, we need to modify the modulus so it is less than 4
    if (editing_digit == 1 and wakeup_time[0] == 2) {
      modulus = 4; // then the second digit cannot be more than 3
    }
    
    // this is the main part: increasing the display by 1 
    wakeup_time[editing_digit] = (wakeup_time[editing_digit] + 1) % modulus; // add one to the editing_digit, and spill over from 9 to 0

    // update the display after an edit
    update_display(wakeup_time);  

  } else if (mode == 2) { // if we are editing the current time

    // if the time reads "2xxx", we need to modify the modulus
    if (editing_digit == 1 and display_digits[0] == 2) {
      modulus = 4; // then the second digit cannot be more than 3
    }
    // this is the main part: increasing the display by 1
    display_digits[editing_digit] = (display_digits[editing_digit] + 1) % modulus;

    // update the display after an edit
    update_display(display_digits);
  }

  
  
}

void change_mode() {
  mode = (mode + 1) % 4; // next mode in the list, but go back to 0 if it spills over
  editing_digit = 0; // reset editing digit to 0

  switch (mode) {
    case 0:
      show_display = true;
      update_display(display_digits);
      break;
    case 1:
      show_display = false;
      break;
    case 2:
      show_display = false;
      update_display(display_digits);
      break;
    case 3:
      show_display = false;
      update_display(wakeup_time);
      break;
  }

  // blink the LED to signify change of mode
  blink_LED();
  
  Serial.println("Changed mode to : " + String(mode));
}

// ========================================== MODE FUNCTIONS BELOW ======================================================
// ========================================== These blocks of code  ======================================================
// ========================================== are substituted into ======================================================
// ========================================== the loop() function ======================================================

void display_on() {
  
  update_clock();
  
}

void display_off() {
  
  sevseg.blank();

}

void change_current_time() {
 
  // final modulus check for one special case
  if (display_digits[0] == 2) {
    display_digits[1] %= 4; // take the modulus of the second digit to make sure it is less than 4
  }

  // refresh display
  // update_display(display_digits);
  refresh_display();
}

void change_alarm_time() {
  
  // final modulus check
  if (wakeup_time[0] == 2) {
    wakeup_time[1] %= 4; // take the modulus of the second digit to make sure it is less than 4
  }

  // update display
  refresh_display();
}
