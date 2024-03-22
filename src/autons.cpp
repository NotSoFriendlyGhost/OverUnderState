#include "autons.hpp"
#include "main.h"
#include "pros/distance.h"
#include "pros/rtos.hpp"
#include "titantron/globals.hpp"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(70, 0, 300);
  chassis.pid_turn_constants_set(4, 0, 35, 15);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}
void leftAuton(){
  intake.move_voltage(12000);
  chassis.pid_drive_set(20_in,DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(250);
  chassis.pid_turn_relative_set(-5_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-21_in,DRIVE_SPEED, true);
  chassis.pid_wait();

  wings.set_value(1);

  chassis.pid_turn_relative_set(-97_deg, TURN_SPEED);
  chassis.pid_wait();
  wings.set_value(0);

  chassis.pid_drive_set(1_in,DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_turn_relative_set(7_deg, TURN_SPEED);
  chassis.pid_wait();

  wings.set_value(0);
  chassis.pid_drive_set(-17_in,DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(1_in,DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(170_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  chassis.pid_drive_set(0.5,DRIVE_SPEED,false);
  pros::delay(2000);
}
void altRight(){
  wings.set_value(1); // Push preload to the side and face barrier
  chassis.drive_imu_reset(-45);
  chassis.pid_turn_set(-38_deg, TURN_SPEED);
  chassis.pid_wait();
  wings.set_value(0);

  intake.move_voltage(12000);
  chassis.pid_drive_set(25_in,DRIVE_SPEED, true); // Go for ball next to barrier
  chassis.pid_wait();
  pros::delay(300);

  chassis.pid_turn_set(-38_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-25_in,DRIVE_SPEED, true); // Back in corner
  chassis.pid_wait_until(-20_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED); // Outtake barrier ball
  chassis.pid_wait();
  intake.move_voltage(-12000);
  pros::delay(300);

  //wings.set_value(1);
  chassis.pid_turn_set(-170,TURN_SPEED * 0.8); // Scoop corner ball out with wings
  chassis.pid_wait();
  wings.set_value(0);

  chassis.pid_turn_set(-160,TURN_SPEED); // Face ball
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in,DRIVE_SPEED); // Push corner ball and preload into the goal
  chassis.pid_wait();

  chassis.pid_drive_set(3_in,DRIVE_SPEED); // Move out of goal
  chassis.pid_wait();

  chassis.pid_turn_set(-65,TURN_SPEED); // Face other barrier ball
  chassis.pid_wait();

  intake.move_voltage(12000);
  chassis.pid_drive_set(20_in,DRIVE_SPEED, true); // Get other barrier ball
  chassis.pid_wait();
  pros::delay(100);

  chassis.pid_turn_set(-180,TURN_SPEED); // Back facing middle ball
  chassis.pid_wait();

  chassis.pid_drive_set(-7_in,DRIVE_SPEED); // Drive towards middle ball
  chassis.pid_wait();

  chassis.pid_turn_set(-90,TURN_SPEED); // Back facing goal
  chassis.pid_wait();
  wings.set_value(1);

  chassis.pid_drive_set(-12_in,DRIVE_SPEED); // Push
  chassis.pid_wait();

  chassis.pid_drive_set(3_in,DRIVE_SPEED); // Move out of goal
  wings.set_value(0);
  chassis.pid_wait();

  chassis.pid_turn_set(90,TURN_SPEED); // Face goal with intaked ball
  chassis.pid_wait();

  intake.move_voltage(-12000); // Outtake ball
  pros::delay(300);
  chassis.pid_drive_set(2_in,DRIVE_SPEED); // Push
  chassis.pid_wait();

  chassis.pid_drive_set(2_in,DRIVE_SPEED); // Push
  chassis.pid_wait();
}
void safeRight(){
  chassis.drive_imu_reset(-90);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move_voltage(12000);
  chassis.pid_drive_set(3_in,DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(250);
  chassis.pid_drive_set(-12_in,DRIVE_SPEED);
  chassis.pid_wait();
  wings.set_value(1);
  chassis.pid_turn_set(-135_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in,DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(-180_deg,TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-5_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(5_in,DRIVE_SPEED);
  chassis.pid_wait();
  wings.set_value(0);
}

void aggroRight(){
  wings.set_value(1);
  chassis.drive_imu_reset(-45);

  chassis.pid_turn_set(-38_deg, TURN_SPEED);
  chassis.pid_wait();
  wings.set_value(0);

  intake.move_voltage(12000);
  chassis.pid_drive_set(25_in,DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  wings.set_value(1);

  chassis.pid_drive_set(-13_in,DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(4_in,DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  pros::delay(500);
  chassis.pid_drive_set(4_in,DRIVE_SPEED);
  wings.set_value(0);
  chassis.pid_wait();

  chassis.pid_drive_set(-3_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-120_deg, TURN_SPEED); // Get close barrier ball
  chassis.pid_wait();
  intake.move_voltage(12000);



  chassis.pid_drive_set(12_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-4_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED); // Go back to corner
  chassis.pid_wait();

  chassis.pid_drive_set(-19_in,DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  pros::delay(500);
  wings.set_value(1);

  chassis.pid_turn_relative_set(-200_deg, TURN_SPEED);
  chassis.pid_wait();
  wings.set_value(0);

  chassis.pid_drive_set(-13_in,DRIVE_SPEED);
  chassis.pid_wait();
}

void skills(){
  chassis.drive_imu_reset(135);
  chassis.pid_turn_set(135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in,DRIVE_SPEED*0.8);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
  
  chassis.pid_drive_set(-8_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(6_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(80_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-2_in,DRIVE_SPEED);
  chassis.pid_wait();
  wings.set_value(1);

  pros::delay(5000);

  /*flywheel.move_voltage(-12000);
  pros::delay(35000);
  flywheel.brake();*/
  wings.set_value(0);
  chassis.pid_drive_set(2_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-30_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in,DRIVE_SPEED);
  chassis.pid_wait();


  chassis.pid_turn_set(-85_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-30_in,DRIVE_SPEED,true);
  chassis.pid_wait();

  chassis.pid_turn_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait();
  
  chassis.pid_drive_set(-8_in,DRIVE_SPEED);
  chassis.pid_wait();

}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}