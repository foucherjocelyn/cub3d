/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@11.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1010/11/01 11:11:11 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/04 01:59:52 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	g_p;

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2)
		return (0);
	scene = malloc(sizeof(t_scene));
	scene->texture = malloc(sizeof(t_data) * 5);
	parsing(argv[1], scene);
	init(scene);
	scene->mlx_ptr = mlx_init();
	scene->win_ptr = mlx_new_window(scene->mlx_ptr,
	scene->r_width, scene->r_height, "cub3d");
	load_image(scene, &(scene->texture[0]), scene->north);
	load_image(scene, &(scene->texture[1]), scene->south);
	load_image(scene, &(scene->texture[2]), scene->west);
	load_image(scene, &(scene->texture[3]), scene->east);
	load_image(scene, &(scene->texture[4]), scene->sprite);
	mlx_loop_hook(scene->mlx_ptr, render, scene);
	mlx_hook(scene->win_ptr, 2, 1L << 0, key_press, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
