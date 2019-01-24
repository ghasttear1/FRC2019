/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>

#include <frc/IterativeRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h>

#include <ctre/Phoenix.h>

#include <cameraserver/CameraServer.h>

#include <opencv2/opencv.hpp>

using namespace frc;
using namespace cv;
using namespace std;

class Robot : public frc::IterativeRobot {
  public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;

  private:
    // Declaring variables
    WPI_VictorSPX m_rightSPX1{0};
    WPI_VictorSPX m_rightSPX2{1};
    WPI_VictorSPX m_leftSPX1{2};
    WPI_VictorSPX m_leftSPX2{3};
    SpeedControllerGroup m_left{m_leftSPX1, m_leftSPX2};
    SpeedControllerGroup m_right{m_rightSPX1, m_rightSPX2};
    DifferentialDrive m_drive{m_left, m_right};

    Joystick driverGamePad{0};
    Timer timer;
    SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    string m_autoSelected;

    // Creates pointer m_test to leftSPX1 (replace values for use with actual motor)
    SpeedController* m_test = &m_leftSPX1;

    // Functions
    double inputVoltage(double voltage) {
      return(voltage/12);
    }

    void SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime) {
      timer.Start();
      while(!timer.Get() >= motorSpeed) {
        motor->Set(0.0);
      }
      motor->Set(0.0);
      timer.Stop();
    }
};
