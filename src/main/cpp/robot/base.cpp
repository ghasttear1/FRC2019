#include "robot/base.hpp"

namespace robot {

void Base::RobotInit() {

	vision_ = std::shared_ptr<core::Vision>{ new core::Vision };
	std::thread visionThread(core::Vision::Thread, vision_);
	visionThread.detach();
}

void Base::RobotPeriodic() {}
void Base::AutonomousInit() {}

void Base::AutonomousPeriodic() {
	Base::TeleopPeriodic();
}

void Base::TeleopInit() {}

void Base::TeleopPeriodic() {

	using namespace core;
	using namespace interface;
	using namespace utils;

	Mappings::drive.ArcadeDrive(Operator::driverGamepad->GetRawAxis(1)
								* maths::Map(Operator::driveSpeed.GetDouble(0), -12, 12, -1, 1),
								Operator::driverGamepad->GetRawAxis(4)
								* maths::Map(Operator::turnSpeed.GetDouble(0), -12, 12, -1, 1));
}

void Base::TestPeriodic() {}

} // namespace robot

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<robot::Base>(); }
#endif