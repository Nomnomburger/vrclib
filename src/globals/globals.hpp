#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

using namespace pros;

#ifndef GLOBALS
#define GLOBALS

extern pros::Controller master;

extern pros::Motor left_front;
extern pros::Motor right_front;
extern pros::Motor left_back;
extern pros::Motor right_back;
extern pros::Motor left_mid;
extern pros::Motor right_mid;

extern pros::Motor lift;
extern pros::Motor indexer;
extern pros::Motor intake;

extern pros::ADIDigitalOut piston_1;
extern pros::ADIDigitalOut piston_2;

extern pros::Imu inertial;



extern int autonSelection;

enum AutonEnum {BLUE_1 = -1, BLUE_2 = -2, BLUE_3 = -3, BLUE_4 = -4, BLUE_5 = -5, RED_1 = 1, RED_2 = 2, RED_3 = 3, RED_4 = 4, RED_5 = 5, NOTHING = 10, SKILLS = 0};

template<typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif