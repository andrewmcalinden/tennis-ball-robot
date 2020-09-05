class Vector
{
    private:
    double x;
    double y;

    public:
    Vector(double hor, double vert);
    double getX();
    double getY();
    Vector rotated(double angle);
};