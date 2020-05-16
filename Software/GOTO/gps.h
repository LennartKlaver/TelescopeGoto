#ifndef GPS_H
#define GPS_H

/* Includes */
#include <Arduino.h>
#include <TinyGPS.h>

/* Prototypes */
void initNEO6MV2();
uint8_t getGPS(float *flat, float *flong);
void debugGPSResultPrint(float flat, float flong, unsigned int sat, unsigned int hd);
void debugGPSPrint(unsigned long chars, unsigned short sentences, unsigned short failed);

#endif /*GPS_H*/
