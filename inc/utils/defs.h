#ifndef DEFS_H
#define DEFS_H

#define INVALID -1
#define TRUE 1
#define FALSE 0
#define BLACK 0xff000000
#define PI 3.14159265358979323846

// X11 events
#define KEY_PRESS_EVENT 2
#define CLIENT_MESSAGE_EVENT 33
#define KEY_PRESS_MASK (1L << 0)
#define STRUCT_NOTIFY_MASK (1L << 17)

typedef int t_bool;
typedef unsigned int t_color;

typedef struct s_texture
{
	char filename[200];
	t_bool initialized;
	int width;
	int height;
	void *ptr;
	char *data;
} t_texture;

typedef struct s_window
{
	int width;
	int height;
} t_window;

typedef enum e_collider
{
	EMPTY,
	WALL,
	SPRITE
} t_collider;

// typedef struct s_color_rgb
// {
// 	unsigned char blue;
// 	unsigned char green;
// 	unsigned char red;
// 	unsigned char oppacity;

// } t_color_rgb;

typedef enum e_status
{
	SUCCESS = 0,
	FILE_ERROR,
	EXTENSION_ERROR,
	RESOLUTION_ERROR,
	TEXTURE_INFO_ERROR,
	COLOR_ERROR,
	MISSING_MAP_ERROR,
	MAP_CONTENT_ERROR,
	MAP_NOT_SURROUNDED_ERROR,
	PLAYER_INIT_ERROR,
	LOAD_ERROR,
	MALLOC_ERROR,
	ARG_ERROR,
	INIT_WINDOW_ERROR,
} t_status;

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

typedef struct s_dimentions
{
	int real_height;
	int height;
	int width;
	int top;
	int real_top;
	int bottom;
} t_dimentions;

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

typedef struct s_player
{
	t_position position;
	int FOV;
	double angle;
	int speed;
} t_player;

typedef struct s_map
{
	int width;
	int height;
	int **matrix;
} t_map;

typedef struct s_data
{
	t_window screen;
	t_img img;
	t_map worldMap;
	t_player player;
	t_texture textures[5];
	t_color floor;
	t_color ceiling;
	t_bool save;
} t_data;

#endif