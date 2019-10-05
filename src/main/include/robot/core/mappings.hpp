#pragma once

// ctre (no namespace D:)
#include <ctre/Phoenix.h>
// frc
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>

namespace robot {
namespace core {

class Mappings {
public:
    static WPI_VictorSPX leftSPX1;
    static WPI_VictorSPX leftSPX2;
    static WPI_VictorSPX rightSPX1;
    static WPI_VictorSPX rightSPX2;
    static frc::SpeedControllerGroup leftMotors;
    static frc::SpeedControllerGroup rightMotors;
    // How the four drive motors are controlled
    static frc::DifferentialDrive drive;
};

} // namespace core
} // namespace robot