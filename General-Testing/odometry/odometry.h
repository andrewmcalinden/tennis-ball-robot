void updateLeftEncoder(double reading);
void updateRightEncoder(double reading);

void setPose(double x, double y, double theta); //theta in degrees
void updatePos(double leftReading, double rightReading);

bool epsilonEquals();

double getX();
double getY();
double getHeading(); //in degrees

double getTotalDist();

extern double globalXPos = 0;
extern double globalYPos = 0;
extern double globalHeading = 0; //in degrees, from -180 to 180
