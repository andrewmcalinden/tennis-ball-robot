class Vector
{
    private:
    double x;
    double y;
    double magnitude;
    double angle; //in radians

    public:
    Vector(double hor, double vert);
    Vector(double mag, double angDeg);
    double getX();
    double getY();
    double getMagnitude();
    double getAngle();
    Vector rotated(double angle);
};