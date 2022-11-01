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

enum AutonEnum {S_BLUE5 = -1, B_BLUE3 = -2, S_BLUE7 = -3, S_BLUE8 = -4, B_BLUE6_C = -5, S_RED5 = 1, B_RED3 = 2, S_RED7 = 3, S_RED8 = 4, B_RED6_C = 5, NOTHING = 10, SKILLS = 0};

template<typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif