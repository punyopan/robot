#include "src/Motor.h"

#define DirectionPin 4
#define BaudRate 115200


const float WHEEL_RADIUS  = 3.7;   
const float AXLE_WIDTH    = 19.4;
const float HALF_AXLE     = 9.7;   
const float CIRCLE_RADIUS = 20.0;  


const int RPM_DRIVE = 40;


unsigned long arcDelay(float arcRadius, float degree, float rpm) {
  if (rpm <= 0) return 0;
  float arcLen   = (degree / 360.0) * 2.0 * PI * arcRadius;   // cm
  float wheelSpd = rpm * 2.0 * PI * WHEEL_RADIUS;             // cm/min
  return (unsigned long)((arcLen / wheelSpd) * 60000.0);       // ms
}


void stopMotors() {
  Motor.turnWheel(1, LEFT,  0);
  Motor.turnWheel(1, RIGHT, 0);
  Motor.turnWheel(2, LEFT,  0);
  Motor.turnWheel(2, RIGHT, 0);
}


void goStraight(float distance) {
  Motor.turnWheel(1, LEFT,  RPM_DRIVE);   
  Motor.turnWheel(2, RIGHT, RPM_DRIVE);   
  float wheelSpd = RPM_DRIVE * 2.0 * PI * WHEEL_RADIUS;
  unsigned long t = (unsigned long)((distance / wheelSpd) * 60000.0);
  delay(t);
  stopMotors();
}

void goBackward(float distance) {
  Motor.turnWheel(1, RIGHT, RPM_DRIVE);   
  Motor.turnWheel(2, LEFT,  RPM_DRIVE);   
  float wheelSpd = RPM_DRIVE * 2.0 * PI * WHEEL_RADIUS;
  unsigned long t = (unsigned long)((distance / wheelSpd) * 60000.0);
  delay(t);
  stopMotors();
}


void spinRight(int degree) {
  Motor.turnWheel(1, LEFT,  RPM_DRIVE);  
  Motor.turnWheel(2, LEFT,  RPM_DRIVE);   
  delay(arcDelay(HALF_AXLE, (float)degree, (float)RPM_DRIVE));
  stopMotors();
}

void spinLeft(int degree) {
  Motor.turnWheel(1, RIGHT, RPM_DRIVE);  
  Motor.turnWheel(2, RIGHT, RPM_DRIVE);  
  delay(arcDelay(HALF_AXLE, (float)degree, (float)RPM_DRIVE));
  stopMotors();
}

void turnRight(int degree) {

  Motor.turnWheel(1, LEFT, RPM_DRIVE);
  delay(arcDelay(AXLE_WIDTH, (float)degree, (float)RPM_DRIVE));
  stopMotors();
}
void turnbackRight(int degree) {

  Motor.turnWheel(2, RIGHT, RPM_DRIVE);
  delay(arcDelay(AXLE_WIDTH, (float)degree, (float)RPM_DRIVE));
  stopMotors();
}

void turnLeft(int degree) {

  Motor.turnWheel(2, RIGHT, RPM_DRIVE);
  delay(arcDelay(AXLE_WIDTH, (float)degree, (float)RPM_DRIVE));
  stopMotors();
}


void circleRight(int degree) {
 
  float innerR = CIRCLE_RADIUS - HALF_AXLE;   // 10.3 cm
  float outerR = CIRCLE_RADIUS + HALF_AXLE;   // 29.7 cm

  float outerRPM = (float)RPM_DRIVE;
  float innerRPM = outerRPM * (innerR / outerR);

  Motor.turnWheel(1, LEFT,  (int)outerRPM);  
  Motor.turnWheel(2, RIGHT, (int)innerRPM);  

  float avgRPM = (outerRPM + innerRPM) / 2.0;
  delay(arcDelay(CIRCLE_RADIUS, (float)degree, avgRPM));
  stopMotors();
}

void circleLeft(int degree) {
 
  float innerR = CIRCLE_RADIUS - HALF_AXLE;
  float outerR = CIRCLE_RADIUS + HALF_AXLE;

  float outerRPM = (float)RPM_DRIVE;
  float innerRPM = outerRPM * (innerR / outerR);

  Motor.turnWheel(1, LEFT,  (int)innerRPM);   
  Motor.turnWheel(2, RIGHT, (int)outerRPM);    

  float avgRPM = (outerRPM + innerRPM) / 2.0;
  delay(arcDelay(CIRCLE_RADIUS, (float)degree, avgRPM));
  stopMotors();
}


void setup() {
  Serial.begin(115200);
  Motor.begin(BaudRate, DirectionPin, &Serial2);
  delay(5000);
  execute();
}

void loop() {
  
}
// ============================================================
void execute() {
 
  
  goStraight(60);         
  delay(1000);

  // turnbackRight(90);         
  // goBackward(60);
  // delay(2000);
  // goStraight(60);         
  // spinRight(90);

  // goStraight(30);
  // spinRight(90);
  // delay(1000);
  // spinLeft(90);
  // goBackward(30);

  // spinLeft(90);
  // goStraight(36.5);
  // spinRight(90);
  // circleRight(180);      
  // delay(1000);

  // goStraight(20.5);
  // spinLeft(70);
  // goStraight(40);

}