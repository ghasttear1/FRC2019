#include "robot/interface/debouncer.hpp"

namespace robot {
namespace interface {

bool Debouncer::Get(std::shared_ptr<frc::Joystick> joystick) {
    double now = timer_.GetFPGATimestamp();
    if (joystick->GetRawButton(buttonNum_)){
        if ((now - latest_) > debouncePeriod_){
            latest_ = now;
            return true;
        }
    }
    return false;
}

} // namespace interface
} // namespace robot