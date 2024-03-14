/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:19:19 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/22 23:13:12 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	initialize_wall(t_data *data, t_wall *wall, int x)
{
	wall->projected_wall_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	wall->corrected_ray_distance = data->rays[x].distance
		* cos(data->player->rotation_angle - data->rays[x].angle);
	wall->projected_wall_height = (int)((TILE_SIZE
				/ wall->corrected_ray_distance * wall->projected_wall_dist));
	wall->top_pixel = (WINDOW_HEIGHT / 2) - (wall->projected_wall_height / 2);
	wall->bottom_pixel = (WINDOW_HEIGHT / 2) + (wall->projected_wall_height
			/ 2);
	if (wall->top_pixel < 0)
		wall->top_pixel = 0;
	if (wall->bottom_pixel > WINDOW_HEIGHT)
		wall->bottom_pixel = WINDOW_HEIGHT;
	if (data->rays[x].is_up)
		wall->x_texture_offset = (int)data->rays[x].hit_y % TILE_SIZE;
	else
		wall->x_texture_offset = (int)data->rays[x].hit_x % TILE_SIZE;
}

t_wall	set_wall_orientation(const t_data *data, t_wall *wall, int x)
{
	if (data->rays[x].is_up == false
		&& data->rays[x].direction.is_up)
		(*wall).orientation = 1;
	else if (data->rays[x].is_up == false
		&& data->rays[x].direction.is_down)
		(*wall).orientation = 0;
	else if (data->rays[x].is_up
		&& data->rays[x].direction.is_left)
		(*wall).orientation = 3;
	else if (data->rays[x].is_up
		&& data->rays[x].direction.is_right)
		(*wall).orientation = 2;
	return (*wall);
}

void	draw_wall(t_data *data, t_wall wall, int x)
{
	int	y;

	wall.orientation = 0;
	y = wall.top_pixel - 1;
	while (++y < wall.bottom_pixel)
	{
		wall.distance_from_top = y
			+ (wall.projected_wall_height / 2) - (WINDOW_HEIGHT / 2);
		wall.y_texture_offset = wall.distance_from_top * ((float)TILE_SIZE
				/ wall.projected_wall_height);
		wall = set_wall_orientation(data, &wall, x);
		wall.texel_color = get_texture_color
			(data->map->textures[wall.orientation]->texture_img,
				wall.x_texture_offset, wall.y_texture_offset);
		pixel_get(data->map->textures[wall.orientation]->texture_img,
			wall.x_texture_offset, wall.y_texture_offset);
		data->game_color_buffer[(WINDOW_WIDTH * y) + x] = wall.texel_color;
	}
}

void	render_walls(t_data *cub3d)
{
	int		ray_count;
	t_wall	wall;

	ray_count = 0;
	while (ray_count < WINDOW_WIDTH)
	{
		initialize_wall(cub3d, &wall, ray_count);
		draw_ceiling(cub3d, wall, ray_count);
		draw_wall(cub3d, wall, ray_count);
		draw_floor(cub3d, wall, ray_count);
		ray_count++;
	}
}
