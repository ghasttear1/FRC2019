#include "robot/interface/operator.hpp"

namespace robot {
namespace interface {

std::shared_ptr<frc::Joystick> Operator::driverGamepad{ new frc::Joystick{0} };

int Operator::buttonA{1};
int Operator::buttonB{2};
int Operator::buttonX{3};
int Operator::buttonY{4};
int Operator::buttonLB{5};
int Operator::buttonRB{6};

wpi::StringMap<std::shared_ptr<nt::Value>> Operator::sliderProperties{
    std::make_pair("min", nt::Value::MakeDouble(-12)),
    std::make_pair("max", nt::Value::MakeDouble(12))
};

nt::NetworkTableEntry Operator::driveSpeed
{
    frc::Shuffleboard::GetTab("Main")
        .AddPersistent("Drive Speed", 0)
        .WithWidget(frc::BuiltInWidgets::kNumberSlider)
        .WithProperties(sliderProperties)
        .GetEntry()
};

nt::NetworkTableEntry Operator::turnSpeed
{
    frc::Shuffleboard::GetTab("Main")
        .AddPersistent("Turn Speed", 0)
        .WithWidget(frc::BuiltInWidgets::kNumberSlider)
        .WithProperties(sliderProperties)
        .GetEntry()
};

} // namespace interface
} // namespace robot