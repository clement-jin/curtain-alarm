#include "clock.h"
#include "Arduino.h"


int time_mode = 24; // either 24 or 12, to signify 24 or 12 hour time respectively.
int display_digits[4] = {0, 0, 0, 0};
bool show_display = true;

unsigned long last_millis = millis();

void update_clock() {
  // always update the display
  if (show_display) {
    refresh_display();
  }

  // check if 1 minute has passed yet. If so, change the display time. 
  unsigned long current_millis = millis();
  if (current_millis - last_millis >= 1000) { // this needs to be configured back to 60 seconds instead of 1 second. 
    last_millis = current_millis;
    increment_clock();
    // Serial.println("1 second passed");
  }
}

void increment_clock() {
  // this is a clumsy but sufficient way of rolling over digits. It is acceptable, as there are very few special cases that are easy to deal with.
  if (display_digits[3] != 9) { // if the last digit is not 9, we do not have to worry about rolling over
    display_digits[3] += 1;
  } else if (display_digits[3] == 9 and display_digits[2] < 5) { // for numbers 09, 19, 29, 39, 49, we roll over to the next 10
    display_digits[2] += 1;
    display_digits[3] = 0;
  } else if (display_digits[3] == 9 and display_digits[2] == 5) { // if the seconds display 59, we rolle over to 00 and add 1 hour to the hours section
    display_digits[2] = 0;
    display_digits[3] = 0;
    display_digits[1] += 1;

    // we now need to check if the hours digit needs to roll over
    if (display_digits[1] == 10) {
      display_digits[1] = 0;
      display_digits[0] += 1;
    } else if (display_digits[0] == 2 and display_digits[1] == 4) { // reset for the new day at 0000
      display_digits[0] = 0;
      display_digits[1] = 0;
    }
  } else {
    Serial.print("ERROR! Unknown case for incrementing the clock: ");
    print_display_digits();
  }

  update_display(display_digits);
}

void print_display_digits() {
  for (int i=0; i < 4; i++) {
      Serial.print(display_digits[i]);
    }
    Serial.println();
}
