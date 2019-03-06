/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

void Robot::RobotInit() {
	// Start and detach the vision thread
	thread visionThread(Vision::VisionThread, &vision);
	visionThread.detach();
	// Start and detach the arm initialisation thread
	thread armThread(RobotMap::ArmInit, &robotMap);
	armThread.detach();
	// robotMap.m_armEncoder.Reset();
	// robotMap.m_armControl.Enable();
	// robotMap.m_armControl.SetSetpoint(0);

	// Dashboard data
	SmartDashboard::PutData("PID", &robotMap.m_armControl);
	SmartDashboard::PutNumber("Drive Speed", oi.m_driveSpeed);
	SmartDashboard::PutNumber("Turn Speed", oi.m_driveSpeed);
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
void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {
	// Mirror Teleop
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	// Arcade drive takes joystick axis -1 to 1 value multiplyed by max speed for up down, left right
	robotMap.m_drive.ArcadeDrive((-(oi.m_driverGamePad.GetRawAxis(1)) * fn.InputVoltage(oi.m_driveSpeed)),
	(oi.m_driverGamePad.GetRawAxis(4) * fn.InputVoltage(oi.m_turnSpeed)));

	// Basic if statement for ramp
	if (oi.m_driverGamePad.GetRawButton(oi.m_buttonLB)) {
		robotMap.m_ramp.Set(fn.InputVoltage(-12));
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonRB)) {
		robotMap.m_ramp.Set(fn.InputVoltage(12));
	} 
	else {
		robotMap.m_ramp.Set(fn.InputVoltage(0));
	}

	// Sets m_armState based on Dpad presses
	switch(oi.m_driverGamePad.GetPOV()) {
		case 180:
			robotMap.m_armState = 0;
			break;
		case 270:
			robotMap.m_armState = 1;
			break;
		case 0:
			robotMap.m_armState = 0;
			break;
	}

	// Switch for PID setpoints for arm in 2:1 ratio e.g (180 = 90degrees)
	switch(robotMap.m_armState) 
	{
		case 0:
			robotMap.m_armControl.SetSetpoint(0.00);
			break;
		case 1: 
			robotMap.m_armControl.SetSetpoint(120.00);
			break;
		case 2: 
			robotMap.m_armControl.SetSetpoint(170.00);
			break;
	}

	// Basic Auto Alignment Handler (ntested)
	if (oi.m_driverGamePad.GetRawButton(oi.m_buttonY)) 
	{
		if (vision.lenStatus) {
			robotMap.m_drive.ArcadeDrive((fn.InputVoltage(1)), fn.InputVoltage(0));
		} 
		else {
			robotMap.m_drive.ArcadeDrive((fn.InputVoltage(0)), fn.InputVoltage(1));
		}
	}
	
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
