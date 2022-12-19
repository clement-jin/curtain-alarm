#ifndef CLOCK_H
#define CLOCK_H
#include "Arduino.h"
#include "display.h"
#include "UI.h"

void update_clock(bool show_display);
void increment_clock(bool show_display);
void print_display_digits();
void print_wakeup_time();
void print_array(int arr[]);
extern int time_mode;
extern int display_digits[4];


#endif
