#include "../include/main.h"
#include "globals/globals.hpp"
#include "lib/autoncontrol.hpp"
#include "lib/robotcontrol.hpp"

void opcontrol() {
	int lift_state = 0;
	int front_goal_grabber_state = 0;
	int back_goal_grabber_state = 0;
	int intake_state = 0;
	while(true)
	{
		lift.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		left_mid.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		right_mid.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

		int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = power + turn;
		int right = power - turn; // This reverses the right motor
		move(left, right);
		//input.append( "m");
		//input.append(std::to_string(left));
		//input.append(std::to_string(right));
		//input.append(".");


		if(master.get_digital_new_press(DIGITAL_L2))
		{
			 front_goal_grappler.set_value(1);
		}
		else if (master.get_digital_new_press(DIGITAL_L1))
		{
			front_goal_grappler.set_value(0);
		}
		if(master.get_digital(DIGITAL_R2))
		{
			if (lift_state < 2)
			{
			lift_state = 2;
		}
		}
		else if(master.get_digital(DIGITAL_R1))
		{
			if (lift_state > 0)
			{
			lift_state = 0;
		}
		}
		else
		{
			lift_state = 1;
		}
		if(master.get_digital_new_press(DIGITAL_LEFT))

		{
					intake_state = 0;
		}
		if(master.get_digital_new_press(DIGITAL_Y))
		{
			back_goal_grappler.set_value(0);
		}
		if(master.get_digital_new_press(DIGITAL_B))
		{
			back_goal_grappler.set_value(1);
		}
		if(master.get_digital_new_press(DIGITAL_DOWN))
		{
			if (intake_state > -1)
			{
				intake_state = -1;
			}
		}
		if(master.get_digital_new_press(DIGITAL_UP))
		{
			if (intake_state < 1)
			{
				intake_state = 1;
			}
		}
		if(master.get_digital_new_press(DIGITAL_RIGHT))
		{
left_back = MOTOR_BRAKE_HOLD;
right_back = MOTOR_BRAKE_HOLD;
right_mid = MOTOR_BRAKE_HOLD;
left_mid = MOTOR_BRAKE_HOLD;
left_front = MOTOR_BRAKE_HOLD;
left_front = MOTOR_BRAKE_HOLD;
		}



		switch(lift_state)
		{
			case 0:
			lift = -127;
			break;
			case 1:
			lift = MOTOR_BRAKE_HOLD;
			break;
			case 2:
			lift = 127;
			break;
		}

		switch(back_goal_grabber_state)
		{
		case 0:
			break;
		case 1:
			break;
		}

		switch(front_goal_grabber_state)
		{
			case 0:
			break;
			case 1:
			break;
		}

		switch(intake_state)
		{
			case -1:
			indexer = -127;
			break;
			case 0:
			indexer = 0;
			break;
			case 1:
			indexer = 127;
			break;
		}
	//double pastTime = currentTime();
	//input.append("break ");
	//input.append(std::to_string(currentTime()));
	// if (master.get_digital_new_press(DIGITAL_UP))
	// {
	// 	running = false;
	// }
	}
	pros::delay(200);
	// ofs.open(filename, std::ofstream::out | std::ofstream::app);
	// ofs << input << std::endl;
}