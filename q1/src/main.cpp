#include "main.h"
#include "constants.h"
#include "pros/screen.h"
#include "pros/screen.hpp"

/**
 * A callback function for screen touch.
 *
 * When this callback is fired, it will toggle text on the screen.
 */
void on_center_button(int16_t x, int16_t y) {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::screen::print(pros::E_TEXT_MEDIUM, 10, 70, "ahhh!");
	} else {
		pros::screen::print(pros::E_TEXT_MEDIUM, 10, 70, "");
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::screen::erase();
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
void autonomous() {}

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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({FRONT_LEFT_MOTOR, BACK_LEFT_MOTOR});   
	pros::MotorGroup right_mg({BACK_RIGHT_MOTOR, FRONT_RIGHT_MOTOR});

	while (true) {
		// Gets amount forward/backward from left joystick
		int power = master.get_analog(ANALOG_LEFT_Y) /2 ;    

		// Gets the steering amount from right joystick
		int turn = master.get_analog(ANALOG_RIGHT_X) /2 ;  
		pros::screen::print(pros::E_TEXT_LARGE, 10, 10, "power: %d, turn: %d", power, turn); 

		int leftVolage = power + turn;
		int rightVolage = power - turn;

		left_mg.move(leftVolage); 
		right_mg.move(rightVolage);                     
		
		pros::screen::print(pros::E_TEXT_LARGE, 10, 40, "left.motor volt: %d", leftVolage); 
		pros::screen::print(pros::E_TEXT_LARGE, 10, 70, "right.motor volt: %d", rightVolage); 
		pros::delay(20);      
		pros::screen::erase();		                         
	}
}