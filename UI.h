#ifndef UI_H
#define UI_H
#include "Arduino.h"
#include "clock.h"
#include "alarm.h"
#include "display.h"
#include "curtain_driver.h"

extern int mode;
extern int mode_LED;

extern int wakeup_time[4]; // this is the time the alarm should sound (in the form of an array)
extern int editing_digit; // this is the digit that is edited. Choose next digit with next_digit() and add one to it with add_one()

extern bool is_pressed(int pin, int previous_value);

extern void next_digit();
extern void add_one();
extern void change_mode();

// 4 functions for the 4 modes of the alarm
extern void display_on();
extern void display_off();
extern void change_current_time();
extern void change_alarm_time();


#endif
