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
// #include <frc/smartdashboard/SendableChooser.h>
// #include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h>
// #include <frc/shuffleboard/Shuffleboard.h>
// #include <frc/shuffleboard/ShuffleboardTab.h>

// #include <networktables/NetworkTableEntry.h>

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
    bool camStatus;

  // These variables are private to class robot
  private:
    // Declaring variables
    WPI_VictorSPX m_rightSPX1{0};
    WPI_VictorSPX m_rightSPX2{1};
    WPI_VictorSPX m_leftSPX1{2};
    WPI_VictorSPX m_leftSPX2{3};
    WPI_VictorSPX m_armSPX1{4};
    WPI_VictorSPX m_rampSPX1{5};
    WPI_VictorSPX m_winchSPX1{6};
    SpeedControllerGroup m_left{m_leftSPX1, m_leftSPX2};
    SpeedControllerGroup m_right{m_rightSPX1, m_rightSPX2};
    DifferentialDrive m_drive{m_left, m_right};

    Joystick m_driverGamePad{0};
    // Joystick m_armGamePad{1};
    Timer m_timer;
    // SendableChooser<std::string> m_chooser;
    // const std::string kAutoNameDefault = "Default";
    // const std::string kAutoNameCustom = "My Auto";
    // string m_autoSelected;

    // Functions
    double InputVoltage(double voltage) {
      return(voltage/12);
    }

    void SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime) {
      m_timer.Start();
      while(!m_timer.Get() >= motorSpeed) {
        motor->Set(0.0);
      }
      motor->Set(0.0);
      m_timer.Stop();
    }
};
