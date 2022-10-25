#ifndef CLOCK_H
#define CLOCK_H
#include "Arduino.h"
#include "display.h"
#include "UI.h"

void update_clock();
void increment_clock();
void print_display_digits();
void print_wakeup_time();
void print_array(int arr[]);
extern int time_mode;
extern int display_digits[4];
extern bool show_display;

#endif
