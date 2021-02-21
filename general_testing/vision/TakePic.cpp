
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

    int count = 1;
    std::stringstream ss;
    std::string name;

    while(1){
        Mat src;
        cap.grab();
        cap.retrieve(src);
  
    //src = imread("images/view3.jpg");
    
    
    ss << "image_"<< to_string(count);
    name = ss.str();
    
    resize(src,src,Size(),.25,.25);
    
    imshow("Preview", src);

    char c=(char)waitKey(1);
    if(c==27) break;

    char d=(char)waitKey(1);
    if(d==32) {
        imwrite(name, src);
        ss << "image_"<< to_string(count);
        name = ss.str();
        ++count;
      
  }

    
}
