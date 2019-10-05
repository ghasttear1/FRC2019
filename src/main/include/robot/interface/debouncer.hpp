#pragma once

// frc
#include <frc/Timer.h>
#include <frc/Joystick.h>
// std
#include <memory>

namespace robot {
namespace interface {

// Adds a delay between when button presses are allowed
class Debouncer {

private:
    int buttonNum_;
    double latest_{ 0 };
    double debouncePeriod_;
    frc::Timer timer_;
public:
    Debouncer(int buttonNum, float period) : buttonNum_(buttonNum), debouncePeriod_(period) {};
    // Checks whether or not the button should act or not
    bool Get(std::shared_ptr<frc::Joystick> joystick);
};

} // namespace interface
} // namespace robot