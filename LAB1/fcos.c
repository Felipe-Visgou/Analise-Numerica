#include <math.h>
#define PI 3.141592653589793
double fcos(double x)
{
	return -((PI - 2.0*x)*(PI*PI - 4.0*PI*x - 24.0 + 4.0*x*x))/48.0;
}
double residuo(double x)
{
	double y = x - PI/2.0;
	return -1.0/120.0 * (y*y*y*y*y);
}
