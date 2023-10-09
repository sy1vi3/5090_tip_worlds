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
#define imu_port 6
#define gl_port 5
#define clamp_port 3
#define clamp_rotator_port 2
#define pto_port 4
#define crstate 1
