#pragma once

#include <opencv2/opencv.hpp>
#include <cameraserver/CameraServer.h>

using namespace cv;
using namespace cs;
using namespace frc;

class Vision {
    public:
        // A thread responisble for handling camera output
        static void VisionThread() {
            // Start capture and set parameters
            cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
            camera.SetResolution(320, 240);
            camera.SetFPS(30);
            // Set frame input and output
            cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
            cs::CvSource output = CameraServer::GetInstance()->PutVideo("customview", 320, 240);

            // Initialise variables
            Timer timerWait;
            double leniencyFactor = 0.3;
            int brightnessMin = 160;
            int x = 159;
            int y = 119;
            int width = 2;
            int height = 2;
            Point pt1(x,y);
            Point pt2(x + width,y + height);
            bool lenStatus;
            int factor;
            Mat frame;
            Mat frameBW;

            // Start timer for wait otherwise robot program doesn't start properly
            timerWait.Start();
            while(timerWait.Get() > 10.0) {
                // Grab frame from input
                cvSink.GrabFrame(frame);
                // Convert frame to grayscale
                cvtColor(frame, frameBW, COLOR_BGR2GRAY);
                factor = 0;

                // Check if pixels in area are above brightness, if so add to factor
                for (int yi = 0; yi < y + height; ++yi) {
                    for (int xi = 0; xi < x + width; ++xi) {
                        Scalar intensity = frameBW.at<uchar>(yi, xi);
                        if (intensity[0] > brightnessMin) {
                            ++factor;
                        }
                    }
                }

                // If high enough amount of pixels in area are bright lenStatus = true
                if (factor > ((y + height * x + width) * leniencyFactor)) {
                    lenStatus = true;
                } else {
                    lenStatus = false;
                }

                // Display red/green rectangle based on lenStatus
                if (lenStatus) {
                    rectangle(frame, pt1, pt2, Scalar(0,255,0));
                } else {
                    rectangle(frame, pt1, pt2, Scalar(0,0,255));
                }

                // Output frame
                output.PutFrame(frame);
            }
        }
};