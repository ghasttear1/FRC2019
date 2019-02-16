#include "Functions.h"

// Divide input by 12
double Functions::InputVoltage(double voltage) {
    return(voltage/12);
}

// Set motor at speed for a specific amount of time (ntested)
void Functions::SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime) {
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