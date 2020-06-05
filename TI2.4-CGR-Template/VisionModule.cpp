#include "VisionModule.h"
#include <thread>
#include <chrono>

constexpr auto KEYCODE_SPACE = 32;
constexpr auto MARKER_SIZE = 25;

using namespace cv;
using namespace std;
using namespace chrono_literals;

int Min_Area = 1, Max_Area = 100000, thresholdValue;

int cLowH = 0;
int cHighH = 20;
int cLowS = 96;
int cHighS = 255;
int cLowV = 47;
int cHighV = 255;

int sLowH = 100;
int sHighH = 125;
int sLowS = 65;
int sHighS = 255;
int sLowV = 19;
int sHighV = 255;

VisionModule::VisionModule(callback_function callback) noexcept :
    _callback(callback), _gridWidth(-1), _gridHeigth(-1), _gridStart(Point2d(-1, -1)), _isRunning(false)
{
    _cap = cv::VideoCapture(1);  // 0 = Webcam, for the daheng camera increase the number by one until you find it

    if (_cap.isOpened())
    {
        _cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
        _cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);
    }
    else
    {
        cout << "Cannot open camera" << endl;
    }
}

void VisionModule::Start()
{
    _isRunning = true;
    std::thread visionThread(&VisionModule::_VisionThread, this);
    visionThread.detach();
}

void VisionModule::Stop() 
{
    _isRunning = false;
}

Mat VisionModule::_SearchColourBlob(Mat sourceImage, Scalar lowerValue, Scalar upperValue, vector<Point2d>& blobs)
{
    // Convert to HSV image
    Mat HSV_frame;
    cvtColor(sourceImage, HSV_frame, COLOR_BGR2HSV);

    // Filter the desired colour and convert this to a binary image
    Mat thresholded_frame;
    inRange(HSV_frame, lowerValue, upperValue, thresholded_frame);
    threshold(thresholded_frame, thresholded_frame, 50, 1, CV_THRESH_BINARY_INV);

    // Remove small static pixels
    erode(thresholded_frame, thresholded_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(thresholded_frame, thresholded_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    // Fill up small holes
    dilate(thresholded_frame, thresholded_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(thresholded_frame, thresholded_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    // Search for  blobs
    vector<cv::KeyPoint> keypoints;
    _sbd->detect(thresholded_frame * 255, keypoints);
    //cout << "Amount of select blobs: " << keypoints.size() << endl;

    // Mark the found blobs
    Mat marker = Mat::zeros(sourceImage.size(), CV_8UC3);;
    for (auto keypoint : keypoints)
    {
        float x = keypoint.pt.x;
        float y = keypoint.pt.y;

        //cout << "X:" << x << " Y:" << y << endl;

        line(marker, Point(x - MARKER_SIZE, y - MARKER_SIZE), Point(x + MARKER_SIZE, y + MARKER_SIZE), Scalar(255, 0, 0), 2);
        line(marker, Point(x + MARKER_SIZE, y - MARKER_SIZE), Point(x - MARKER_SIZE, y + MARKER_SIZE), Scalar(255, 0, 0), 2);

        blobs.push_back(Point(x, y));
    }

    return marker;
}

bool VisionModule::_HandleCorners(vector<Point2d> corners)
{
    if (corners.size() != 4)    // Check if 4 corners are present
    {
        return false;
    }

    float smallestX = corners[0].x, largestX = corners[0].x;
    float smallestY = corners[0].y, largestY = corners[0].y;

    for (Point2d corner : corners)  // Search for the minimum and maximum values of x and y
    {
        if (corner.x < smallestX)
        {
            smallestX = corner.x;
        }
        if (corner.x > largestX)
        {
            largestX = corner.x;
        }
        if (corner.y < smallestY)
        {
            smallestY = corner.y;
        }
        if (corner.y > largestY)
        {
            largestY = corner.y;
        }
    }

    // Save grid information to class attributes
    _gridStart = Point2d(smallestX, smallestY);
    _gridWidth = largestX - smallestX;
    _gridHeigth = largestY - smallestY;

    //cout << "Grid is " << gridWidth << "x" << gridHeigth << " pixels\n";
    //cout << "Grid starts at (" << gridStart.x << "," << gridStart.y << ")\n";

    return true;
}

bool VisionModule::_HandleSelection(Point2d selection)
{
    //Check if the selection is within the grid
    if (selection.x < _gridStart.x || selection.x > _gridStart.x + _gridWidth)
    {
        cout << "VisionModule::HandleSelection: Selection not in grid\n";
        return false;
    }
    if (selection.y < _gridStart.y || selection.y > _gridStart.y + _gridHeigth)
    {
        cout << "VisionModule::HandleSelection: Selection not in grid\n";
        return false;
    }

    //Calculate the x and y values as a 10x10 grid
    float cellWidth = _gridWidth / 10;
    float cellheigth = _gridHeigth / 10;

    int selectionX = (selection.x - _gridStart.x) / cellWidth;
    int selectionY = (selection.y - _gridStart.y) / cellheigth;

    _callback(selectionX, selectionY);

    return true;
}

void VisionModule::_VisionThread()
{
    _sbd = SimpleBlobDetector::create();

    namedWindow("Control Corners");
    createTrackbar("LowH", "Control Corners", &cLowH, 255); //Hue (0 - 255)
    createTrackbar("HighH", "Control Corners", &cHighH, 255);
    createTrackbar("LowS", "Control Corners", &cLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control Corners", &cHighS, 255);
    createTrackbar("LowV", "Control Corners", &cLowV, 255);//Value (0 - 255)
    createTrackbar("HighV", "Control Corners", &cHighV, 255);

    namedWindow("Control Select");
    createTrackbar("LowH", "Control Select", &sLowH, 255); //Hue (0 - 255)
    createTrackbar("HighH", "Control Select", &sHighH, 255);
    createTrackbar("LowS", "Control Select", &sLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control Select", &sHighS, 255);
    createTrackbar("LowV", "Control Select", &sLowV, 255);//Value (0 - 255)
    createTrackbar("HighV", "Control Select", &sHighV, 255);

    while (_isRunning)
    {
        Mat original_frame;
        bool bSuccess = _cap.read(original_frame);

        if (bSuccess)   //Check if the videocapture was able te retrieve a frame
        {
            if (original_frame.empty())
            {
                std::cout << "Couldn't read frame from video stream\n";
            }

            Mat marked_frame = original_frame;

            //Search for red corners
            vector<Point2d> cornerPoints;
            if (!_isRunning)
            {
                break;
            }
            marked_frame += _SearchColourBlob(original_frame, Scalar(cLowH, cLowS, cLowV), Scalar(cHighH, cHighS, cHighV), cornerPoints);

            //Search for a blue selection marker
            vector<Point2d> selectionPoints;
            marked_frame += _SearchColourBlob(original_frame, Scalar(sLowH, sLowS, sLowV), Scalar(sHighH, sHighS, sHighV), selectionPoints);

            // Process position data
            _HandleCorners(cornerPoints);
            if (selectionPoints.size() > 0)
            {
                _HandleSelection(selectionPoints[0]);
            }

            imshow("Marked", marked_frame);

        }
        else
        {
            cout << "Cannot read a frame from video stream\n";
        }
        
        //Sleep for a time to allow other threads to execute
        waitKey(1);
        this_thread::sleep_for(10ms);
    }

    // Release resources
    destroyAllWindows();
    _sbd.release();
}