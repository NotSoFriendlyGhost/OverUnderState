#pragma once

#include "main.h"
#include "pros/motors.hpp"
#include "pros/vision.hpp"
#include <fstream>

class Drivetrain;
extern Drivetrain drive;

extern pros::Motor intake;
extern pros::Motor flywheel;
extern pros::Motor lifter;
extern pros::ADIDigitalOut wings;

extern pros::Controller master;
extern pros::Imu imu;

extern float flywheelVelocity;
extern bool wingState;

extern std::ofstream ofs;
extern bool recording;

extern pros::Vision vision;

extern int tileLength;
extern double diagTileLength;