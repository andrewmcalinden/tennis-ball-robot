
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    VideoCapture cap(0);


    int height(720);
    int width(1280);

    
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    //cap.set(cv::CAP_PROP_FOURCC, 0x21);
    cap.set(cv::CAP_PROP_FPS, 48);

    int count = 59;
    std::stringstream ss;
    std::string name;
    Mat src, previewPic;

    name = ss.str();
    while(1){
        
        cap.grab();
        cap.retrieve(src);
  
    //src = imread("images/view3.jpg");
    
    
    
    
    
    resize(src,previewPic,Size(),1.5,1.5);
    
    imshow("Preview", previewPic);
    int d = waitKey(1);
    
    if(d==27) break;

    
    if(d==' ') {
        ss << "image_"<< to_string(count) << ".png";
        name = ss.str();
        imwrite(name, src);
        ss.str("");
        ++count;
      
        }
    }
}

    

