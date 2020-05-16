/*
 * Used libraries:
 * - AccelStepper by Mike McCauley version 1.59.0
 */

/* INCLUDES */
#include "motor.h"


/* DEFINES */
#define MAXSPEED 100
#define ACCELERATION 20

    /*int _pinstep, _pindir;
    unsigned int _stepsfor360;
    unsigned int _currentposition, _desiredposition;
    float _currentangle, _desiredangle;*/

/*
 * Constructor.
 */
Motor::Motor(int pindir, uint8_t invertdirpin, int pinstep, unsigned int stepsfor360) {
  _pindir = pindir;
  _pinstep = pinstep;
  _stepsfor360 = stepsfor360;
  _currentposition = 0;
  _currentangle = 0;
  _desiredposition = 0;
  _desiredangle = 0;
  _motor = new AccelStepper(AccelStepper::DRIVER, pinstep, pindir);
  _invertdirpin = invertdirpin;
  
  if(invertdirpin){
    _motor->setPinsInverted();
  }

  _motor->setMaxSpeed(MAXSPEED);
  _motor->setAcceleration(ACCELERATION);
  
  //_motor->enableOutputs();
}

void Motor::calibratePosition(float angle) {
    _currentangle = angle;
    _currentposition = calcStepsFromAngle(angle);
}

unsigned int Motor::getPosition(){
  return _currentposition;
}

unsigned int Motor::getDesiredPosition(){
  return _desiredposition;
}

float Motor::getAngle(){
  return _currentangle;
}

float Motor::getDesiredAngle(){
  return _desiredangle;  
}

unsigned int Motor::setDesiredAngle(float angle){

  //Limit the angle to 360 degrees.
  angle = fmod(angle, 360); //Modulo.
  
  _desiredangle = angle;
  _desiredposition = calcStepsFromAngle(angle);
}

unsigned int Motor::setDesiredPosition(unsigned int steps){

  //Limit steps to the number of steps for 360 degrees.
  steps = steps % _stepsfor360;
  
  _desiredangle = calcAngleFromSteps(steps);
  _desiredposition = steps;
}

void Motor::gotoDesired(){
  //TODO start motion.
}
   
void Motor::stopMotion(){
  //TODO stop motion.
  _motor->stop();
}

int Motor::calcDistance(unsigned int steps){
  int result = 0;
  unsigned int stepsModMax = 0;

  //Avoid a divide_by_0, better return 1.
  if(!_stepsfor360)
    return 1;

  //Limit the steps argument to the maximum number of steps.
  stepsModMax = steps % _stepsfor360; //Modulo.
  
  //Calculate the absolute distance.
  result = fmod((steps - _currentposition), _stepsfor360); //Distance in steps. Modulo.

  //Check if the distance is shorter if we move the other direction.
  if (result > (unsigned int)(_stepsfor360 / 2)){
    //It is shorter to change direction and move counter clockwise, return this distance but negative.
    result = -1 * (_stepsfor360 - result);
  }

  return result;
}

float Motor::calcAngleFromSteps(unsigned int steps){
  float result = 0;

  //Avoid a divide_by_0, better return 0.
  if(!_stepsfor360)
    return 0;

  //Scale steps to angles.
  result = (steps * 360) / _stepsfor360;
  
  return result;
}

unsigned int Motor::calcStepsFromAngle(float angle){
  unsigned int result = 0;

  //Avoid a divide_by_0, better return 0.
  if(!_stepsfor360)
    return 0;

  //Scale angles to steps and round the result (we cannot have decimal steps).
  result = (unsigned int)(angle * _stepsfor360) / 360;
  
  return result;
}
