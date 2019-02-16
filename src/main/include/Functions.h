#pragma once

#include <frc/SpeedController.h>
#include <frc/Timer.h>

using namespace frc;

class Functions {
    public:
        double InputVoltage(double voltage);
        void SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime);
};