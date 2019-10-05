#include "robot/core/mappings.hpp"
   
namespace robot {
namespace core {

WPI_VictorSPX Mappings::leftSPX1{1};
WPI_VictorSPX Mappings::leftSPX2{2};
WPI_VictorSPX Mappings::rightSPX1{3};
WPI_VictorSPX Mappings::rightSPX2{4};
frc::SpeedControllerGroup Mappings::leftMotors{ leftSPX1, leftSPX2 };
frc::SpeedControllerGroup Mappings::rightMotors{ rightSPX1, rightSPX2 };
frc::DifferentialDrive Mappings::drive{ leftMotors, rightMotors };

} // namespace core
} // namespace robot