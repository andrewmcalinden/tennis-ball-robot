#include <iostream>
#include <cmath>
int main()
{
    double initialX = 2;
    double initialY = 1;
    double initialHeadingRad = (M_PI / 180.0) * -45.0;

    //flipped because if you actually draw the triangle it works out
    double additionalX = 20 * sin(initialHeadingRad);
    double additionalY = 20 * cos(initialHeadingRad);

    double finalX = initialX + additionalX;
    double finalY = initialY + additionalY;
    std::cout << "finalX: " << finalX << "\nfinalY: " << finalY;
}