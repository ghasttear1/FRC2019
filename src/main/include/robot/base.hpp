#pragma once

// std
#include <iostream>
// frc
#include <frc/TimedRobot.h>
// robot
#include "robot/core/vision.hpp"
#include "robot/core/mappings.hpp"
#include "robot/interface/operator.hpp"
#include "robot/utils/maths/maths.hpp"

namespace robot {

class Base : public frc::TimedRobot {
private:
    std::shared_ptr<core::Vision> vision_;
public:
    // Gets called at robot startup
    void RobotInit() override;
    // Gets called periodically while the robot is turned on
    void RobotPeriodic() override;
    // Gets called when autonomous period starts
    void AutonomousInit() override;
    // Gets called periodically while autonomous mode is active
    void AutonomousPeriodic() override;
    // Gets called when teleoperated period starts
    void TeleopInit() override;
    // Gets called periodically while teleoperated mode is active
    void TeleopPeriodic() override;
    // Gets called periodically while test mode is active
    void TestPeriodic() override;
};

} // namespace robot