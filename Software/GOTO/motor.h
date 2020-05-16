#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "AccelStepper.h"

/*
 * Inline function to calculate the number of stepper motor steps for one full rotation.
 * <param name="motorsteps360">Number of steps for 1 motor rotation (aka 360 divided by step angle).</param>
 * <param name="microstepfactor">The number of microsteps for one normal motor step.</param>
 * <param name="gearratio">The gear ratio between stepper motor and worm wheel (aka number of turns the stepper motor needs to do to do 1 worm rotation).</param>
 * <param name="wormspeed">The number of turns the worm wheel does for 1 full telescope rotation.</param>
 */
static inline unsigned int calcStepsFor360(unsigned int motorsteps360, unsigned int microstepfactor, unsigned int gearratio, unsigned int wormspeed){ 
  unsigned int result = 1;
  result = motorsteps360 * microstepfactor * gearratio * wormspeed;
  return result; 
}

class Motor
{
    int _pinstep, _pindir;
    unsigned int _stepsfor360;
    unsigned int _currentposition, _desiredposition;
    uint8_t _invertdirpin;
    float _currentangle, _desiredangle;
    AccelStepper * _motor;
   
  public:
    Motor(int, uint8_t, int, unsigned int);
    void calibratePosition(float);
    unsigned int getPosition();
    unsigned int getDesiredPosition();
    float getAngle();
    float getDesiredAngle();
    unsigned int setDesiredAngle(float);
    unsigned int setDesiredPosition(unsigned int);
    void stopMotion();
    void gotoDesired();
    
  private:
    int calcDistance(unsigned int);
    float calcAngleFromSteps(unsigned int);
    unsigned int calcStepsFromAngle(float);
};

 #endif /*MOTOR_H*/
