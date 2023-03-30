#ifndef ALARM_H
#define ALARM_H
#include "Arduino.h"

extern float hours_till_alarm;
extern int transistor_pin;
extern int buzzer_pin;
extern unsigned long milliseconds_till_alarm;

extern unsigned long curtain_lift_milliseconds;
extern unsigned long day_milliseconds;

extern alarm();
extern check_alarm(); // checks if it is time to run the alarm and does so if the time is right

#endif
