/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:17:24 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/18 22:24:47 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_scene *scene)
{
	int	size_x;
	int	size_y;

	check_map(scene);
	scene->player.move_speed = 0.2;
	scene->player.rot_speed = 0.1;
	find_player(scene);
	find_sprite(scene);
	mlx_get_screen_size(scene->mlx_ptr, &size_x, &size_y);
	if (size_x < scene->r_width)
		scene->r_width = size_x;
	if (size_y < scene->r_height)
		scene->r_height = size_y;
	if (!(scene->player.z_buffer = malloc(sizeof(double) * scene->r_width)))
		error("malloc error");
}

void	find_dir(t_scene *scene, char player)
{
	scene->player.dir_x = 0;
	scene->player.dir_y = -1;
	scene->player.plane_x = 0.66;
	scene->player.plane_y = 0;
	if (player == 'S')
	{
		scene->player.dir_x = 0;
		scene->player.dir_y = 1;
		scene->player.plane_x = -0.66;
		scene->player.plane_y = 0;
	}
	if (player == 'E')
	{
		scene->player.dir_x = 1;
		scene->player.dir_y = 0;
		scene->player.plane_x = 0;
		scene->player.plane_y = 0.66;
	}
	if (player == 'W')
	{
		scene->player.dir_x = -1;
		scene->player.dir_y = 0;
		scene->player.plane_x = 0;
		scene->player.plane_y = -0.66;
	}
}

void	find_player(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (charinstr("NSEW", scene->map[i][j]))
			{
				scene->player.pos_x = j + 0.5;
				scene->player.pos_y = i + 0.5;
				find_dir(scene, scene->map[i][j]);
				scene->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	count_sprite(t_scene *scene)
{
	int	i;
	int j;

	i = 0;
	scene->nb_sprites = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (scene->map[i][j] == '2')
				scene->nb_sprites++;
			j++;
		}
		i++;
	}
}

void	find_sprite(t_scene *scene)
{
	int	i;
	int	j;
	int	k;

	count_sprite(scene);
	if (!(scene->sprites = malloc(sizeof(t_sprite) * scene->nb_sprites)))
		error("malloc error");
	i = 0;
	k = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (scene->map[i][j] == '2')
			{
				scene->sprites[k].y = i + 0.5;
				scene->sprites[k].x = j + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}
