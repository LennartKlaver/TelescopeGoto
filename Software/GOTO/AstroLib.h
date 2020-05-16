#ifndef ASTROLIB_H
#define ASTROLIB_H

#include "Arduino.h"

class AstroLib{
  public:
    static double calculateLocalSiderealTime(int year, int month, int day, int hour, int minutes, int seconds, bool summertime, int timezone, double longitude);
    static double calculateJulianDayNumber(int year, int month, int day, int hour, int minutes, int seconds, int timezone, bool summertime);
    static float convertJulianDayToJ2000(double daynumber);
    static double calculateGreenwichMeanSiderealTime(double daynumber);
    static double calculateLocalTime(double time, double longitude);
};

#endif /*ASTROLIB_H*/
