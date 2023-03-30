#include "alarm.h"
#include "display.h"

// pin configuration
int transistor_pin = A0;
int buzzer_pin = A4;

// buzzer configuration
int no_buzzes = 2;
int buzz_duration = 1000; // how long each buzz and each delay lasts

// motor configuration
int curtain_lift_duration = 15000;


// everything inside alarm() is called when the alarm goes off
alarm() {
  int buzz_count = 0;
  int motor_reference = millis();
  int buzzer_reference = millis();
  int buzzer_state = 0;

  digitalWrite(transistor_pin, HIGH); // turn motor on
  
  while (buzz_count <= 2*no_buzzes or digitalRead(transistor_pin) == 1) { // 2 times because buzz_count counts buzzes and delays
    if (buzz_count <= 2*no_buzzes and millis() - buzzer_reference >= buzz_duration) {
        buzz_count += 1;
        digitalWrite(buzzer_pin, buzz_count % 2);
        buzzer_reference = millis();
        Serial.println(buzz_count);
    }

    if (buzz_count == 2*no_buzzes) {
      Serial.println("digital write to low");
      buzz_count += 1; // make sure the buzz_count is now greater 
      digitalWrite(buzzer_pin, LOW);
    }

    if (millis() - motor_reference >= curtain_lift_duration) {
      digitalWrite(transistor_pin, LOW);
      motor_reference = (2^15)-1; // largest value for int, so this code does not run again
    }
  }

  digitalWrite(transistor_pin, LOW); // just in case the above code fails 
  digitalWrite(buzzer_pin, LOW); // make sure the buzzer is off!!!
  
}
