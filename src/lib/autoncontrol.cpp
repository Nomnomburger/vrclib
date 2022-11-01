#include "../include/main.h"
#include "../globals/globals.hpp"
#include "autoncontrol.hpp"

//house cleaning functions
int currentTime()
{
	//get time here, kinda useless but ok
	return pros::millis();
}
// lol
double rotation()
{
	double length;
	length = left_back.get_position()/360*3.1416*4*7/5;
	double width;
	width = right_back.get_position()/360*3.1416*4*7/5;
	return (length/2)+(width/2);
}



//movement functions basic
void move(double left, double right)
{
	left_back=left;
	left_mid = left;
	left_front=left;
	right_back=right;
	right_mid=right;
	right_front=right;
}


double gyro_value()
{
	//pros::delay(199);
	double getHeadingVal;
	//pros::delay(135);3
	getHeadingVal=inertial.get_heading();
	pros::delay(20);
	if (getHeadingVal > 180)
	{
		getHeadingVal = getHeadingVal - 360;
	}
	//pros::delay(135);
	return getHeadingVal;
	//<180 ,((-(getHeadingVal-180)) < 0);
}


double PID(vector* pCenter, double* pLastError)
{
	if (pCenter -> Turning == false){
		//time things
		unsigned int elapsedTime;
		static unsigned int previousTime = pros::millis();
		elapsedTime = 80;
		double turn = inertial.get_heading();
		if (turn > 180)
		{
			turn = turn - 360;
		}
		//change these to tune
		double Kp;
		double Ki;
		double Kd;
		Kp = 0.085;
		Ki = 0.08;
		Kd = 0.08;

		double errorRotation;
		double culmanativeErrorRotation;
		double rateErrorRotation;
		//PID alg
		errorRotation = pCenter -> rotation - turn;
		culmanativeErrorRotation += errorRotation * elapsedTime;
		rateErrorRotation = (errorRotation - *pLastError)/elapsedTime;
		double PIDoutput;
		PIDoutput = Kp * errorRotation + Ki * culmanativeErrorRotation + Kd * rateErrorRotation;
		*pLastError = errorRotation;

		//time
		previousTime = currentTime();

		return PIDoutput;
	}
	return 0;
}

double pLastError = 0;
//movement function advanced

void go_straight(double distance, double maxSpeed, vector* pCenter)
{
	double LastError;
	double segment = distance/3;
	double traveled = 0.0;
	double start = rotation();
	double speed = 40;
	double speedSeg = maxSpeed/segment;
	int i = 0;
	while (traveled < segment)
	{
		pros::delay(30);
		double error = PID(pCenter, &LastError);
		move(speed+error, speed-error);
		if (speed < maxSpeed)
		{
			i ++;
			double l = i*0.73;
			speed = speed + l;
		}
		traveled = rotation()-start;
	}

	while (traveled < (2*segment))
	{
				pros::delay(30);
		double error = PID(pCenter, &LastError);
		move(maxSpeed+error, maxSpeed-error);
		traveled = rotation()-start;
	}
  i = 0;
	while (traveled < distance)
	{
				pros::delay(30);
		double error = PID(pCenter, &LastError);
		move(speed+error, speed-error);
		i ++;
		double l = i*0.73;
		speed = speed - l;
		if (speed < 55)
		{
			speed = 55;
		}
		traveled = rotation()-start;
	}
	move(0, 0);
}


void back(double distance, double maxSpeed, vector* pCenter)
{
	double LastError;
	double segment = distance/3;
	double traveled = 0.0;

	double speed = -40;
	int i = 0;
	double start = rotation();
	while (traveled > segment)
	{
				pros::delay(30);
		double error = PID(pCenter, &LastError);
		move(speed+error, speed-error);
		if (speed > maxSpeed)
		{
			i ++;
			double l = i*0.53;
			speed = speed - l;
		}
		traveled = rotation()-start;
	}

	while (traveled > (2*segment))
	{
				pros::delay(30);
		double error = PID(pCenter, &LastError);
		move(maxSpeed+error, maxSpeed-error);
		traveled = rotation()-start;
	}
  i = 0;
	while (traveled > distance)
	{
				pros::delay(30);
		double error = PID(pCenter, &LastError);
		move(speed+error, speed-error);
		i ++;
		double l = i*0.53;
		speed = speed + l;
		if (speed > -40)
		{
			speed = -40;
		}
		traveled = rotation()-start;
	}
	move(0, 0);
}
void turn_forwards(int degrees, double radius, vector* pCenter) //(int velocityLeft, int velocityRight, int degrees)
{
	//double degres;
	//degres = degrees + pCenter->rotation;
	//inertial.reset();
	//distanceTravled = 0;
	//begin = rotation();

	double velocityLeft;
	//velocityLeft = 0.5*degrees;
	double velocityRight;
	//velocityRight = 0.5*degrees*-1;
	//double arcLength;
	/*
	arcLength = 4;
	if (radius == 0)
	{radius = 0.1;
	}
	*/
	int a = round(pCenter -> rotation + degrees);
	int c = a % 360;


	//double radius;
	//radius = 0.5 * ((velocityLeft + velocityRight)/(velocityRight-velocityLeft));
	//velocityLeft/velocityRight = radius+6/radius-6;
	if (radius == 0)
	{
		velocityLeft = 80;
		velocityRight = -80;
	}
	else
	{
		velocityLeft = 115*(1/2 + 4/radius);
		velocityRight = 115*(1/2 - 4/radius);
	}
	//arcLength = (2 * 3.141592 * radius * degrees / 360);

	//debugging things
	double gyro_val;
	gyro_val = 0;

	//pointer thing goes here
	//double lastErrorRotation = 0.0;
	if (c == 0)
	{
		move(0,0);
	}
	else
	{
		pCenter -> Turning = true;
		while((gyro_val < c-3) or (gyro_val > c+3))
		{

			//do things here
			//move(velocityLeft, velocityRight);
			gyro_val = gyro_value();
			pros::delay(10);

			//move(velocityLeft,velocityRight);

			// master.print(0, 0, "gyro_val: %d", gyro_val);
			// pros::lcd::print(2,  "gyro_val: %d", gyro_val);

			//pid here
			//double PIDcorrection;
			//center.rotation = gyro_val;

			//PIDcorrection = PIDturn(center, degrees, &lastErrorRotation);
			move(velocityLeft, velocityRight); // + PIDcorrection);
		}
		//pCenter->rotation = degres;
		move(0,0); //stop once heading is reached
	}

	move(MOTOR_BRAKE_HOLD,MOTOR_BRAKE_HOLD);
	pros::delay(100);
	pCenter -> Turning = false;
	pCenter -> rotation = inertial.get_heading();
	pros::delay(20);

	//return center;
}

void turn_backwards(int degrees, double radius, vector* pCenter) //(int velocityLeft, int velocityRight, int degrees)
{
	//double degres;
	//degres = degrees + pCenter->rotation;
	//inertial.reset();
	//distanceTravled = 0;
	//begin = rotation();

	double velocityLeft;
	//velocityLeft = 0.5*degrees;
	double velocityRight;
	//velocityRight = 0.5*degrees*-1;
	//double arcLength;
	/*
	arcLength = 4;
	if (radius == 0)
	{radius = 0.1;
	}
	*/
	int a = round(pCenter -> rotation + degrees);
	int c = a % 360;


	//double radius;
	//radius = 0.5 * ((velocityLeft + velocityRight)/(velocityRight-velocityLeft));
	//velocityLeft/velocityRight = radius+6/radius-6;
	if (radius == 0)
	{
		velocityLeft = 80;
		velocityRight = -80;
	}
	else
	{
		velocityLeft = -110*(1/2 + 4/radius);
		velocityRight = -110*(1/2 - 4/radius);
	}
	//arcLength = (2 * 3.141592 * radius * degrees / 360);

	//debugging things
	double gyro_val;
	gyro_val = 0;

	//pointer thing goes here
	//double lastErrorRotation = 0.0;
	if (c == 0)
	{
		move(0,0);
	}
	else
	{
		pCenter -> Turning = true;
		while((gyro_val < c-3) or (gyro_val > c+3))
		{

			//do things here
			//move(velocityLeft, velocityRight);
			gyro_val = gyro_value();
			pros::delay(10);

			//move(velocityLeft,velocityRight);

			// master.print(0, 0, "gyro_val: %d", gyro_val);
			// pros::lcd::print(2,  "gyro_val: %d", gyro_val);

			//pid here
			//double PIDcorrection;
			//center.rotation = gyro_val;

			//PIDcorrection = PIDturn(center, degrees, &lastErrorRotation);
			move(velocityLeft, velocityRight); // + PIDcorrection);
		}
		//pCenter->rotation = degres;
		move(0,0); //stop once heading is reached
	}

	move(MOTOR_BRAKE_HOLD,MOTOR_BRAKE_HOLD);
	pros::delay(100);
	pCenter -> Turning = false;
	pCenter -> rotation = inertial.get_heading();
	pros::delay(20);

	//return center;
}

void magic_wand()
{
	while(true)
	{
		master.rumble(".- .- .-");
		pros::delay(1);
	}
	master.rumble("");
}

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed; // pressed does not equal pressed?
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pres3sed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

vector center =
 {
	 .x = 0,
	 .y = 0,
	 .rotation = 0,
	 .Turning = false
 };