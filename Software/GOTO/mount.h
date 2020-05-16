#ifndef MOUNT_H
#define MOUNT_H

/* Includes */
#include <Arduino.h>
#include "motor.h"
#include "AstroLib.h"

/* Prototypes */
class Mount
{
  Motor _motorra;
  Motor _motordec;
  public:
    Mount();
    void enableTracking();
    void stopMotion();
    void coordinateWithinReach(float, float);
    void slewToCoordinates(float, float);
      
};


#endif /*MOUNT_H*/
