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
 * Outputs intake voltage to the text file
*/
void trackIntake();

/**
 * Outputs flywheel voltage to the text file
*/
void trackFlywheel();

/**
 * Tracks if wings are on or off
*/
void trackWings(bool state);

/**
 * Track lifter voltage to the text file
*/
void trackLifter();