#ifndef DEFS_H
#define DEFS_H

#define INVALID -1
#define TRUE 1
#define FALSE 0
// COLORS
#define RED 0x0096000f
#define DARK_RED 0x0075040f
#define YELLOW 0x00FFFF00
#define GREEN 0xaa55aa00
#define DARK_GREEN 0xaa005500
#define BLUE 0xFF7580FF
#define WHITE 0x00FFFFFF
#define BLACK 0xFF000000
#define DARK_BLUE 0x00233f58
#define DARK_BROWN 0x002C1F0E
#define SKY_COLOR 0x0013180F

#define PI 3.14159265358979323846

typedef int t_bool;

typedef struct s_texture
{
	t_bool initialized;
	int width;
	int height;
	void *ptr;
	char *data;
} t_texture;

typedef enum e_collider
{
	EMPTY,
	WALL,
	SPRITE
} t_collider;

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

typedef struct s_dimentions
{
	int height;
	int width;
	int top;
	int bottom;
} t_dimentions;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int color;
} t_img;

typedef struct s_player
{
	t_position position;
	int FOV;
	int plane_x;
	int plane_y;
	double angle;
	int size;
	int speed;
	int color;
} t_player;

typedef struct s_map
{
	int width;
	int height;
	int **matrix;
} t_map;

typedef struct s_data
{
	void *mlx;
	void *window;
	int screenWidth;
	int screenHeight;
	t_img map;
	t_map worldMap;
	t_player player;
	t_texture texture[5];
} t_data;

#endif