#include "RobotMap.h"

// Arm initialisation
void RobotMap::ArmInit(RobotMap* robotMap) {
    robotMap->m_armControl.Disable();
    // Set arm to slowly go in until limit switch hit(bool reversed)
    while(robotMap->m_armlimit.Get()) {
        robotMap->m_armSPX1.Set(-0.1);
    }
    // Arm encoder to 0 and PID enable
    robotMap->m_armEncoder.Reset();
    robotMap->m_armControl.Enable();
    robotMap->m_armControl.SetSetpoint(0);
}