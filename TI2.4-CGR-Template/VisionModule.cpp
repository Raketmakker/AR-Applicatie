#define _USE_MATH_DEFINES
#include "VisionModule.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <map>
#include <vector>

constexpr auto KEYCODE_SPACE = 32;
constexpr auto MARKER_SIZE = 25;

using namespace cv;
using namespace std;
using namespace chrono_literals;

int Min_Area = 1, Max_Area = 100000;

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

VisionModule::VisionModule():
    _gridWidth(-1), _gridHeigth(-1), _gridStart(Point2d(-1, -1)), _isRunning(false), _lastPoint(Point2d(-1,-1)), _isDone(true)
{
    _cap = cv::VideoCapture(2);  // 0 = Webcam, for the daheng camera increase the number by one until you find it

    if (_cap.isOpened())
    {
        _cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
        _cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
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

Point2d VisionModule::GetSelectionPos()
{
    return _lastPoint;

    /*if (_points.empty())
    {
        return Point2d(-1, -1);
    }

    map<int, int> occurringpoints;

    for (Point2d point : _points)
    {
        int pointValue = point.x + (point.y * 100);
        std::map<int, int>::iterator it = occurringpoints.find(pointValue);

        if (it == occurringpoints.end())
        {
            occurringpoints.insert(pair<int, int>(pointValue, 0));
        }
        else 
        {
            it->second = it->second + 1;
        }
    }

    int mostFrequentPoint = -101;
    int mostFrequenPointAmount = 0;

    for (auto const& pair : occurringpoints)
    {
        if (pair.second > mostFrequenPointAmount)
        {
            mostFrequenPointAmount = pair.second;
            mostFrequentPoint = pair.first;
        }
    }
    return Point2d(mostFrequentPoint%100, mostFrequentPoint/100);*/
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
    

    // Mark the found blobs
    Mat marker = Mat::zeros(sourceImage.size(), CV_8UC3);;
    for (auto keypoint : keypoints)
    {
        float x = keypoint.pt.x;
        float y = keypoint.pt.y;

        line(marker, Point(x - MARKER_SIZE, y - MARKER_SIZE), Point(x + MARKER_SIZE, y + MARKER_SIZE), Scalar(255, 0, 0), 2);
        line(marker, Point(x + MARKER_SIZE, y - MARKER_SIZE), Point(x - MARKER_SIZE, y + MARKER_SIZE), Scalar(255, 0, 0), 2);

        blobs.push_back(Point(x, y));
    }

    return marker;
}

bool VisionModule::_HandleCorners(vector<Point2d>& corners)
{
    if (corners.size() != 2)    // Check if 4 corners are present
    {
        cout << "Invalid amount of corners\n";
        return false;
    }

    Point2d topLeft;
    Point2d bottomRight;

    if (corners[0].x < corners[1].x)
    {
        topLeft = corners[0];
        bottomRight = corners[1];
    }
    else 
    {
        topLeft = corners[1];
        bottomRight = corners[0];
    }

    //Calculate the distane between the 2 points
    _gridDiameter = sqrt(pow(bottomRight.x - topLeft.x, 2) + pow(bottomRight.y - topLeft.y, 2));

    _gridWidth = sin(45.0 * (M_PI / 180.0)) * _gridDiameter;
    _gridHeigth = cos(45.0 * (M_PI / 180.0)) * _gridDiameter;
    _gridStart = topLeft;
    _gridEnd = bottomRight;

    return true;
}

bool VisionModule::_HandleSelection(vector<Point2d>& selections)
{
    if (selections.size() != 1)
    {
        cout << "Invalid amount of selections\n";
        return false;
    }

    Point2d selection = selections.front();

    //Calculate other 2 points
    double xc = (_gridStart.x + _gridEnd.x) / 2; double yc = (_gridStart.y + _gridEnd.y) / 2;    // Center point of grid
    double xd = (_gridStart.x - _gridEnd.x) / 2; double yd = (_gridStart.y - _gridEnd.y) / 2;    // Half-diagonal from bottom left to top right

    double x3 = xc - yd;  double y3 = yc + xd;    // Top right
    double x4 = xc + yd;  double y4 = yc - xd;    // Bottom left
    
    //Calculate angles
    double angle1 = atan((_gridStart.y - y4) / (_gridStart.x -x4)) * (180 / M_PI);                      //Calculate angle from point
    double angle2 = atan((selection.y - _gridStart.y) / (selection.x - _gridStart.x)) * (180 / M_PI);   //Calculate angle from selection
    double angle3 = angle1 - angle2;

    //cout << "Angle 1: " << angle1 << " Angle 2: " << angle2 << " Angle 3: " << angle3 << "\n";

    //Calculate difference between top left and selection
    double distance = sqrt(pow(selection.x - _gridStart.x, 2) + pow(selection.y - _gridStart.y, 2));

    //Calculate the x and y values as a 10x10 grid
    int selectionX = abs((sin(angle3 * (M_PI / 180.0)) * distance) / (_gridWidth / 10));
    int selectionY = abs((cos(angle3 * (M_PI / 180.0)) * distance) / (_gridHeigth / 10));

    //cout << selectionX << "," << selectionY << "\n";

    if (selectionX < 0 || selectionX > 9 || selectionY < 0 || selectionY > 9)
    {
        cout << "Selection out of bounds\n";
        return false;
    }

    _lastPoint = Point2d(selectionX, selectionY);

    return true;
}

void VisionModule::_VisionThread()
{
    _sbd = SimpleBlobDetector::create();
    _isDone = false;

    //namedWindow("Corner Control");
    //createTrackbar("LowH", "Corner Control", &cLowH, 255); //Hue (0 - 255)
    //createTrackbar("HighH", "Corner Control", &cHighH, 255);
    //createTrackbar("LowS", "Corner Control", &cLowS, 255); //Saturation (0 - 255)
    //createTrackbar("HighS", "Corner Control", &cHighS, 255);
    //createTrackbar("LowV", "Corner Control", &cLowV, 255);//Value (0 - 255)
    //createTrackbar("HighV", "Corner Control", &cHighV, 255);

    //namedWindow("Selection Control");
    //createTrackbar("LowH", "Selection Control", &sLowH, 255); //Hue (0 - 255)
    //createTrackbar("HighH", "Selection Control", &sHighH, 255);
    //createTrackbar("LowS", "Selection Control", &sLowS, 255); //Saturation (0 - 255)
    //createTrackbar("HighS", "Selection Control", &sHighS, 255);
    //createTrackbar("LowV", "Selection Control", &sLowV, 255);//Value (0 - 255)
    //createTrackbar("HighV", "Selection Control", &sHighV, 255);

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
            marked_frame += _SearchColourBlob(original_frame, Scalar(cLowH, cLowS, cLowV), Scalar(cHighH, cHighS, cHighV), cornerPoints);

            //Search for a blue selection marker
            vector<Point2d> selectionPoints;
            marked_frame += _SearchColourBlob(original_frame, Scalar(sLowH, sLowS, sLowV), Scalar(sHighH, sHighS, sHighV), selectionPoints);

            // Process position data
            _HandleCorners(cornerPoints);
            _HandleSelection(selectionPoints);

            imshow("Marked", marked_frame);

        }
        else
        {
            cout << "Cannot read a frame from video stream\n";
        }
        
        //Sleep for a time to allow other threads time
        waitKey(1);
        this_thread::sleep_for(1ms);
    }

    // Release resources
    destroyAllWindows();
    _sbd.release();
    _mtx.lock();
    _isDone = true;
    _mtx.unlock();
}

bool VisionModule::IsThreadDone()
{
    _mtx.lock();
    bool isDone = _isDone;
    _mtx.unlock();
    return isDone;
}
