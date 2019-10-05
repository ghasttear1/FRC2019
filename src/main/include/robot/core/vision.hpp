#pragma once

// std
#include <memory>
// cv
#include <opencv2/opencv.hpp>
// cs
#include <cameraserver/CameraServer.h>
// frc
#include <frc/Timer.h>

namespace robot {
namespace core {

class Vision {
public:
    // The thread for running vision processing
    static void Thread(std::shared_ptr<Vision> vision);
};

} // namespace core
} // namespace robot