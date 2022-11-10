#include "../../include/main.h"

using namespace pros;

#ifndef AUTON_CONTROL
#define AUTON_CONTROL

/*
    only put declarations in this file
*/

extern double currentHeading;
extern float diameter;
extern void move(int left, int right);
extern float avgEncoder();
extern float prevEncoder;
extern float integral;
extern float PIDController(float error, float kp, float ki, float kd, float deltaTime, float minOutput, float maxOutput);
extern void moveSteering(float steering, float speed);
extern void goStraight(float distance, int power, int momentum = 0, float kp = 5, float ki = 0, float kd = 0.5, int minPower = 30, int decelZone = 5, float decelRate = 0.8, int timeOut = 999999);
extern void turn(double angle, int power, float steering = 100, double decelZone = 40, float decelRate = 0.8, double momentum =6, int minPower =33);
extern void reset();
extern void a_init();

#endif
