#ifndef DEFS_H
#define DEFS_H
#include <stdint.h>
#define INVALID -1
#define TRUE 1
#define FALSE 0

typedef int t_bool;

typedef struct s_color_rgba
{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t opacity;
} t_color_rgba;

typedef struct s_texture
{
	char filename[200];
	t_bool initialized;
	int width;
	int height;
	int bit_per_pixel;
	int line_size;
	void *ptr;
	char *data;
} t_texture;

typedef enum e_collider
{
	EMPTY,
	WALL,
	SPRITE
} t_collider;

typedef enum e_texture
{
	INVALID_TEXTURE = -1,
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	SP = 4,
} t_texture_enum;

typedef enum e_player_orientation
{
	INVALID_ORIENTATION = -1,
	N = 90,
	S = 270,
	W = 180,
	E = 0,
} t_player_orientation;

typedef enum e_orientation
{
	VERTICAL,
	HORIZONTAL
} t_orientation;

typedef struct s_position
{
	double x;
	double y;
} t_position;

typedef struct s_grid_position
{
	int x;
	int y;
} t_grid_position;

typedef struct s_texture_position
{
	int x;
	int y;
} t_texture_position;

typedef struct s_ray
{
	t_position pos;
	double distance;
	double angle;
	t_orientation orientation;
} t_ray;

typedef struct s_dimensions
{
	int real_height;
	int height;
	int real_width;
	int width;
	int top;
	int real_top;
	int bottom;
} t_dimensions;

typedef struct s_img
{
	void *mlx;
	void *window;
	void *ptr;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int color;
} t_img;

typedef struct s_map
{
	int width;
	int height;
	int **matrix;
} t_map;

#endif