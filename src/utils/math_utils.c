#include <utils/angle_utils.h>
#include <utils/defs.h>
#include <utils/math_utils.h>

int min_i(int a, int b)
{
	return (a < b ? a : b);
}

int max_i(int a, int b)
{
	return (a > b ? a : b);
}

double min_d(double a, double b)
{
	return (a < b ? a : b);
}

double max_d(double a, double b)
{
	return (a > b ? a : b);
}

double abs_value(double value)
{
	if (value < 0.0)
		return (value * -1.0);
	return (value);
}
