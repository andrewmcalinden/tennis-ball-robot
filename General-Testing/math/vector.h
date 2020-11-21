class Vector
{
    private:
    double x;
    double y;
    double magnitude;
    double angle;

    public:
    Vector(double hor, double vert);
    double getX();
    double getY();
    double getMagnitude();
    double getAngle();
    Vector rotated(double angle);
};