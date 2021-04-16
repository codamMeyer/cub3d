#include "bmp.h"
#include <fcntl.h>
#include <unistd.h>
#include <utils/defs.h>

static t_bmp_header	create_bmp_header(t_window window)
{
	const int		pixel_data_offset = 54;
	const int		bytes_per_pixel = 4;
	const uint32_t	bitmap_size =
		pixel_data_offset + (window.height * window.width * bytes_per_pixel);
	t_bmp_header	bmp_header;

	bmp_header.bitmap_signature_bytes[0] = 'B';
	bmp_header.bitmap_signature_bytes[1] = 'M';
	bmp_header.size_of_bitmap_file = bitmap_size;
	bmp_header.reserved_bytes = 0;
	bmp_header.pixel_data_offset = pixel_data_offset;
	return (bmp_header);
}

static t_bmp_info_header	create_bmp_info_header(t_window window)
{
	t_bmp_info_header	bmp_info_header;

	bmp_info_header.size_of_this_header = 40;
	bmp_info_header.width = window.width;
	bmp_info_header.height = window.height;
	bmp_info_header.number_of_color_planes = 1;
	bmp_info_header.color_depth = 32;
	bmp_info_header.compression_method = 0;
	bmp_info_header.raw_bitmap_data_size = 0;
	bmp_info_header.horizontal_resolution = 0;
	bmp_info_header.vertical_resolution = 0;
	bmp_info_header.color_table_entries = 0;
	bmp_info_header.important_colors = 0;
	return (bmp_info_header);
}

static void	write_bmp_pixels(const int fd, t_window window, void *image)
{
	const int	bytes_per_pixel = 4;
	const int	num_of_bytes_per_line = window.width * bytes_per_pixel;
	char		*write_ptr;

	write_ptr = (char *)image;
	write_ptr += num_of_bytes_per_line * (window.height - 1);
	while (write_ptr >= (char *)image)
	{
		write(fd, write_ptr, num_of_bytes_per_line);
		write_ptr -= num_of_bytes_per_line;
	}
}

static void	create_bmp_file(t_window window, void *image)
{
	const int				fd = open("image.bmp", \
								O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	const t_bmp_header		bmp_header = create_bmp_header(window);
	const t_bmp_info_header	bmp_info_header = create_bmp_info_header(window);

	if (fd < 0)
		return ;
	write(fd, (char *)&bmp_header, 14);
	write(fd, (char *)&bmp_info_header, 40);
	write_bmp_pixels(fd, window, image);
	close(fd);
	return ;
}

t_bool	save_image(t_window screen, void *address, t_bool save)
{
	static t_bool	image_saved = FALSE;

	if (!image_saved && save)
	{
		image_saved = TRUE;
		create_bmp_file(screen, address);
	}
	return (image_saved);
}
