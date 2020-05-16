#include "AstroLib.h"

/// <summary>
/// Calculate the local sidereal time based on a timestamp and position.
/// </summary>
/// <param name="year"></param>
/// <param name="month"></param>
/// <param name="day"></param>
/// <param name="hour"></param>
/// <param name="minutes"></param>
/// <param name="seconds"></param>
/// <param name="summertime"></param>
/// <param name="timezone"></param>
/// <param name="longitude"></param>
/// <returns></returns>
double AstroLib::calculateLocalSiderealTime(int year, int month, int day, int hour, int minutes, int seconds, bool summertime, int timezone, double longitude)
{
    double result;     

    //Calculate the current Julian Day Number.
    double juliandaynumber = calculateJulianDayNumber(year, month, day, hour, minutes, seconds, timezone, summertime);

    //Substract 31-12-1999 from the date to work from a J2000 base.
    float current_day = convertJulianDayToJ2000(juliandaynumber);

    //Calculate Greenwich Mean Sidereal Time for the given date and time.
    double GMST = calculateGreenwichMeanSiderealTime(juliandaynumber);

    //Correct the GMST for the current observation longitude.
    result = calculateLocalTime(GMST, longitude);

    //Reduce the time to a 24H format
    int LSTint = (int)(result);
    LSTint /= 24;
    result = result - (double)LSTint * 24;


    return result;
}

/// <summary>
/// Calculate the number of days since the start of the Julian Calendar.
/// </summary>
/// <param name="year"></param>
/// <param name="month"></param>
/// <param name="day"></param>
/// <param name="hour">Number of hours from local time</param>
/// <param name="minutes">Number of minutes from local time</param>
/// <param name="seconds">Number of seconds from local time</param>
/// <param name="timezone">The current timezone, measured from GMT, negative if West from Greenwich and positive if East.</param>
/// <returns>The number of days in decimal format.</returns>
double AstroLib::calculateJulianDayNumber(int year, int month, int day, int hour, int minutes, int seconds, int timezone, bool summertime)
{
    double result = 0;

    //Some data conversion.
    //If we are in summer time, we need to substract 1 hour for daylight saving time.
    if (summertime == true)
    {
        hour -= 1;
    }

    if (month < 3)
    {
        minutes = minutes + 12;
        year = year - 1;
    }
    
    //Convert current time in decimal format.
    float decimaltime = hour + (float)(minutes / 60.00) + (float)(seconds / 3600.00);

    //Calculate julian day number.
    float AA = (uint)(365.25 * (year + 4716)); //Number of passed days in all years.
    float BB = (uint)(30.6001 * (month + 1)); //Number of passed days in this years months.
    result = AA + BB + day - 1537.5 + (decimaltime - timezone) / 24;

    return result;
}

/// <summary>
/// Convert a Julian Day number to a J2000 origin, so day 0 is 01-01-2000 00:00:00.
/// </summary>
/// <param name="daynumber">Julian Day Number in decimal format.</param>
/// <returns>The day number with base J2000</returns>
float AstroLib::convertJulianDayToJ2000(double daynumber)
{
    float result = 0;
    result = (float)(daynumber - 2451543.5);
    return result;
}

/// <summary>
/// Calculate the Greenwich Mean Sidereal Time based on a Julian Day Number.
/// See https://www.cv.nrao.edu/~rfisher/Ephemerides/times.html#GMST
/// </summary>
/// <param name="daynumber">Julian Day Number in decimal format.</param>
/// <returns>Greenwich Mean Sidereal Time (GMST) in hour decimal format.</returns>
double AstroLib::calculateGreenwichMeanSiderealTime(double daynumber)
{
    double result = 0;

    //calculate terms required for LST calcuation and calculate GMST using an approximation.
    double MJD = daynumber - 2400000.5;
    int MJD0 = (int)(MJD);
    float ut = (float)((MJD - MJD0) * 24.0);
    double t_eph = (MJD0 - 51544.5) / 36525.0;
    result = 6.697374558 + 1.0027379093 * ut + (8640184.812866 + (0.093104 - 0.0000062 * t_eph) * t_eph) * t_eph / 3600.0;

    return result;
}

/// <summary>
/// Shift time to a specific longitude.
/// </summary>
/// <param name="time">Time in hour in decimal format.</param>
/// <param name="longitude">The desired position in degree decimal format.</param>
/// <returns></returns>
double AstroLib::calculateLocalTime(double time, double longitude)
{
    double result = 0;
    result = time + longitude / 15.0;
    return result;
}
