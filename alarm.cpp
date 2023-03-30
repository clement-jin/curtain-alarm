#include "alarm.h"
#include "display.h"
#include "clock.h"

// pin configuration
int transistor_pin = A0;
int buzzer_pin = A4;

// buzzer configuration
int no_buzzes = 5;
unsigned long buzz_duration = 1000; // how long each buzz and each delay lasts

// motor configuration
unsigned long curtain_lift_duration = 30000;


// everything inside alarm() is called when the alarm goes off
alarm() {

  increment_clock(true); // so the function is not called repeatedly
  
  sevseg.setChars("HEYO");
  
  int buzz_count = 0;
  unsigned long motor_reference = millis();
  unsigned long buzzer_reference = millis();
  int buzzer_state = 0;

  Serial.println("motor ON");
  
  digitalWrite(transistor_pin, HIGH); // turn motor on
  
  while (buzz_count <= 2*no_buzzes or (millis() - motor_reference < curtain_lift_duration)) { // 2 times because buzz_count counts buzzes and delays

    sevseg.refreshDisplay();
    
    if (buzz_count <= 2*no_buzzes and millis() - buzzer_reference >= buzz_duration) {
        buzz_count += 1;
        digitalWrite(buzzer_pin, buzz_count % 2);
        buzzer_reference = millis();
        Serial.println("Buzz times: " + String(buzz_count/2));
    }

    if (buzz_count == 2*no_buzzes) {
      Serial.println("turned buzzer off");
      buzz_count += 1; // make sure the buzz_count is now greater 
      digitalWrite(buzzer_pin, LOW);
    }

    if (millis() - motor_reference >= curtain_lift_duration) {
      digitalWrite(transistor_pin, LOW);
    }
  }

  Serial.println("Alarm Sequence Finished!");
  update_display(display_digits);
  
}


check_alarm() {
  bool ring_alarm = true;
  for (int i=0; i<4; i++) {
    if (display_digits[i] != wakeup_time[i]) {
      ring_alarm = false;
    }
  }
  if (ring_alarm == true) {
    Serial.println("ALARM STARTING");
    alarm();
  }
}
