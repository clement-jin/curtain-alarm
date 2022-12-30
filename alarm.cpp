#include "alarm.h"
#include "display.h"

float hours_till_alarm = 10;

int transistor_pin = A0;
int buzzer_pin = A4;

unsigned long milliseconds_till_alarm = 1000ul * 60ul * 60ul * hours_till_alarm; // only takes the integer part of this calculation
unsigned long curtain_lift_milliseconds = 28ul * 1000ul;

// everything inside alarm() is called when the alarm goes off
alarm() {
  Serial.println("bell is ringing");
  ring_bell();
}


void lift_curtain() {
  sevseg.blank();
  Serial.println(String("****************") + String("lifting curtain!") + String("*****************"));

  digitalWrite(transistor_pin, HIGH);
  delay(curtain_lift_milliseconds);
  digitalWrite(transistor_pin, LOW);

  Serial.println(String("*****************") + String("done lifting curtain!") + String("*****************"));

}

void ring_bell() {
  
  sevseg.blank();
  Serial.println(String("****************") + String("ringing bell!") + String("*****************"));

  for (int i=0; i<10; i++){
    digitalWrite(buzzer_pin, HIGH);
    delay(1000);
    digitalWrite(buzzer_pin, LOW);
    delay(1000);
  }

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
