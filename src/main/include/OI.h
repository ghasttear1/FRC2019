#pragma once

#include <frc/Joystick.h>
#include <frc/Shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableEntry.h>

using namespace frc;

class OI {
    public:
        // Store all input variables
        Joystick m_driverGamePad{0};
        // Joystick m_armGamePad{1};
        int m_buttonA = 1;
        int m_buttonB = 2;
        int m_buttonX = 3;
        int m_buttonY = 4;
        int m_buttonLB = 5;
        int m_buttonRB = 6;
        nt::NetworkTableEntry m_driveSpeed
        {
            Shuffleboard::GetTab("Main")
                .Add("Drive Speed", 12)
                .WithWidget("Number Slider")
                .GetEntry()
        };
        nt::NetworkTableEntry m_turnSpeed
        {
            Shuffleboard::GetTab("Main")
                .Add("Turn Speed", 12)
                .WithWidget("Number Slider")
                .GetEntry()
        };
};