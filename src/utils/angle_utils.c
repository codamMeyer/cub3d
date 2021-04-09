#include "angle_utils.h"
#include "map_utils.h"
#include <math.h>

double degree_to_radians(double degree)
{
	return (degree * M_PI / 180.0);
}

double fix_angle(double angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return angle;
}
