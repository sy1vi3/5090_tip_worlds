#include "main.h"
#include "motors.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
pros::Motor r1(3);
pros::Motor r2(2);
pros::Motor r3(1);
pros::Motor l1(13);
pros::Motor l2(12);
pros::Motor l3(11);
pros::Motor rlift(17);
pros::Motor llift(9);
pros::Imu InertialSensor(4);

pros::ADIMotor red(8);
pros::ADIMotor green(7);
pros::ADIMotor blue(6);

pros::ADIDigitalOut frontClaw(5, true);
pros::ADIDigitalOut backClaw(2, false);
pros::ADIDigitalOut rotator(3, true);
pros::ADIDigitalOut pto(4, true);

int backClampState = 0;
bool frontClampState = true;
bool brakeMode = false;
bool liftBrakeMode = true;
bool ptoMode = true;
int intakeState = 0;

void lights(int _red, int _green, int _blue) {
    red.set_value(_red / 2);
    green.set_value(_green / 2);
    blue.set_value(_blue / 2);
}

