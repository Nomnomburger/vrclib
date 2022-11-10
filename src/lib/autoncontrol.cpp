#include "../include/main.h"
#include "../globals/globals.hpp"
#include "autoncontrol.hpp"

/* VARIABLES */
float circumference = 4 * 3.14; // 4 inch diameter wheels
double currentHeading = 0; 

/* BASIC FUNCTIONS */

//4 Motor Drivetrain (X-Drive, 4 motor inline)
//Comment out this section to use the 6 motor drivetrain variant

/* Default move command to save programmers some time writing movement for all motors.
 - int left:  Left motor power.
 - int right: Right motor power. */
void move(double left, double right)
{
	left_back=left;
	left_front=left;
	right_back=right;
	right_front=right;
}

//6 Motor Drivetrain (6 motor inline)
//Uncomment section below to use
/*
void move(double left, double right)
{
	left_back=left;
	left_mid = left;
	left_front=left;
	right_back=right;
	right_mid=right;
	right_front=right;
}
*/

float avgEncoder()
{
    float avg = (left_front.get_position() + left_back.get_position() + right_back.get_position() + right_front.get_position()) / 4;    
    return (avg);
}

float previousError = 0;
float integral = 0;


float PIDController(float error, float kp, float ki, float kd, float deltaTime, float minOutput, float maxOutput)
{
  float tmpIntegral = 0;
  float derivative;
  float input = 0;
  float output = 0;

  tmpIntegral = integral + error * deltaTime;
  derivative = (error - previousError) / deltaTime;
  input = kp * error + ki * tmpIntegral + kd * derivative;
  output = input;
  previousError = error;
  // Clamp steering output to -50 to 50
  if (input < minOutput) output = minOutput;
  if (input > maxOutput) output = maxOutput;

  // Clamp integrator when steering is saturating and integral is still at the same direction as error
  if (input != output && sgn(error) == sgn(input))
  {
      output = kp * error + kd * derivative;
      if (output < minOutput) output = minOutput;
      if (output > maxOutput) output = maxOutput;
  }
  else
  integral = tmpIntegral;

  //writeDebugStreamLine("Error: %f, Integral %f, Derivative: %f, Input: %f, Output: %f", error, integral, derivative, input, output);
    return output;
}

/* Implements move steering from EV3, with positive steering value being a right turn. This is the basis for all our autonomous code, as it is an efficient way to tell the robot how to move and to course-correct it when it is out of line.
 - int steering: Steering value, where 0 steering is going straight, 50 steering is a one wheel turn, 100 steering is an 0on-spot turn, and anything in between is a two-wheeled turn.
 - int speed:    Power value. Determines how fast the robot moves.  */
void moveSteering (float steering, float speed)
{
  if (steering < 0) { //left
    move(((50 + steering)/50)*speed, speed);
  }
  else { //right
    move(speed, ((50 - steering)/50)*speed);
  }
}

/* Go Straight with Gyro control, distance calculation and deceleration. The routine is broken up into 2 parts, power control and heading control. Power control is done by setting a "decelZone" which is the zone at which the robot is decelerating. Within the zone, the power is continuously multiplied by a variable which controls the rate at which the robot decelerates. For heading control, the robot attempt to maintain the heading that it starts with. This is achieved by calling a global variable, "currentHeading", which is updated every time it turns.
 - `float distance`:    The distance that the robot moves in centimeters.
 - `int power`:         The maximum power that the robot moves at. this power is maintained while the robot is cruising, and decreases when the robot decelerates.
 - `float kp`:          The rate at which the robot tries to corrent its heading. The higher the kp, the faster the robot turns to correct the heading. If this value is too low, the robot takes too long to correct its heading, which results in the robot going off course. If this value is too high, the robot will overshoot, when it corrects itself, causing the whole robot to shake.
 - `int minPower`:      The minimum power that the robot will decelerate to.
 - `int decelZone`:     The zone in which the robot starts decelerating.
 - `float decelRate`:   The rate at which the robot decelerates. */
void goStraight(float distance, int power, int momentum, float kp, float ki, float kd, int minPower, int decelZone, float decelRate, int timeOut)
{
    int sTime = pros::millis();
    right_front.tare_position();
    right_back.tare_position();
    left_front.tare_position();
    left_back.tare_position();
    //encoder.reset();
    //pros::lcd::print(3, "enc: %d", avgEncoder());


    int prevEncoder = 0;
    int curEncoder = avgEncoder();
    float currentPower = sgn(power) * 10;
    float startHeading = currentHeading*1.05;
    float distanceInDeg = 360 * (distance / circumference);
    float decelInDeg = 360 * (decelZone / circumference);

    while(abs(curEncoder) < distanceInDeg - momentum && pros::millis() - sTime < timeOut)
    {
       int remainDistance = distanceInDeg - abs(curEncoder);
       //pros::lcd::print(2, "decel: no");

       if (remainDistance < decelInDeg)
       {
           // Deceleration
           currentPower = (float)currentPower * (1 - decelRate);
           currentPower = std::abs(currentPower) > minPower ? currentPower : sgn(power) * minPower;
           //pros::lcd::print(2, "decel: yes");
       }
       else
       {
           currentPower = currentPower * 1.2;
           if (std::abs(currentPower) > abs(power))
             currentPower = power;
       }
       //if you don't decelerate, this plays to go straight normally
       float error = startHeading - inertial.get_rotation()*1.05;

       float output = PIDController(error, kp*sgn(power), ki, kd, 20, -100, 100);
       moveSteering(output, currentPower);
       prevEncoder = curEncoder;
       delay(20);
       //std::cout << output;
       master.print(1, 0, "output: %f", distanceInDeg);
       curEncoder = avgEncoder();
       pros::lcd::print(0, "imu: %f", inertial.get_rotation());
       //master.print(1, 0, "imu: %f", inertial.get_rotation());
       pros::lcd::print(1, "output: %f", output);
       pros::lcd::print(2, "pow: %f", currentPower);
       //pros::lcd::print(4, "tilt: %d", tilter.get_position());
    }
    move(0,0);
}

/* Turn using V5 Inertial Sensor including exponential decay
 - `double angle`:      Relative angle to turn
 - `int power`:         Power used when not decelerating
 - `int steering`:      Steering value for turning. Same as EV3 turn, where 50 and -50 steering signify a one wheel turn, and 100 and -100 signify a two wheel turn.
 - `double decelZone`:  Zone in which the robot is decelerating.
 - `double momentum`:   A small value which is subtracted from the angle when turning to account for some overshoot.
 - `int minPower`:      the minimum */

void turn(double angle, int power, float steering, double decelZone, float decelRate, double momentum, int minPower)
{
    // if gyro is below target, go left, otherwise, go right/run else

    double targetHeading = currentHeading + angle;
    currentHeading = targetHeading;

    float currentPower = (float)power;
    double deltaDegrees = targetHeading - inertial.get_rotation()*1.05;
    int direction = sgn(deltaDegrees);

    pros::lcd::print(2, "targetHeading: %f", targetHeading);
    pros::lcd::print(3, "direction: %d", direction);

    steering = std::abs(steering) * direction;
    while(deltaDegrees * direction - std::abs(momentum) > 0)
    {
        //pros::lcd::print(1, "turn 1");

        pros::lcd::print(4, "imu: %f", inertial.get_rotation());
        pros::lcd::print(5, "delta: %f", deltaDegrees);
        if(std::abs(deltaDegrees) >= decelZone)
        {
            //pros::lcd::print(1, "turn NO DECEL");
        }
        else
        {
            //pros::lcd::print(1, "turn DECEL");
            currentPower = (float)currentPower * (1 - decelRate);
            currentPower = std::abs(currentPower) > minPower ? currentPower : sgn(power) * minPower;
        }
        //pros::lcd::print(5, "power: %d", currentPower);
        moveSteering(steering, currentPower);
        deltaDegrees = targetHeading - inertial.get_rotation()*1.05;
        delay(20);
    }
    moveSteering(steering, 0);
}


void reset()
{
    currentHeading = inertial.get_rotation();
}

void a_init()
{
  currentHeading = 0;
  // auton init starts
  left_back.set_encoder_units(E_MOTOR_ENCODER_DEGREES); // set encoder units of drive to degrees for distance tracking
  left_front.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
  right_back.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
  right_front.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
  lift.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
	indexer.set_encoder_units(E_MOTOR_ENCODER_DEGREES);

  left_back.set_brake_mode(E_MOTOR_BRAKE_BRAKE); // set drive to brake
  left_front.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  right_back.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  right_front.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

  lift.tare_position();
	indexer.tare_position();
	left_front.tare_position();
	left_mid.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_mid.tare_position();
	right_back.tare_position();
  // auton init ends
}