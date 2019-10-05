#pragma once

// frc
#include <frc/Joystick.h>
#include <frc/Shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
// nt
#include <networktables/NetworkTableEntry.h>
// std
#include <utility>
#include <memory>

namespace robot {
namespace interface {

class Operator {
public:
    // The controller used for the driver
    static std::shared_ptr<frc::Joystick> driverGamepad;
    static int buttonA;
    static int buttonB;
    static int buttonX;
    static int buttonY;
    static int buttonLB;
    static int buttonRB;
    // The number slider properties used for the shuffleboard widgets
    static wpi::StringMap<std::shared_ptr<nt::Value>> sliderProperties;
    static nt::NetworkTableEntry driveSpeed;
    static nt::NetworkTableEntry turnSpeed;
};

} // namespace interface
} // namespace robot