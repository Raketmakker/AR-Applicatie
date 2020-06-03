#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "blobdetectionavans.h"

// Function pointer
typedef void (*callback_function)(int x, int y);

class VisionModule {
private:
    cv::VideoCapture cap;               // used to read frames from a camera
    Ptr<SimpleBlobDetector> sbd;        // used to detect blobs
    callback_function callback;         // callback method for coordinates on grid
    int thresholdValue;                 // wat
    float gridWidth;                    // The width of the grid in pixels
    float gridHeigth;                   // The heigth of the grid in pixels 
    Point2d gridStart;                  // The upper left corner of the grid

    /**
        @brief Searches a given image for a specific colour

        @param sourceImage the image to search
        @param lower the lower values of the colour in HSV format
        @param upper the upper values of the colour in HSV format
        @param points a pass by reference vector to store the points that get found in the method
        @return a Mat object containing markers where the points are located on the source image (primarily used for debugging)
    */
    Mat SearchColourBlob(Mat sourceImage, Scalar lower, Scalar Upper, vector<Point2d>& points);

    /**
        @brief Helper method which processes the data about the grid corners

        @param corners a vector of all the corners found, checks internally if there are 4 corners
        @return true if the processing was succesful, false if unsuccesful
    */
    bool HandleCorners(vector<Point2d> corners);

    /**
        @brief Helper method which processes the data about the selection

        @param selection the point on the screen which the user has selected
        @return true if the processing was succesful, false if unsuccesful
    */
    bool HandleSelection(Point2d selection);

public:
    VisionModule(callback_function callback) noexcept;
    VisionModule() = delete;
    ~VisionModule() = default;

    void start();
};