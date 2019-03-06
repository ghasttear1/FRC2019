#pragma once

#include <opencv2/opencv.hpp>
#include <cameraserver/CameraServer.h>
#include <frc/Timer.h>

class Vision {
    public:
        // Declare vision thread
        static void VisionThread(Vision* vision);
        // (ntested)
        bool lenStatus;
};