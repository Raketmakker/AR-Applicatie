#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

// Function pointer
typedef void (*callback_function)(int x, int y);

class VisionModule
{
private:
    cv::VideoCapture _cap;               // used to read frames from a camera
    Ptr<SimpleBlobDetector> _sbd;        // used to detect blobs
    callback_function _callback;         // callback method for coordinates on grid
    float _gridWidth;                    // The width of the grid in pixels
    float _gridHeigth;                   // The heigth of the grid in pixels 
    Point2d _gridStart;                  // The upper left corner of the grid
    bool _isRunning;                     // Keeps track if the visionmodule is currently running 

    /**
        @brief Searches a given image for a specific colour

        @param sourceImage the image to search
        @param lower the lower values of the colour in HSV format
        @param upper the upper values of the colour in HSV format
        @param points a pass by reference vector to store the points that get found in the method
        @return a Mat object containing markers where the points are located on the source image (primarily used for debugging)
    */
    Mat _SearchColourBlob(Mat sourceImage, Scalar lower, Scalar Upper, std::vector<Point2d>& points);

    /**
        @brief Helper method which processes the data about the grid corners

        @param corners a vector of all the corners found, checks internally if there are 4 corners
        @return true if the processing was succesful, false if unsuccesful
    */
    bool _HandleCorners(std::vector<Point2d> corners);

    /**
        @brief Helper method which processes the data about the selection

        @param selection the point on the screen which the user has selected
        @return true if the processing was succesful, false if unsuccesful
    */
    bool _HandleSelection(Point2d selection);

    /**
        @brief Function executed by the visionmodule thread.
    */
    void _VisionThread();

public:
    VisionModule(callback_function callback) noexcept;
    VisionModule() = delete;
    ~VisionModule() = default;

    /**
        @brief Starts the visionmodule on a new thread. The visionmodule reads from the camera, looks if a grid and selection marker are
               present, and calls the callback method which was passed in the constructor. In this call the visionmodule will pass
               the x and y coordinates of the selection marker on the grid.
    */
    void Start();

    /**
        @brief Stops the visionmodule process. This function stops the current thread, and releases any of it's current resources.
    */
    void Stop();
};