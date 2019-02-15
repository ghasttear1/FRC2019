#pragma once

#include <frc/Joystick.h>

using namespace frc;

class OI {
    public:
        Joystick m_driverGamePad{0};
        // Joystick m_armGamePad{1};
        int m_buttonA = 1;
        int m_buttonB = 2;
        int m_buttonX = 3;
        int m_buttonY = 4;
};