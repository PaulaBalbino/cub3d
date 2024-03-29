/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:28:23 by pbalbino        #+#    #+#             */
/*   Updated: 2023/09/05 15:35:12 by m_kamal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	map_scale_factor(t_data *data)
{
	float factor;

	factor = 0.15;
	while ((data->map_num_rows * 64 * factor > WINDOW_HEIGHT / 4) || (data->map_num_cols * 64 * factor > WINDOW_WIDTH / 4))
		factor -= 0.01;
	return factor;
}

bool	is_wall_at(t_data *data, float x, float y)
{
	int	map_grid_x;
	int	map_grid_y;

	//if (!is_inside_map(data, x, y))
	//	return (true);
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	//return (data->map[map_grid_y][map_grid_x] == '1'
	//	|| data->map[map_grid_y][map_grid_x] == ' ');
	if (map_grid_x < 0 || map_grid_x >= data->map->x_max || map_grid_y < 0 || map_grid_y >= data->map->rows)
		return (true);
	if (data->map->grid[map_grid_y][map_grid_x].type == WALL) // if we consider spaces as wall we need to add this condition here;
		return (true);
	return (false);
}

void	render_map(t_data *data)
{
	t_rect	rect;
	int		i;
	int		j;

	i = -1;
	while (++i < data->map_num_rows)
	{
		j = -1;
		while (++j < data->map_num_cols)
		{
			rect.x = (j * TILE_SIZE) * data->mini_map_scale;
			rect.y = (i * TILE_SIZE) * data->mini_map_scale;
			rect.height = TILE_SIZE * data->mini_map_scale;
			rect.width = TILE_SIZE * data->mini_map_scale;
			if (data->map->grid[i][j].type == WALL)
			//if (data->map[i][j] == '1')
				rect.color = WHITE_OLD;
			else
				rect.color = 0x0;
			draw_rect(data, rect);
		}
	}
}

bool	is_inside_map(t_data *data, float x, float y)
{
	return (x >= 0 && x < data->map_num_cols * TILE_SIZE && y >= 0
		&& y < data->map_num_rows * TILE_SIZE);
}
