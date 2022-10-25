#include "alarm.h"

float hours_till_alarm = 10;

int transistor_pin = A0;
unsigned long milliseconds_till_alarm = 1000ul * 60ul * 60ul * hours_till_alarm; // only takes the integer part of this calculation
unsigned long curtain_lift_milliseconds = 28ul * 1000ul;

void lift_curtain() {

  Serial.println(String("****************") + String("lifting curtain!") + String("*****************"));

  digitalWrite(transistor_pin, HIGH);
  delay(curtain_lift_milliseconds);
  digitalWrite(transistor_pin, LOW);

  Serial.println(String("*****************") + String("done lifting curtain!") + String("*****************"));

}

void wait_a_day() {
  unsigned long day_milliseconds = 86400000; // 1000ul * 60ul * 60ul * 24ul
  
  Serial.println(String("*****************") + String("waiting a day!") + String("*****************"));
  unsigned long now = millis();
  unsigned long day_later = now + day_milliseconds;

  Serial.print(String("now: ") + String(now));
  Serial.print(String("day_milliseconds: ") + String(day_milliseconds));
  Serial.println(String("day_later: ") + String(day_later));

  while (now < day_later) {
    Serial.println(String("Waiting a day! --- current time: ") + String(now) + " < " + String(day_later) + String(" ---"));
    now = millis();
  }

  Serial.println(String("*****************") + String("done waiting a day!") + String("*****************"));
  lift_curtain();
}
