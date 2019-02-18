#pragma once

#include <frc/Joystick.h>

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
};