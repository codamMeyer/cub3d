#ifndef RENDER_H
#define RENDER_H
#include <game/game.h>
#include <player/player.h>
#include <utils/defs.h>

void draw_slice(t_data *data, int slice_col, t_ray *ray);
t_color_rgba get_pixel_color(const t_texture *texture, int x, int y);
t_dimensions get_dimensions(double dist_to_wall, t_player player, t_window screen);
t_color_rgba apply_shading(double distance, t_color_rgba color, double min_dist);
#endif