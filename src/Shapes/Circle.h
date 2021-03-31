#include <IK.h>

bool testCircle(float x1, float y1, bool clockwise, float section, float r, double iterations);
bool testPartialCircle(float x1, float y1, bool clockwise, float section, float r, double iterations, double beginangle);

void drawCircle(float x1, float y1, bool clockwise, float section, float r);
void drawPartialCircle(float x1, float y1, bool clockwise, float section, float x0, float y0);