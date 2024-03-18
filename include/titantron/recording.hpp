#pragma once
#include <string>

/**
 * Toggles recording
 * \param filename The inputs will be stored to a file with this name
*/
void startRecording(std::string filename);

/**
 * Stops recording
*/
void stopRecording();

/**
 * Starts playing back movements from the recording file
 * \param filename Name of the file being played
*/
void playback(std::string filename);

/**
 * Outputs intake state to the text file
 * \param state 1 means spinning forward, -1 means spinning in reverse, and 0 means braking
*/
void trackIntake(short state);

/**
 * Prints left joystick value to the text file
*/
void trackLeftStick(double value);

/**
 * Prints right joystick value to the text file
*/
void trackRightStick(double value);

/**
 * Tracks if wings are on or off
*/
void trackWings(bool state);