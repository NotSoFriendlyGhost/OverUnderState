#pragma once

#include "main.h" // IWYU pragma: keep

class Drivetrain{
    private:
        pros::Motor* leftFront;
        pros::Motor* leftBack;
        pros::Motor* rightFront;
        pros::Motor* rightBack;  
        double kP, kI, kD;
        double turnkP, turnkI, turnkD;
        double gearRatio;
        double wheelCircumference;

        /**
         * Transforms the number of inches needed to travel to degrees
        */
        double calcDegrees(double inches);

        /**
         * Use a PID loop to drive to the target
        */
        void drivePID(double target);

        /**
         * Drive all motors at a specific voltage
        */
        void driveAll(double power);
    public:
        /**
         *
         * Sets up four motor drive train by inputting port numbers. Entering a negative number reverses the motor.
         *
         */
        Drivetrain(int leftA, int leftB, int rightA, int rightB, double wheelDiameter);

        /**
         * Sets up gear ratio with drivenGear/drivingGear
        */
        void setGearRatio(double drivenGear, double drivingGear);

        /**
         * Sets PID constants for driving
        */
        void setDrivePID(double p, double i, double d);

        /**
         * Sets PID constants for turning
        */
        void setTurnPID(double p, double i, double d);

        /**
         * Tares all encoders on the drive motors
        */
        void resetDriveEncoders();

        /**
         * Turns on split arcade mode for driver control
        */
        void arcadeDrive();

        /**
         * Reads from the recorded text file and uses it to drive the robot
        */
        void playbackDrive(double leftStick, double rightStick);

        /**
         * Sets all drive motors to a brake mode
        */
        void setBrakeMode(pros::motor_brake_mode_e brakeMode);

        /**
         * Brakes all drive motors
        */
        void brakeAll();
        
        /**
         * Drives for a number of inches
        */
        void driveInches(double inches);

        /**
         * Turns for a number of degrees
        */
        void turnDegrees(double target);

        /**
         * Turn to a heading
        */
        void turnHeading(double target);

        /**
         * Turn while driving
         * \param target Heading to turn to
         * \param oppositeScale A value between 0 and 1 (exclusive). It scales down the motor power of the motors opposite the ones turning.
        */
        void swingTurn(double target, bool right, double oppositeScale);
};
