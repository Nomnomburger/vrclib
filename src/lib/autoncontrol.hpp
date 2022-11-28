#include "../../include/main.h"

using namespace pros;

#ifndef AUTON_CONTROL
#define AUTON_CONTROL

/*
    only put declarations in this file
*/

extern double currentHeading;
extern float diameter;
void move(int left, int right);
float avgEncoder();
extern float prevEncoder;
extern float integral;
float PIDController(float error, float kp, float ki, float kd, float deltaTime, float minOutput, float maxOutput);
void moveSteering(float steering, float speed);
void goStraight(float distance, int power, int momentum = 0, float kp = 5, float ki = 0, float kd = 0.5, int minPower = 30, int decelZone = 5, float decelRate = 0.8, int timeOut = 999999);
void turn(double angle, int power, float steering = 100, double decelZone = 40, float decelRate = 0.8, double momentum =6, int minPower =33);
void reset();
void a_init();

#endif // AUTON_CONTROL
