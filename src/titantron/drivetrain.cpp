#include "drivetrain.hpp"
#include "main.h"



double Drivetrain::calcDegrees(double inches){
    int oneRev = 360;
    double degrees = inches * (1 / wheelCircumference) * oneRev * gearRatio;
    return degrees;
}

void Drivetrain::drivePID(double target){
    resetDriveEncoders();
    double error;
    double prevError = target;
    double integral = 0;
    double derivative;
    double currentPosition;
    bool enablePID = true;
    while(enablePID){
        currentPosition = (leftFront->get_position()+leftBack->get_position()+rightFront->get_position()+rightBack->get_position())/4;
        error = target - currentPosition;
        integral += error;
        derivative = error-prevError;
        prevError = error;
        if(error<=0) {
            integral = 0;
            enablePID = false;
        }
        
        double power = error*kP + integral * kI + derivative*kD;
        driveAll(power);
        
        pros::delay(20);
    }
    std::cout<<"Current position: "<<currentPosition<<'\n';
    std::cout<<"Target position: "<<target<<'\n';
    std::cout<<"DONE\n";
    drive.brakeAll();
    pros::delay(15);
}

void Drivetrain::driveAll(double power){
    leftFront->move_voltage(power);
    leftBack->move_voltage(power);
    rightFront->move_voltage(power);
    rightBack->move_voltage(power);
}

Drivetrain::Drivetrain(int leftA, int leftB, int rightA, int rightB, double wheelDiameter){
    bool reversed;
    reversed = (leftA<0);
    leftFront = new pros::Motor(leftA,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
    reversed = (leftB<0);
    leftBack = new pros::Motor(leftB,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
    reversed = (rightA<0);
    rightFront = new pros::Motor(rightA,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);
    reversed = (rightB<0);
    rightBack = new pros::Motor(rightB,pros::E_MOTOR_GEAR_GREEN,reversed,pros::E_MOTOR_ENCODER_DEGREES);

    wheelCircumference = wheelDiameter * M_PI;
}

void Drivetrain::setGearRatio(double drivenGear, double drivingGear){
    gearRatio = drivenGear/drivingGear;
}

void Drivetrain::setDrivePID(double p, double i, double d){
    kP = p;
    kI = i;
    kD = d;
}

void Drivetrain::setTurnPID(double p, double i, double d){
    turnkP = p;
    turnkI = i;
    turnkD = d;
}

void Drivetrain::resetDriveEncoders(){
    leftFront->tare_position();
    leftBack->tare_position();
    rightBack->tare_position();
    rightFront->tare_position();
};

void Drivetrain::arcadeDrive(){
    int power = master.get_analog(ANALOG_LEFT_Y);
    power = opcontrolLeftCurve(power);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    turn = opcontrolRightCurve(turn);
    int left = power + turn;
    int right = power - turn;
    leftFront->move(left);
    leftBack->move(left);
    rightFront->move(right);
    rightBack->move(right);
}

void Drivetrain::trackVoltage(){
    ofs<<leftFront->get_voltage()<<' ';
    ofs<<rightFront->get_voltage()<<' ';
}
void Drivetrain::playbackDrive(double leftVoltage, double rightVoltage){
    leftFront->move_voltage(leftVoltage);
    leftBack->move_voltage(leftVoltage);
    rightFront->move_voltage(rightVoltage);
    rightBack->move_voltage(rightVoltage);
}

void Drivetrain::setBrakeMode(pros::motor_brake_mode_e brakeMode){
    leftFront->set_brake_mode(brakeMode);
    leftBack->set_brake_mode(brakeMode);
    rightFront->set_brake_mode(brakeMode);
    rightBack->set_brake_mode(brakeMode);
}

void Drivetrain::brakeAll(){
    leftFront->brake();
    leftBack->brake();
    rightFront->brake();
    rightBack->brake();
}

void Drivetrain::driveInches(double inches){
    drivePID(calcDegrees(inches));
}

void Drivetrain::turnDegrees(double target){
    resetDriveEncoders();
    imu.tare_rotation();
    double error;
    double prevError = target;
    double integral = 0;
    double derivative;
    double currentPosition;
    bool enablePID = true;
    while(enablePID){
        currentPosition = imu.get_rotation();
        error = target - currentPosition;
        integral += error;
        derivative = error-prevError;
        prevError = error;
        if(error<=0) {
            integral = 0;
            enablePID = false;
        }
        double power = error*turnkP + integral * turnkI + derivative * turnkD;
        leftFront->move_voltage(power);
        leftBack->move_voltage(power);
        rightFront->move_voltage(-power);
        rightBack->move_voltage(-power);
        
        pros::delay(20);
    }
    std::cout<<"Current rotation: "<<currentPosition<<'\n';
    std::cout<<"Target rotation: "<<target<<'\n';
    std::cout<<"DONE\n";
    drive.brakeAll();
    pros::delay(15);

}

void Drivetrain::turnHeading(double target){
    resetDriveEncoders();
    double error;
    double prevError = target;
    double integral = 0;
    double derivative;
    double currentPosition;
    bool enablePID = true;
    bool right = (fabs(target - imu.get_heading())>0) ? true : false;
    while(enablePID){
        currentPosition = imu.get_heading();
        error = target - currentPosition;
        integral += error;
        derivative = error-prevError;
        prevError = error;
        if(error<=0) {
            integral = 0;
            enablePID = false;
        }
        double power = error*turnkP + integral * turnkI + derivative * turnkD;
        if(right){
            leftFront->move_voltage(power);
            leftBack->move_voltage(power);
            rightFront->move_voltage(-power);
            rightBack->move_voltage(-power);
        }
        else{
            leftFront->move_voltage(-power);
            leftBack->move_voltage(-power);
            rightFront->move_voltage(power);
            rightBack->move_voltage(power);
        }
        pros::delay(20);
    }
    std::cout<<"Current heading: "<<currentPosition<<'\n';
    std::cout<<"Target heading: "<<target<<'\n';
    std::cout<<"DONE\n";
    drive.brakeAll();
    pros::delay(15);
}

void Drivetrain::swingTurn(double target, bool right, double oppositeScale){
    resetDriveEncoders();
    double error;
    double prevError = target;
    double integral = 0;
    double derivative;
    double currentPosition;
    bool enablePID = true;
    while(enablePID){
        currentPosition = imu.get_heading();
        error = target - currentPosition;
        integral += error;
        derivative = error-prevError;
        prevError = error;
        if(error<=0) {
            integral = 0;
            enablePID = false;
        }
        double power = error*turnkP + integral * turnkI + derivative * turnkD;
        if(right){
            leftFront->move_voltage(power);
            leftBack->move_voltage(power);
            rightFront->move_voltage(power * oppositeScale);
            rightBack->move_voltage(power * oppositeScale);
        }
        else{
            leftFront->move_voltage(power * oppositeScale);
            leftBack->move_voltage(power * oppositeScale);
            rightFront->move_voltage(power);
            rightBack->move_voltage(power);
        }
        pros::delay(20);
    }
    std::cout<<"Current heading: "<<currentPosition<<'\n';
    std::cout<<"Target heading: "<<target<<'\n';
    std::cout<<"DONE\n";
    drive.brakeAll();
    pros::delay(15);
}