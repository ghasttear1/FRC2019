#include "Vision.h"

using namespace cv;
using namespace cs;
using namespace frc;

// A thread responisble for handling camera output (ntested)
void Vision::VisionThread() {
    // Initialise variables
    double leniencyFactor = 0.3;
    int brightnessMin = 160;
    int x = 159;
    int y = 119;
    int width = 2;
    int height = 2;
    bool lenStatus;
    int factor;
    int checkArea = (y + height * x + width) * leniencyFactor;
    Point pt1(x,y);
    Point pt2(x + width,y + height);
    Mat frame;
    Mat frameBW;

    // Start capture and set parameters
    UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(320, 240);
    camera.SetFPS(30);
    // Set frame input and output
    CvSink cvSink = CameraServer::GetInstance()->GetVideo();
    CvSource output = CameraServer::GetInstance()->PutVideo("customview", 320, 240);

    // Wait for camera to start properly (do not remove)
    Wait(10);

    while(true) {
        // Grab frame from input
        cvSink.GrabFrame(frame);
        // Convert frame to grayscale
        cvtColor(frame, frameBW, COLOR_BGR2GRAY);
        factor = 0;

        // Check if pixels in area are above brightness, if so add to factor
        for (int yi = 0; yi < y + height; ++yi) {
            for (int xi = 0; xi < x + width; ++xi) {
                int intensity = frameBW.at<uchar>(yi, xi);
                if (intensity > brightnessMin) {
                    ++factor;
                }
            }
        }

        // If high enough amount of pixels in area are bright lenStatus = true
        if (factor > checkArea) {
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