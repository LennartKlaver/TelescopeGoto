/*
 * Used libraries:
 * - TinyGPS by Mikal Hart version 13.0.0
 */

/* INCLUDES */
#include "gps.h"

/* DEFINES */
//Pin associations.
#define NEO6MV2RX 19 
#define NEO6MV2TX 18

void initNEO6MV2(){
    Serial1.begin(9600);
}

uint8_t getGPS(float *flat, float *flong){
  TinyGPS gps;
  uint8_t result = false;
  unsigned long chars;
  unsigned short sentences, failed;
  
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (Serial1.available()) {
      char c = Serial1.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      // Did a new valid sentence come in?
      if (gps.encode(c)) {
        result = true;        
      }
    }
  }
  
  if (result){
    unsigned long age;
    gps.f_get_position(flat, flong, &age);
    debugGPSResultPrint(*flat, *flong, gps.satellites(), gps.hdop());
  }
  
  gps.stats(&chars, &sentences, &failed);
  debugGPSPrint(chars, sentences, failed);
  
  return result;
}

void debugGPSResultPrint(float flat, float flong, unsigned int sat, unsigned int hd){
  Serial.print("LAT=");
  Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Serial.print(" LON=");
  Serial.print(flong == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flong, 6);
  Serial.print(" SAT=");
  Serial.print(sat == TinyGPS::GPS_INVALID_SATELLITES ? 0 : sat);
  Serial.print(" PREC=");
  Serial.print(hd == TinyGPS::GPS_INVALID_HDOP ? 0 : hd);
}

void debugGPSPrint(unsigned long chars, unsigned short sentences, unsigned short failed){
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");  
}


 
