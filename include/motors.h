extern pros::Motor r1;
extern pros::Motor r2;
extern pros::Motor r3;
extern pros::Motor l1;
extern pros::Motor l2;
extern pros::Motor l3;
extern pros::Motor llift;
extern pros::Motor rlift;
extern pros::Controller master;
extern pros::Controller partner;
extern pros::Imu InertialSensor;

extern bool brakeMode;
extern bool liftBrakeMode;
extern int backClampState;
extern bool frontClampState;


extern pros::ADIDigitalOut frontClaw;
extern pros::ADIDigitalOut backClaw;
extern pros::ADIDigitalOut rotator;
extern pros::ADIDigitalOut pto;


#define left_1_port 13
#define right_1_port 3
#define left_2_port 12
#define right_2_port 2
#define left_3_port 11
#define right_3_port 1
#define left_lift_port 9
#define right_lift_port 17
#define imu_port 4
#define gl_port 5
#define clamp_port 3
#define clamp_rotator_port 2
#define pto_port 4
#define crstate 1

extern void initAuton();
extern void liftUp(int spd, int del);
extern void liftDown(int spd, int del);
extern void frontClawUp();
extern void frontClawDown();
extern void backClawUp();
extern void backClawDown();
extern void rotatorOn();
extern void rotatorOff();
extern void ptOn();
extern void ptOff();
extern void stopDriveMotors();
extern void moveBackward(int spd, int runDel, int endDel);
extern void turnDir(int spd);
extern void matchAuton();
extern void skillsAuton();
extern void goalRush(int sped, int backSped);
extern void leftMiddleMA();
extern void rightMiddleMA() ;















// #pragma once
// //extern int lds;
// //extern int rds;
// extern int page;
// extern int ap;
// extern int intake_state;
// extern int leftY;
// extern int rightY;
// extern int tank1act;
// extern int left_y_f;
// extern int right_y_f;
//
// extern pros::Motor l1;
// extern pros::Motor l2;
// extern pros::Motor l3;
// extern pros::Motor r1;
// extern pros::Motor r2;
// extern pros::Motor r3;
// extern pros::Motor fbar;
// extern pros::Motor intake;
// extern pros::Rotation liftencoder;
// extern pros::Controller master;
// extern pros::Controller partner;
//
// extern pros::ADIDigitalOut gl;
// extern pros::ADIDigitalOut clamp;
// extern pros::Imu InertialSensor;
// extern bool glstate;
// extern bool cstate;
// extern bool intake_on;
// extern bool intake_reversed;
// extern void goallift();
// extern void llemugui();
// extern void intakes();
// extern void leftdrive(int lds);
// extern void rightdrive(int rds);
// extern void drive();
// extern pros::ADIMotor red;
// extern pros::ADIMotor blue;
// extern pros::ADIMotor green;
// extern void matchAuton();
// extern void matchAutonElims();
// extern void skillsAuton();
// extern void matchAutonElimsLeft();
// extern void fbarUp(int spd, int del);
// extern void fbarDown(int spd, int del);
// extern void rings(int spd, int del);
// extern void inverseRings(int spd, int del);
