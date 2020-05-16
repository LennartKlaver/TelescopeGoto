/*
 * Used libraries:
 * - DS3231FS by Petre Rodan version 1.1.1
 */

/* INCLUDES */
#include "time.h"

/* DEFINES */
//Pin associations.
#define DS3231SDA 20
#define DS3231SCL 21

void initDS3231(){
  //DS3231 init.
  Wire.begin(); //start i2c (required for connection)
  DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
}

void setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds, uint8_t isdst){
  ts t; //ts is a struct findable in ds3231.h
  t = {seconds, minutes, hour, day, month, year, 7, 0, isdst, 0};
  DS3231_set(t);
}

void getTime(ts *t){
  DS3231_get(t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
}

void debugTimePrint(ts *t){
  //DS3231_get() will use the pointer of t to directly change t value (faster, lower memory used)
  Serial.print("Day : ");
  Serial.print(t->mon); //just print some data
  Serial.print("/");
  Serial.print(t->mday);
  Serial.print("/");
  Serial.println(t->year);
  Serial.print("Hour : ");
  Serial.print(t->hour);
  Serial.print(":");
  Serial.print(t->min);
  Serial.print(".");
  Serial.println(t->sec);
  Serial.println();
}
