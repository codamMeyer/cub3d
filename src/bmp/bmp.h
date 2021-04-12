#ifndef BMP_H
# define BMP_H
# include <game/game.h>
# include <stdint.h>
# include <utils/defs.h>

typedef struct s_pixel
{
	uint8_t	blue;
	uint8_t	green;
	uint8_t	red;
}	t_pixel;

/* __attribute__((__packed__)) is to guarantee that no padding
will be added to the struct, so the struct has only 14 bytes */
typedef struct __attribute__((__packed__)) s_bmp_header
{
	char		bitmap_signature_bytes[2];
	uint32_t	size_of_bitmap_file;
	uint32_t	reserved_bytes;
	uint32_t	pixel_data_offset;
}	t_bmp_header;

/* __attribute__((__packed__)) is to guarantee that no padding
will be added to the struct, so the struct has only 40 bytes */
typedef struct __attribute__((__packed__)) s_bmp_info_header
{
	uint32_t	size_of_this_header;
	int32_t		width;
	int32_t		height;
	uint16_t	number_of_color_planes;
	uint16_t	color_depth;
	uint32_t	compression_method;
	uint32_t	raw_bitmap_data_size;
	int32_t		horizontal_resolution;
	int32_t		vertical_resolution;
	uint32_t	color_table_entries;
	uint32_t	important_colors;
}	t_bmp_info_header;

unsigned int		get_size_of_bitmap_file(t_window window, \
											const int pixel_data_offset);
t_bmp_header		create_bmp_header(t_window window);
t_bmp_info_header	create_bmp_info_header(t_window window);
void				create_bmp_file(t_window window, void *image);
void				save_image(t_window screen, void *address, t_bool save);

#endif