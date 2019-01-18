/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <ctre/Phoenix.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h>

#include <cameraserver/CameraServer.h>

#include <opencv2/opencv.hpp>

using namespace frc;
using namespace cv;
using namespace std;

// Thread so the robot doesn't need to wait for the completion
// static void VisionThread() {
// 	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
// 	// camera.SetResolution(640, 480);
// 	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
// 	cs::CvSource output = CameraServer::GetInstance()->PutVideo("customview", 640, 480);
// 	// Initialise Materials
// 	Mat frame;
// 	Mat frame_HSV;
// 	Mat frame_threshold;
// 	vector<vector<Point>> contours;
// 	Vec4f lines;
// 	// Factors
// 	int leniencyFactor = 50;
// 	int brightnessMin = 160;
// 	while(true) {
// 		cvSink.GrabFrame(frame);
// 		cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
// 		GaussianBlur(frame_HSV, frame_HSV, Size(3, 3), 0);
// 		inRange(frame_HSV, Scalar(0, 0, brightnessMin), Scalar(80, 80, 255), frame_threshold);
// 		if (!countNonZero(frame_threshold) < 1) {
// 			findContours(frame_threshold, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
// 			fitLine(Mat(contours[0]), lines, 2, 0, 0.01, 0.01);

// 			int lefty = (-lines[2] * lines[1] / lines[0]) + lines[3];
// 			int righty = ((frame_HSV.cols - lines[2])*lines[1] / lines[0]) + lines[3];

// 			if (righty >= (lefty - leniencyFactor) && righty <= (lefty + leniencyFactor)) {
// 				cout << "Forwards";
// 			}
// 			else {
// 				cout << "Direction";
// 			}
// 			// cout << lefty << "---" << righty << endl;
// 			// Draws line on frame from right to left with colour blue
// 			line(frame, Point(frame_HSV.cols - 1, righty), Point(0, lefty), Scalar(255, 0, 0), 2);
// 		}
// 		output.PutFrame(frame);
// 	}
// }

void Robot::RobotInit() {
	// thread visionThread(VisionThread);
	// visionThread.detach();
	CameraServer::GetInstance()->StartAutomaticCapture();
	m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
	m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
	SmartDashboard::PutData("Auto Modes", &m_chooser);
}

Joystick driverGamePad{0};

WPI_VictorSPX m_rightSPX1{0};
WPI_VictorSPX m_rightSPX2{1};
WPI_VictorSPX m_leftSPX1{2};
WPI_VictorSPX m_leftSPX2{3};

SpeedControllerGroup m_left{m_leftSPX1, m_leftSPX2};
SpeedControllerGroup m_right{m_rightSPX1, m_rightSPX2};

DifferentialDrive m_drive{m_left, m_right};


/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
	m_autoSelected = m_chooser.GetSelected();
	// m_autoSelected = SmartDashboard::GetString(
	//     "Auto Selector", kAutoNameDefault);
	std::cout << "Auto selected: " << m_autoSelected << std::endl;

	if (m_autoSelected == kAutoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
}

void Robot::AutonomousPeriodic() {
	if (m_autoSelected == kAutoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	m_drive.ArcadeDrive((driverGamePad.GetRawAxis(1) * 0.9), (driverGamePad.GetRawAxis(2) * 0.7));
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
