#pragma once

#include <opencv2/opencv.hpp>
#include <cameraserver/CameraServer.h>
#include <frc/Timer.h>

class Vision {
    public:
        static void VisionThread();
        // (ntested)
        bool lenStatus;
};