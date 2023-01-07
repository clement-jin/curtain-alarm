#include "alarm.h"
#include "display.h"

// pin configuration
int transistor_pin = A0;
int buzzer_pin = A4;

// buzzer configuration
int no_buzzes = 1;
int buzz_duration = 1000; // how long each buzz and each delay lasts

// motor configuration
int curtain_lift_duration = 33000;


// everything inside alarm() is called when the alarm goes off
alarm() {
  int buzz_count = 0;
  int motor_reference = millis();
  int buzzer_reference = millis();
  int buzzer_state = 0;

  digitalWrite(transistor_pin, HIGH); // turn motor on
  
  while (buzz_count <= 2*no_buzzes or digitalRead(transistor_pin) == 1) { // 2 times because buzz_count counts buzzes and delays
    Serial.println(millis());
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


//void lift_curtain() {
//  sevseg.blank();
//  Serial.println(String("****************") + String("lifting curtain!") + String("*****************"));
//
//  digitalWrite(transistor_pin, HIGH);
//  delay(curtain_lift_milliseconds);
//  digitalWrite(transistor_pin, LOW);
//
//  Serial.println(String("*****************") + String("done lifting curtain!") + String("*****************"));
//
//}
//
//void ring_bell() {
//  
//  sevseg.blank();
//  Serial.println(String("****************") + String("ringing bell!") + String("*****************"));
//
//  for (int i=0; i<10; i++){
//    digitalWrite(buzzer_pin, HIGH);
//    delay(1000);
//    digitalWrite(buzzer_pin, LOW);
//    delay(1000);
//  }
//
//  Serial.println(String("*****************") + String("done lifting curtain!") + String("*****************"));
//  
//}
//
//void wait_a_day() {
//  unsigned long day_milliseconds = 86400000; // 1000ul * 60ul * 60ul * 24ul
//  
//  Serial.println(String("*****************") + String("waiting a day!") + String("*****************"));
//  unsigned long now = millis();
//  unsigned long day_later = now + day_milliseconds;
//
//  Serial.print(String("now: ") + String(now));
//  Serial.print(String("day_milliseconds: ") + String(day_milliseconds));
//  Serial.println(String("day_later: ") + String(day_later));
//
//  while (now < day_later) {
//    Serial.println(String("Waiting a day! --- current time: ") + String(now) + " < " + String(day_later) + String(" ---"));
//    now = millis();
//  }
//
//  Serial.println(String("*****************") + String("done waiting a day!") + String("*****************"));
//  lift_curtain();
//}
