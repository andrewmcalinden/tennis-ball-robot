
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    VideoCapture cap(0);

    while(1){
        Mat src;
        cap.grab();
        cap.retrieve(src);
  
    //src = imread("images/view3.jpg");
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 3);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    dialate(gray, gray, kernel);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    erode(gray, gray, kernel);
    Canny(gray, gray, 1, 3, 3);
    medianBlur(gray, gray, 15);
    
    vector<Vec3f> circles;
    imshow("detected circles", src);
    HoughCircles(gray, circles, HOUGH_GRADIENT, .8,
                 gray.rows/128,  // change this value to detect circles with different distances to each other
                 80, 30, 10, 40 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }
    resize(src,src,Size(),.25,.25);
    imshow("detected circles", src);
    waitKey(17);
    
}
}