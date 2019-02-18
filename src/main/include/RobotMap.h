#pragma once

#include <ctre/Phoenix.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Encoder.h>
#include <frc/PIDController.h>

using namespace frc;

class RobotMap {
    public:
        // Declare motor variables
        WPI_VictorSPX m_rightSPX1{3};
        WPI_VictorSPX m_rightSPX2{4};
        WPI_VictorSPX m_leftSPX1{1};
        WPI_VictorSPX m_leftSPX2{2};
        WPI_VictorSPX m_armSPX1{7};
        WPI_VictorSPX m_rampSPX1{5};
        WPI_VictorSPX m_rampSPX2{6};
        SpeedControllerGroup m_ramp{m_rampSPX1, m_rampSPX2};
        SpeedControllerGroup m_left{m_leftSPX1, m_leftSPX2};
        SpeedControllerGroup m_right{m_rightSPX1, m_rightSPX2};
        DifferentialDrive m_drive{m_left, m_right};

        // Start encoder
        Encoder m_armEncoder{0, 1, false, Encoder::EncodingType::k4X};
};