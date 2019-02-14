/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

// A thread responisble for handling camera output
void VisionThread() {
	Robot robotLink;
	// Start capture and set parameters
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(320, 240);

	// Set frame input and output
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	cs::CvSource output = CameraServer::GetInstance()->PutVideo("customview", 320, 240);

	// Initialise variables
	Timer wait;
	double leniencyFactor = 0.3;
	int brightnessMin = 160;
	int x = 159;
	int y = 119;
	int width = 2;
	int height = 2;
	Point pt1(x,y);
	Point pt2(x + width,y + height);
	bool lenStatus;
	int factor;
	Mat frame;
	Mat frame_BW;
	// Network table for adjusting minimum brightness for frame threshold
	// nt::NetworkTableEntry brightnessMin = Shuffleboard::GetTab("Camera")
	// 	.Add("Minimum Brightness", 255)
	// 	.WithWidget("Number Slider")
	// 	.GetEntry();

	// Start timer for wait otherwise robot program doesn't start properly
	wait.Start();
	while(wait.Get() > 10.0) {
		// Grab frame from input
		cvSink.GrabFrame(frame);
		cvtColor(frame, frame_BW, COLOR_BGR2GRAY);
		factor = 0;

		for (int yi = 0; yi < y + height; ++yi) {
			for (int xi = 0; xi < x + width; ++xi) {
				Scalar intensity = frame_BW.at<uchar>(yi, xi);
				if (intensity[0] > brightnessMin) {
					factor += 1;
				}
			}
		}

		if (factor > ((y + height * x + width) * leniencyFactor)) {
			lenStatus = true;
		} else {
			lenStatus = false;
		}

		if (lenStatus) {
			rectangle(frame, pt1, pt2, Scalar(0,255,0));
		} else {
			rectangle(frame, pt1, pt2, Scalar(0,0,255));
		}
		robotLink.camStatus = lenStatus;

		// Output frame
		output.PutFrame(frame);
	}
}

void Robot::RobotInit() {
	// Start and detach the vision thread
	thread visionThread(VisionThread);
	visionThread.detach();

	// CameraServer::GetInstance()->StartAutomaticCapture();
	// m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
	// m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
	// SmartDashboard::PutData("Auto Modes", &m_chooser);
}

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
	// m_autoSelected = m_chooser.GetSelected();
	// // m_autoSelected = SmartDashboard::GetString(
	// //     "Auto Selector", kAutoNameDefault);
	// std::cout << "Auto selected: " << m_autoSelected << std::endl;

	// if (m_autoSelected == kAutoNameCustom) {
	// 	// Custom Auto goes here
	// } else {
	// 	// Default Auto goes here
	// }
}

void Robot::AutonomousPeriodic() {
	// if (m_autoSelected == kAutoNameCustom) {
	// 	// Custom Auto goes here
	// } else {
	// 	// Default Auto goes here
	// }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	// Arcade drive takes joystick axis -1 to 1 value multiplyed by max speed for up down, left right
	m_drive.ArcadeDrive((m_driverGamePad.GetRawAxis(1) * InputVoltage(10.8)), (m_driverGamePad.GetRawAxis(4) * InputVoltage(8.4)));
	// When button 3 is pressed set pointer(declare in header), to desired voltage and time 
	if (m_driverGamePad.GetRawButtonPressed(3)) {
		SetTimedMotor(&m_rampSPX1, InputVoltage(8), 2.0);
	}
	
	// Controls arm out and in
	if (m_driverGamePad.GetRawButton(1)) {
		m_armSPX1.Set(InputVoltage(12));
	} else if(m_driverGamePad.GetRawButton(2)) {
		m_armSPX1.Set(InputVoltage(-12));
	}
	else {
		m_armSPX1.Set(InputVoltage(0));
	}

	// Basic Auto Alignment Handler
	if (m_driverGamePad.GetRawButton(4)) {
		if (camStatus) {
			m_drive.ArcadeDrive((InputVoltage(1)), InputVoltage(0));
		} else {
			m_drive.ArcadeDrive((InputVoltage(0)), InputVoltage(1));
		}
		
	}

	// Controls elevator up and down
	// if (m_driverGamePad.GetRawButton(DPAD_UP)) {
	// 	m_winchSPX.Set(InputVoltage(12));
	// } else if(m_driverGamePad.GetRawButton(DPAD_UP)) {
	// 	m_winchSPX.Set(InputVoltage(-12));
	// }
	// else {
	// 	m_winchSPX.Set(InputVoltage(0));
	// }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
