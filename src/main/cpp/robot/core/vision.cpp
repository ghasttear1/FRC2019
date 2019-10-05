#include "robot/core/vision.hpp"

namespace robot {
namespace core {

// A thread responisble for handling camera output
void Vision::Thread(std::shared_ptr<Vision> vision) {

	using namespace cv;
	using namespace cs;

    // Initialise variables
	unsigned int windowWidth{ 240 };
    unsigned int windowHeight{ 180 };
	unsigned int halfWidth{ windowWidth / 2 };
	unsigned int halfHeight{ windowHeight / 2 };
	unsigned int squareSize{ 20 };
	Scalar squareColor{ 0,255,0 };

	Point rectanglePoint1{ 0, 0 };
	Point rectanglePoint2{ 0, 0 };
	Point brightestPoint{ 0, 0 };

    Mat frame, frameBW;

    // Start capture and set parameters
    UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(windowWidth, windowHeight);
    camera.SetFPS(30);

    // Set frame input and output
    CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    CvSource output = frc::CameraServer::GetInstance()->PutVideo("visionstream", windowWidth, windowHeight);

    // Wait for camera to start properly IMPORTANT
    frc::Wait(10);

    while(true) {

        cvSink.GrabFrame(frame);
        cvtColor(frame, frameBW, COLOR_BGR2GRAY);

        // Reset minimum brightness
        unsigned int brightest = 0;

		// Checks all pixels for brightest value
		for (int x = 0; x<windowHeight; ++x) {
			for (int y = 0; y<windowWidth; ++y) {
				unsigned int intensity = frameBW.at<uchar>(x, y);
				if (intensity > brightest) {
					brightest = intensity;
					brightestPoint = Point(x, y);
				}
			}
		}

		rectanglePoint1 = Point(brightestPoint.x - squareSize,
								brightestPoint.y + squareSize);
								
		rectanglePoint2 = Point(brightestPoint.x + squareSize,
								brightestPoint.y - squareSize);


		// Draw a rectangle to the current frame
		rectangle(frame, rectanglePoint1, rectanglePoint2, squareColor);

        output.PutFrame(frame);
    }
}

} // namespace core
} // namespace robot