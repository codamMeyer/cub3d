#include <utils/angle_utils.h>
#include <utils/defs.h>
#include <utils/math_utils.h>

int	min_i(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max_i(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double	min_d(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	abs_value(double value)
{
	if (value < 0.0)
		return (value * -1.0);
	return (value);
}
