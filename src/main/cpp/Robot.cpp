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
	// thread armThread(RobotMap::ArmInit, &robotMap);
	// armThread.detach();
	robotMap.m_armEncoder.Reset();
	robotMap.m_armControl.Enable();
	robotMap.m_armControl.SetSetpoint(0);

	// Dashboard data
	Shuffleboard::GetTab("Main")
		.Add("PID", &robotMap.m_armControl)
		.WithWidget("PID Command");
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {
	// Arcade drive takes joystick axis -1 to 1 value multiplyed by max speed for up down, left right
	robotMap.m_drive.ArcadeDrive((-(oi.m_driverGamePad.GetRawAxis(1)) * fn.InputVoltage(oi.m_driveSpeed.GetDouble(0))),
	(oi.m_driverGamePad.GetRawAxis(4) * fn.InputVoltage(oi.m_turnSpeed.GetDouble(0))));

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
	// switch(oi.m_driverGamePad.GetPOV()) {
	// 	case 180:
	// 		robotMap.m_armState = 2;
	// 		break;
	// 	case 270:
	// 		robotMap.m_armState = 1;
	// 		break;
	// 	case 0:
	// 		robotMap.m_armState = 0;
	// 		break;
	// }

	if (oi.m_driverGamePad.GetRawButton(oi.m_buttonA)) {
		robotMap.m_armState = 2;
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonB)) {
		robotMap.m_armState = 1;
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonX)) {
		robotMap.m_armState = 0;
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonY)) {
		robotMap.m_armState = 3;
	}

	// Switch for PID setpoints for arm in 2:1 ratio e.g (180 = 90degrees)
	switch(robotMap.m_armState) 
	{
		case 0:
			robotMap.m_armControl.SetSetpoint(0.00);
			break;
		case 1: 
			robotMap.m_armControl.SetSetpoint(112.00);
			break;
		case 2: 
			robotMap.m_armControl.SetSetpoint(180.00);
			break;
		case 3:
			robotMap.m_armControl.SetSetpoint(-180.00);
			break;
	}
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	// Arcade drive takes joystick axis -1 to 1 value multiplyed by max speed for up down, left right
	robotMap.m_drive.ArcadeDrive((-(oi.m_driverGamePad.GetRawAxis(1)) * fn.InputVoltage(oi.m_driveSpeed.GetDouble(0))),
	(oi.m_driverGamePad.GetRawAxis(4) * fn.InputVoltage(oi.m_turnSpeed.GetDouble(0))));

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
	// switch(oi.m_driverGamePad.GetPOV()) {
	// 	case 180:
	// 		robotMap.m_armState = 2;
	// 		break;
	// 	case 270:
	// 		robotMap.m_armState = 1;
	// 		break;
	// 	case 0:
	// 		robotMap.m_armState = 0;
	// 		break;
	// }

	if (oi.m_driverGamePad.GetRawButton(oi.m_buttonA)) {
		robotMap.m_armState = 2;
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonB)) {
		robotMap.m_armState = 1;
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonX)) {
		robotMap.m_armState = 0;
	}
	else if (oi.m_driverGamePad.GetRawButton(oi.m_buttonY)) {
		robotMap.m_armState = 3;
	}

	// Switch for PID setpoints for arm in 2:1 ratio e.g (180 = 90 degrees)
	switch(robotMap.m_armState) 
	{
		case 0:
			robotMap.m_armControl.SetSetpoint(0.00);
			break;
		case 1: 
			robotMap.m_armControl.SetSetpoint(112.00);
			break;
		case 2: 
			robotMap.m_armControl.SetSetpoint(180.00);
			break;
		case 3:
			robotMap.m_armControl.SetSetpoint(-180.00);
			break;
	}
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
