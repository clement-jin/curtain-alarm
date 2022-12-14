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

void lift_curtain();
void ring_bell();
void wait_a_day();
void update_clock();

#endif
