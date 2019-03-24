#include "Vision.h"

using namespace cv;
using namespace cs;
using namespace frc;

// A thread responisble for handling camera output
void Vision::VisionThread(Vision* vision) {
    // Initialise variables
    float leniencyFactor = 0.3;
    unsigned int brightnessMin = 180;
    unsigned int x = 115;
    unsigned int y = 85;
    unsigned int width = 5;
    unsigned int height = 5;
    int factor;
    int checkArea = (y + height * x + width) * leniencyFactor;
    Point pt1(x,y);
    Point pt2(x + width,y + height);
    Mat frame;
    Mat frameBW;

    // Start capture and set parameters
    UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(240, 180);
    camera.SetFPS(30);
    // Set frame input and output
    CvSink cvSink = CameraServer::GetInstance()->GetVideo();
    CvSource output = CameraServer::GetInstance()->PutVideo("customview", 240, 180);

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
                unsigned int intensity = frameBW.at<uchar>(yi, xi);
                if (intensity > brightnessMin) {
                    ++factor;
                }
            }
        }

        // If high enough amount of pixels in area are bright lenStatus = true
        if (factor > checkArea) {
            vision->lenStatus = true;
        } else {
            vision->lenStatus = false;
        }

        // Display red/green rectangle based on lenStatus
        if (vision->lenStatus) {
            rectangle(frame, pt1, pt2, Scalar(0,255,0));
        } else {
            rectangle(frame, pt1, pt2, Scalar(0,0,255));
        }

        // Output frame
        output.PutFrame(frame);
    }
}