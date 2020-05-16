#include "time.h"
#include "gps.h"
#include "motor.h"
#include "AstroLib.h"

/* DEFINES */
//Pin assignments
#define PINDECDIR  2
#define PINDECSTEP 3
#define PINRADIR   4
#define PINRASTEP  5

//Telescope settings
//Right ascension motor.
#define RAMOTORSTEPS 400
#define RAMICROSTEPS 16
#define RAGEARRATIO 2
#define RAWORMRATIO 144
#define RAMOTORINVERTED 0
//Declination motor.
#define DECMOTORSTEPS 400
#define DECMICROSTEPS 16
#define DECGEARRATIO 2
#define DECWORMRATIO 144
#define DECMOTORINVERTED 0

Motor * motordec;
Motor * motorra;

void setup() {
  //Init DS3231 timer.
  initDS3231();
  setTime(2020, 05, 10, 20, 00, 00, true);

  //Init NEO6MV2
  initNEO6MV2();

  //Init DEC motor.
  //motordec = new Motor(PINDECDIR, DECMOTORINVERTED, PINDECSTEP, calcStepsFor360(DECMOTORSTEPS, DECMICROSTEPS, DECGEARRATIO, DECWORMRATIO));
  motorra = new Motor(PINRADIR, RAMOTORINVERTED, PINRASTEP, calcStepsFor360(RAMOTORSTEPS, RAMICROSTEPS, RAGEARRATIO, RAWORMRATIO));
 
  //Debug init.
  Serial.begin(9600);
}

void loop() {
  ts t;
  getTime(&t);
  debugTimePrint(&t); 

  delay(1000);


  float flat = 0;
  float flong = 0;
  getGPS(&flat, &flong);

  delay (10000);

}
