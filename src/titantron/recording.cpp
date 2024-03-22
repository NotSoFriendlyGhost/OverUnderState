#include "recording.hpp"
#include "EZ-Template/util.hpp"
#include "main.h"
#include <fstream>
#include <ios>

void startRecording(std::string filename){
    filename = "/usd/" + filename;
    ofs.open(filename.c_str(), std::ios::out | std::ios::trunc);
    recording = true;
}
void stopRecording(){
    ofs<<-12001;
    ofs.close();
    recording = false;
}
void playback(std::string filename){
    filename = "/usd/" + filename;
    std::ifstream ifs;
    ifs.open(filename.c_str());
    int leftVoltage;
    int rightVoltage;
    int intakeVoltage;
    int flywheelVoltage;
    bool wingState;
    int lifterVoltage;
    while (true) {
        ifs>>leftVoltage;
        if(leftVoltage==-12001) break;
        ifs>>rightVoltage>>intakeVoltage>>flywheelVoltage>>wingState>>lifterVoltage;
		drive.playbackDrive(leftVoltage, rightVoltage);
        intake.move_voltage(intakeVoltage);
        flywheel.move_voltage(flywheelVoltage);
        wings.set_value(wingState);
        lifter.move_voltage(lifterVoltage);
		
        pros::delay(1);
	}
}

void trackIntake(){
    ofs<<intake.get_voltage()<<' ';
};
void trackFlywheel(){
    ofs<<flywheel.get_voltage()<<' ';
}
void trackWings(bool state){
    ofs<<state<<' ';
}
void trackLifter(){
    ofs<<lifter.get_voltage();
}