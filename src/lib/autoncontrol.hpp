#include "../../include/main.h"

using namespace pros;

#ifndef AUTON_CONTROL
#define AUTON_CONTROL

/*
    only put declarations in this file
*/

struct vector
    {
    	double x;
    	double y;
    	double rotation;
      bool Turning;
    };

extern double gyro_value();
extern int currentTime();
extern double rotation();

extern void ohnomyP(double dRight, double dLeft, double dStrafe, vector center);
extern double PID(vector center, double turn, double* pLastError);

extern void move(double left, double right);
extern void move_steering (int speed, double turn);

extern void speed_up(int speed, int max, int duration, double rate, vector center);
extern void slow_down(int speed, int min, int duration, double  rate, vector center);
extern void go_straight(int distance, int maxSpeed, vector* pCenter);

extern void turn(int degrees, double radius, vector* pCenter);

extern void bot_grid(vector* pCenter, vector point1);

extern void back(double distance, double maxSpeed, vector* pCenter);

extern void turn_forwards(int degrees, double radius, vector* pCenter);

extern void turn_backwards(int degrees, double radius, vector* pCenter);

extern vector center;

#endif