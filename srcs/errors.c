/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:31:31 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 15:13:34 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_error(t_scene *scene, char *msg, char *line)
{
	free(line);
	error(scene, msg);
}

void	error(t_scene *scene, char *msg)
{
	printf("Error\n%s\n", msg);
	ft_exit(scene);
}

int		ft_exit(t_scene *scene)
{
	if (scene->player.z_buffer)
		free(scene->player.z_buffer);
	if (scene->map)
		free_map(scene);
	free_texture(scene);
	if (scene->sprites)
		free(scene->sprites);
	if (scene->win_ptr)
		mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	if (scene && scene->mlx_ptr)
		mlx_loop_end(scene->mlx_ptr);
	if (scene->mlx_ptr)
		mlx_destroy_display(scene->mlx_ptr);
	if (scene->mlx_ptr)
		free(scene->mlx_ptr);
	free(scene);
	exit(0);
	return (0);
}

void	free_texture(t_scene *scene)
{
	int	i;

	if (scene->north)
		free(scene->north);
	if (scene->south)
		free(scene->south);
	if (scene->east)
		free(scene->east);
	if (scene->west)
		free(scene->west);
	if (scene->sprite)
		free(scene->sprite);
	if (scene->texture)
	{
		i = 0;
		while (i < 5)
		{
			if (scene->texture[i].img)
				mlx_destroy_image(scene->mlx_ptr, scene->texture[i].img);
			i++;
		}
		free(scene->texture);
	}
}

void	free_map(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_map_lines)
	{
		free(scene->map[i]);
		i++;
	}
	free(scene->map);
}
