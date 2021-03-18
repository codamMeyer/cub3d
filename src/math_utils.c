#include <defs.h>
#include <math_utils.h>

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

t_grid_position to_grid_position(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = {.x = pos.x / GRID_SIZE, .y = pos.y / GRID_SIZE};
	if(grid_pos.x >= worldMap.width || grid_pos.y >= worldMap.height)
	{
		grid_pos.x = INVALID;
		grid_pos.y = INVALID;
	}
	return (grid_pos);
}

double degree_to_radians(double degree)
{
	return (degree * PI / 180.0);
}

double abs_value(double value)
{
	if(value < 0.0)
		return (value * -1.0);
	return (value);
}

double fix_angle(double angle)
{
	if(angle > 359)
		angle -= 360;
	if(angle < 0)
		angle += 360;
	return angle;
}