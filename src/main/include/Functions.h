#pragma once

#include <frc/SpeedController.h>
#include <frc/Timer.h>

using namespace frc;

class Functions {
    public:
        float InputVoltage(float voltage);
        void SetTimedMotor(SpeedController* motor, float motorSpeed, float motorTime);
};