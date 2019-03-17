#include "Functions.h"

// Divide input by 12
float Functions::InputVoltage(float voltage) {
    return(voltage/12);
}

// Set motor at speed for a specific amount of time (ntested)
void Functions::SetTimedMotor(SpeedController* motor, float motorSpeed, float motorTime) {
    motor->Set(motorSpeed);
    Wait(motorTime);
    motor->Set(0.0);
}