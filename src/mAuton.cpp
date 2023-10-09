#include "main.h"
#include "motors.h"
int MAX_VEL = 200;

// l1.move_velocity(-50);
// l2.move_velocity(50);
// l3.move_velocity(-50);
// r1.move_velocity(50);
// r2.move_velocity(50);
// r3.move_velocity(-50);

void initAuton() {
  backClaw.set_value(false);
  rotator.set_value(false);
  frontClaw.set_value(true);
  pto.set_value(true);
}


void stopDriveMotors() {
  l1.move_velocity(0);
  l2.move_velocity(0);
  l3.move_velocity(0);
  r1.move_velocity(0);
  r2.move_velocity(0);
  r3.move_velocity(0);
  pros::delay(10);
}

void moveForward(int spd, int runDel, int endDel) {
  l1.move_velocity(-spd);
  l2.move_velocity(-spd);
  l3.move_velocity(-spd);
  r1.move_velocity(spd);
  r2.move_velocity(spd);
  r3.move_velocity(spd);
  pros::delay(runDel);
  stopDriveMotors();
  pros::delay(endDel);
}
void moveBackward(int spd, int runDel, int endDel) {
  l1.move_velocity(spd);
  l2.move_velocity(spd);
  l3.move_velocity(spd);
  r1.move_velocity(-spd);
  r2.move_velocity(-spd);
  r3.move_velocity(-spd);
  pros::delay(runDel);
  stopDriveMotors();
  pros::delay(endDel);
}
void turnDir(int spd) {
  l1.move_velocity(spd);
  l2.move_velocity(-spd);
  l3.move_velocity(spd);
  r1.move_velocity(spd);
  r2.move_velocity(spd);
  r3.move_velocity(-spd);
  pros::delay(1);
}

// (+ is clockwise)
void turnRobot(int ang, int spd, int endDel) {
  int curPos,difPos,difPosU;

  curPos = (InertialSensor.get_rotation());
  printf("first pos:%d\n",curPos);
  difPosU = (ang - curPos);
  if(curPos >= 180){
    curPos -= 360;
  }
  difPos = (ang - curPos);

  if((ang >= 0) && (curPos >= 0) && (difPos >= 0)) { // 1
    while ((InertialSensor.get_rotation()) < ang) {
      turnDir(spd);
      // printf("current pos:%f\n", -(InertialSensor.get_rotation()));
      // pros::delay(1);
    }
  }
  else if((ang >= 0) && (curPos >= 0) && (difPos < 0)) { // 2
    while ((InertialSensor.get_rotation()) > ang) {
      turnDir(-spd);
    }
  }
  else if((ang >= 0) && (curPos < 0) && (difPos >= 0)) { // 3
    if(difPosU < 0){
      while ((InertialSensor.get_rotation()) > ang) {
        turnDir(-spd);
      }
    }
    else {
      while ((InertialSensor.get_rotation()) < ang) {
        turnDir(spd);
      }
    }
    }
  else if((ang < 0) && (curPos >= 0) && (difPos < 0)) { // 4
        while ((InertialSensor.get_rotation()) > ang) {
          turnDir(-spd);
        }
      }
  else if((ang < 0) && (curPos < 0) && (difPos >= 0)) { // 5
        while ((InertialSensor.get_rotation()) < ang) {
          turnDir(spd);
        }
      }
  else if((ang < 0) && (curPos < 0) && (difPos < 0)) { // 6
        while ((InertialSensor.get_rotation()) > ang) {
          turnDir(-spd);
        }
      }
  else if((ang >= 0)  && (curPos < 0) && (difPosU < 0)) { // 7
        pros::delay(1000);
        while ((InertialSensor.get_rotation()) > ang) {
          turnDir(-spd);
        }
      }
  stopDriveMotors();
  pros::delay(endDel);
}

void liftUp(int spd, int del) {
  llift.move_velocity(spd);
  rlift.move_velocity(-spd);
  pros::delay(del);
  llift.move_velocity(0);
  rlift.move_velocity(0);
}

void liftDown(int spd, int del) {
  llift.move_velocity(-spd);
  rlift.move_velocity(spd);
  pros::delay(del);
  llift.move_velocity(0);
  rlift.move_velocity(0);
}



void frontClawUp() {
  frontClaw.set_value(true);
}

void frontClawDown() {
  frontClaw.set_value(false);
}

void backClawUp() {
  backClaw.set_value(true);
}

void backClawDown() {
  backClaw.set_value(false);
}

void rotatorOn() {
  rotator.set_value(true);
}

void rotatorOff() {
  rotator.set_value(false);
}

void ptOn() {
  pto.set_value(true);
  ptoMode = true;
}

void ptOff() {
  pto.set_value(false);
  ptoMode = false;
}

//---------------------------------------------------------------------
// main code
//---------------------------------------------------------------------

void matchAuton() {
  moveForward(70, 1100, 20); //move straight: speed, duration, end delay
  turnRobot(90, 25, 50); // angle,speed,delay
  moveForward(100, 500, 1000); //move straight
  turnRobot(-90, 25, 50); // angle,speed,delay
  moveBackward(70, 1000, 20); //move backward
  // glFire();
  moveBackward(70, 500, 20);
}

void skillsAuton() {
  moveForward(100, 2800, 100);
  moveBackward(70, 2400, 20);
  turnRobot(-30, 20, 50);
  moveForward(100, 2000, 100);
  moveBackward(100, 1900, 20);
  turnRobot(-60, 20, 50);
  moveForward(100, 3500, 100);
  turnRobot(5, 20, 50);
  moveBackward(70, 3000, 20);
}

// void matchAutonElims() {
//   forkDown(100, 200);
//   moveForward(100, 1700, 200); //move straight: speed, duration, end delay
//   glFire();
//   forkUp(70, 100);
//   moveBackward(70, 2000, 20); //move backward
//   turnRobot(80, 20, 50); // angle,speed,delay
//   forkDown(70, 100);
//   glLoad();
//   pros::delay(100);
//   moveBackward(70, 400, 20);
//   turnRobot(-25, 20, 50);
//   moveForward(100, 1500, 100);
//   glFire();
//   forkUp(70, 100);
//   moveBackward(70, 2000, 20); //move backward
// }

/// left/right goals need 800,700 parameter and middle needs 1100,900
void goalRush(int sped, int backSped) {
    liftDown(200, 600);
    moveForward(200, sped, 500); //move straight: speed, duration, end delay
    frontClaw.set_value(false);//latches on to goal
    moveBackward(200, backSped, 10);
}

void leftMiddleMA() {
    liftDown(100, 500);
    moveForward(100, 1500, 10); //move straight: speed, duration, end delay
    frontClaw.set_value(false);//latches on to goal
    moveBackward(100, 1500, 10);
}

void rightMiddleMA() {
    liftDown(100, 500);
    moveForward(100, 1500, 10); //move straight: speed, duration, end delay
    frontClaw.set_value(false);//latches on to goal
    moveBackward(100, 1500, 10);
}
