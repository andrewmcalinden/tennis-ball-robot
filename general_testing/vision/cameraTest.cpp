#include camera.h
#include <iostream>

using namespace std;

int main()
{
    Camera c(0);
    Mat frame;

    while (1)
    {
        frame = c.getFrame();
        imshow("image", frame);
        waitKey(0);
    }
}