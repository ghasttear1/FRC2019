#pragma once

#include <frc/SpeedController.h>
#include <frc/Timer.h>

using namespace frc;

class Function {
    public:
        double InputVoltage(double voltage) {
            return(voltage/12);
        }

        void SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime) {
            Timer timer;
            timer.Start();
            while(!timer.Get() >= motorSpeed) {
                motor->Set(0.0);
            }
            motor->Set(0.0);
            timer.Stop();
        }

        // double toPIDDegrees(int degrees) {
        //   return(output)
        // }
};