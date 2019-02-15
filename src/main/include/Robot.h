/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>

#include <frc/TimedRobot.h>
#include "OI.h"
#include "RobotMap.h"
#include "Function.h"
#include "Vision.h"

using namespace frc;
using namespace std;

class Robot : public frc::TimedRobot {
    public:
        void RobotInit() override;
        void RobotPeriodic() override;
        void AutonomousInit() override;
        void AutonomousPeriodic() override;
        void TeleopInit() override;
        void TeleopPeriodic() override;
        void TestPeriodic() override;

    // Makes instances of public classes for use in class Robot
    private:
        OI oi;
        RobotMap robotMap;
        Function fn;
};
