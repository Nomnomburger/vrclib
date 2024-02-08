#include "../../include/main.h"

using namespace pros;

#ifndef AUTON_CONTROL
#define AUTON_CONTROL

/*
    only put declarations in this file
*/

extern double currentHeading;
extern float diameter;
extern void move(double left, double right);
extern float avgEncoder();
extern float prevEncoder;
extern float integral;
extern float PIDController(float error, float kp, float ki, float kd, float deltaTime, float minOutput, float maxOutput);
extern void moveSteering(float steering, float speed);
extern void goStraight(float distance, int power, int momentum = 5, float kp = 3, float ki = 0, float kd = 0.5, int minPower = 22, int decelZone = 8, float decelRate = 0.9, int timeOut = 999999);
extern void turn(double angle, int power, float steering = 100, double decelZone = 20, float decelRate = 0.8, double momentum = 0, int minPower =22);
extern void reset();
extern void a_init();

#endif
