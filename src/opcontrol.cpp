#include "../include/main.h"
#include "globals/globals.hpp"
#include "lib/autoncontrol.hpp"
#include "lib/robotcontrol.hpp"
#include "pros/misc.h"

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

    ///*CHASSIS MOVEMENT*///

    /* Chassis Movement for X-Drive or Mecanum Drive */ //(Comment out if using methods below)
		y = map(master.get_analog(ANALOG_LEFT_Y));
		x = map(master.get_analog(ANALOG_LEFT_X));
		r = map(master.get_analog(ANALOG_RIGHT_X));
		int fLeft = capMotorPower(y + x + r);
		int fRight = capMotorPower(y - x - r);
		int bLeft = capMotorPower(y - x + r);
		int bRight = capMotorPower(y + x - r);

    /* Chassis Movement for 4 Wheel Inline Drive */ //(Uncomment this section if you are using a 4 wheel inline drive)
    /*
    y = map(master.get_analog(ANALOG_LEFT_Y));
    r = map(master.get_analog(ANALOG_RIGHT_X));
    int fLeft = capMotorPower(y + r);
		int fRight = capMotorPower(y - r);
		int bLeft = capMotorPower(y + r);
		int bRight = capMotorPower(y - r);
    */

    /* Chassis Movement for 6 Wheel Inline Drive */ //(Uncomment this section if you are using a 6 wheel inline drive)
    /*
    y = map(master.get_analog(ANALOG_LEFT_Y));
    r = map(master.get_analog(ANALOG_RIGHT_X));
    int fLeft = capMotorPower(y + r);
		int fRight = capMotorPower(y - r);
		int bLeft = capMotorPower(y + r);
		int bRight = capMotorPower(y - r);
    //Uncomment the last two lines in the Drive Motor Pairing section to use 6 wheel inline
    int mLeft = capMotorPower(y + r);
    int mRight = capMotorPower(y - r);
    */



    ///*SUBSYSTEM CONTROL*///

    //Intake Control
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
	 	  runIntake(127); //intake
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			runIntake(-127);
		}
		else {
			runIntake(0);

		}

    //Lift Control
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			lift = 127; //lift
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			lift = -127;
		}
		else {
			lift = 0;
		}

    //Indexer Control
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			index(127); //running the indexer will run both indexers
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			index(-127);
		}
		else {
			index(0);
		}

    //Pneumatics Control
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			 piston_1.set_value(1);
		}
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      piston_1.set_value(0);
    }



    ///*DRIVE MOTOR PAIRING*///

		left_front = fLeft;
		right_front = fRight;
		left_back = bLeft;
		right_back = bRight;
    /* //Uncomment this section if you are using a 6 wheel inline drive
    left_mid = mLeft;
    right_mid = mRight;
    */
    


		// Delay to avoid overloading the code
		pros::delay(20);
	}
}