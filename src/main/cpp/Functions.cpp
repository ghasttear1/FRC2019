#include "Functions.h"

// Divide input by 12
double Functions::InputVoltage(double voltage) {
    return(voltage/12);
}

// Set motor at speed for a specific amount of time (ntested)
void Functions::SetTimedMotor(SpeedController* motor, double motorSpeed, double motorTime) {
    motor->Set(motorSpeed);
    Wait(motorTime);
    motor->Set(0.0);
}