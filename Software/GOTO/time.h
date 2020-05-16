#ifndef TIME_H
#define TIME_H

/* Includes */
#include <Arduino.h>
#include <Wire.h>
#include <ds3231.h>

 /* Prototypes */
void initDS3231();
void getTime(ts *t);
void setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds, uint8_t isdst);
void debugTimePrint(ts *t);

 #endif /*TIME_H*/
