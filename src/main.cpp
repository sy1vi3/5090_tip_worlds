#include "main.h"
#include "motors.h"

void initialize() {
	r1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	r2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	r3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	l1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	l2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	l3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	llift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rlift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	initAuton();
	/// left/right goals need 800,700 parameter and middle needs 1100,900
	goalRush(1100, 900);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void drive() {
	if (abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 10) {
		l1.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		l2.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		l3.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
	}
	else {
		l1.move_velocity(0);
		l2.move_velocity(0);
		l3.move_velocity(0);
	}

	if (abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 10) {
		r1.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
		r2.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
		r3.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
	}
	else {
		r1.move_velocity(0);
		r2.move_velocity(0);
		r3.move_velocity(0);
	}

	if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
		if (brakeMode) {
			brakeMode = false;
			r1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			r2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			r3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			l1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			l2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			l3.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		}
		else {
			brakeMode = true;
			r1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			r2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			r3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			l1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			l2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			l3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
	}
}

void lift() {
	if (abs(partner.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y))>10 || abs(partner.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 10) {
		llift.move(partner.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		rlift.move(-partner.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
	}
	else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		liftBrakeMode = false;
		llift.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		rlift.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		llift.move_velocity(0);
		rlift.move_velocity(0);
	}
	else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		if (!liftBrakeMode) {
			liftBrakeMode = true;

			llift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rlift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		llift.move(127);
		rlift.move(-127);
	}
	else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		if (!liftBrakeMode) {
			liftBrakeMode = true;

			llift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rlift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		llift.move(-127);
		rlift.move(127);
	}
	else {
		llift.move_velocity(0);
		rlift.move_velocity(0);
	}

}

void opcontrol() {
	backClaw.set_value(false);
	rotator.set_value(true);
	frontClaw.set_value(true);
	pto.set_value(true);
	while (true) {
		drive();
		lift();
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			frontClampState = !frontClampState;
			frontClaw.set_value(frontClampState);
		}
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			if (backClampState==0) {
				backClampState = 1;
				backClaw.set_value(false);
				rotator.set_value(false);
			}
			else if (backClampState == 1) {
				backClampState = 2;
				backClaw.set_value(true);
				rotator.set_value(false);
			}
			else if (backClampState == 2) {
				backClampState = 0;

				backClaw.set_value(false);
				rotator.set_value(true);
			}
		}

		pros::delay(20);
	}
}
