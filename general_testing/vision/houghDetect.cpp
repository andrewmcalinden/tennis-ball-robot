
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    VideoCapture cap(0);


    int height(1080);
    int width(1920);

    
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FOURCC, 0x21);
    cap.set(cv::CAP_PROP_FPS, 30);


    while(1){
        Mat src;
        cap.grab();
        cap.retrieve(src);
  
    //src = imread("images/view3.jpg");
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3,3));

    
    Canny(gray, gray, 110, 330, 3);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    
    dilate(gray, gray, kernel);

    kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(gray, gray, kernel);
    
    blur(gray, gray, Size(5,5));
    
    vector<Vec3f> circles;
    
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/4,  // change this value to detect circles with different distances to each other
                 110, 26, 5, 120 // change the last two parameters
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
    resize(gray,gray,Size(),.25,.25);
    imshow("detected circles", src);
    imshow("img view", gray);
    char c=(char)waitKey(1);
    if(c==27) break;
      
  }

    
}
