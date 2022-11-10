#include "main.h"
#include "selection.h"
#include "globals/globals.hpp"
#include "route/route.hpp"


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	inertial.reset();
	selectorInit();
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
void competition_initialize() {
	inertial.reset();
	selectorInit();
}

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

  switch (autonSelection)
	{
		case RED_1:
			// Auton function here
			break;
		case BLUE_1:
			// Auton function here
			break;

		case RED_2:
      // Auton function here
			break;
		case BLUE_2:
      // Auton function here
			break;
			
		case RED_3:
      // Auton function here
			break;
		case BLUE_3:
      // Auton function here
			break;
			
		case RED_4:
      // Auton function here
			break;
		case BLUE_4:
      // Auton function here
			break;
			
		case RED_5:
      // Auton function here
			break;
		case BLUE_5:
      // Auton function here
			break;
			
		case SKILLS:
			// Skills function here
			break;
	}

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

