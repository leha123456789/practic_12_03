#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;
void detectLines(Mat& color_dst, const Mat& dst, vector<Vec4i>& lines) 
{
    HoughLinesP(dst, lines, 1, CV_PI / 180, 80, 30, 10);
    for (size_t i = 0; i < lines.size(); i++) 
    {
        line(color_dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 200, 200), 3, 8);
    }
}

void detectCircles(Mat& img, const Mat& gray, vector<Vec3f>& circles) 
{
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);
    HoughCircles(gray, circles, HOUGH_GRADIENT, 2, gray.rows / 4, 200, 100);
    for (size_t i = 0; i < circles.size(); i++) 
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(img, center, radius, Scalar(0, 255, 0), 3, 8, 0);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    string imagePath = "C:/Users/jojoi/Desktop/gold.jpg";
    Mat src, dst, color_dst, gray, img;
    img = imread(imagePath, 1);
    imshow("pic", img);
    Canny(img, dst, 50, 200, 3);
    cvtColor(dst, color_dst, COLOR_GRAY2BGR);
    vector<Vec4i> lines;
    vector<Vec3f> circles;
    detectLines(color_dst, dst, lines);
    cvtColor(img, gray, COLOR_BGR2GRAY);
    detectCircles(img, gray, circles);  
    imshow("cer", img);
    imshow("line", color_dst);
    waitKey(0);
    return 0;
}