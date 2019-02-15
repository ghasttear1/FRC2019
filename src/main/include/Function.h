#pragma once

#include <frc/SpeedController.h>
#include <frc/Timer.h>

using namespace frc;

class Function {
    public:
        // Divide input by 12
        double InputVoltage(double voltage) {
            return(voltage/12);
        }

        // Set motor at speed for a specific amount of time
        void SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime) {
            Timer timer;
            timer.Start();
            while(!timer.Get() >= motorSpeed) {
                motor->Set(0.0);
            }
            motor->Set(0.0);
            timer.Stop();
        }

        // // Turn degrees into setpoint for PID
        // double toPIDDegrees(int degrees) {
        //   return(output)
        // }
};