#include "main.h"
#include <fstream>
#include <ios>

void startRecording(std::string filename){
    filename = "/usd/" + filename;
    ofs.open(filename.c_str(), std::ios::out | std::ios::trunc);
    recording = true;
}
void stopRecording(){
    ofs<<-128;
    ofs.close();
    recording = false;
}
void playback(std::string filename){
    filename = "/usd/" + filename;
    std::ifstream ifs;
    ifs.open(filename.c_str());
    double leftStick = 0;
    double rightStick = 0;
    short intakeState = 0;
    while (true) {
        ifs>>leftStick;
        if(leftStick==-128) break;
        ifs>>rightStick>>intakeState;
		drive.playbackDrive(leftStick, rightStick);
		
		if(intakeState==1){
			intake.move_voltage(12000);
		}
		else if(intakeState==-1){
			intake.move_voltage(-12000);
		}
		else if(intakeState==0){
			intake.brake();
		}
        pros::delay(2);
	}
}
void trackLeftStick(double value){
    ofs<<value<<' ';
}
void trackRightStick(double value){
    ofs<<value<<' ';
}
void trackIntake(short state){
    ofs<<state<<' ';
};
void trackWings(bool state){
    ofs<<state<<' ';
}