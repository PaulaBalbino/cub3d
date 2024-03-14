/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:12:51 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:14:32 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	map_error(void *pointer);

void	write_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_error(void *pointer, int code)
{
	if (code == MALLOC_ERR)
	{
		write_err(RED);
		write_err("Error:\n Malloc error.\n");
		write_err(RESET);
		exit(1);
	}
	else if (code == ARGS_ERR)
	{
		write_err(RED);
		write_err("Error:\n Wrong map path or arguments.\n");
		write_err(RESET);
		exit(0);
	}
	else if (code == MAP_ERR)
		map_error(pointer);
	else if (code == EXIT)
		exit_window(pointer);
}

static void	map_error(void *pointer)
{
	t_data	*cub3d;

	cub3d = (t_data *)pointer;
	write_err(RED);
	write_err("Error:\n Invalid map.\n");
	write_err(RESET);
	free_all(cub3d);
	exit(0);
}
