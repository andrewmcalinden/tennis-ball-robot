void updateLeftEncoder(double reading);
void updateRightEncoder(double reading);

void updatePos(double leftReading, double rightReading);

double angleWrap(double angle);

bool epsilonEquals();

double getX();
double getY();
double getHeading();
