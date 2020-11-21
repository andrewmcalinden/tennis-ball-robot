class MotorPowers
{
    private:
    double lPower;
    double rPower;

    public:
    MotorPowers(double wantedLPower, double wantedRPower);
    double getLPower();
    double getRPower();
    void setLPower(double power);
    void setRPower(double power);
}