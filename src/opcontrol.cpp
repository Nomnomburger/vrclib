#include "../include/main.h"
#include "globals/globals.hpp"
#include "lib/autoncontrol.hpp"
#include "lib/robotcontrol.hpp"

bool slow = false;

int joyMap[128] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
	20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
	20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
	40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
	40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 60, 62, 62, 63, 63, 64, 64, 65, 85,
	100,100,100,100,100,100,100,100,100,100,
	110,110,110,110,110,110,110,110,110,110,
	120,121,122,123,124,125,126,127,127,127,
	127,127,127,127,127,127,127,127
};

int capMotorPower(int power)
{
	int cappedPower = abs(power) > 126 ? 126 : abs(power);
	cappedPower = sgn(power) * cappedPower;
	return slow ? cappedPower * 0.7 : cappedPower;
}

int map(int joy)
{
	int j = abs(joy) > 126 ? 127: abs(joy);
	j = sgn(joy) * joyMap[j];

	return capMotorPower(j);
}

void opcontrol() {
	right_front.set_brake_mode(E_MOTOR_BRAKE_COAST);
	left_front.set_brake_mode(E_MOTOR_BRAKE_COAST);
	right_back.set_brake_mode(E_MOTOR_BRAKE_COAST);
	left_back.set_brake_mode(E_MOTOR_BRAKE_COAST);

	bool slow = false;

	// Variables for split-stick arcade control.
	int x;
	int y;
	int r;

	// Main drive loop
	while (true) {

		y = map(master.get_analog(ANALOG_LEFT_Y));
		x = map(master.get_analog(ANALOG_LEFT_X));
		r = map(master.get_analog(ANALOG_RIGHT_X));
		int fLeft = capMotorPower(y + x + r);
		int fRight = capMotorPower(y - x - r);
		int bLeft = capMotorPower(y - x + r);
		int bRight = capMotorPower(y + x - r);


		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
	 	  runIntake(127); //intake
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			runIntake(-127);
		}
		else {
			runIntake(0);

		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			index(127); //running the indexer will run both indexers
			//isIndexRun = true;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			index(-127);
			//isIndexRun = true;
		}
		else {
			index(0);
		}

		left_front = fLeft;
		right_front = fRight;
		left_back = bLeft;
		right_back = bRight;


		// Delay to avoid overloading the code

		pros::delay(20);
	}
}