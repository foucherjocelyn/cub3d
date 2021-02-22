/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@11.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1010/11/01 11:11:11 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/22 13:50:23 by jfoucher         ###   ########.fr       */
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
	g_ptr.mlx = mlx_init();
	g_ptr.win = mlx_new_window(g_ptr.mlx, scene->r_width, scene->r_height, "cub3d");
	load_image(&(scene->texture[0]), scene->north);
	load_image(&(scene->texture[1]), scene->south);
	load_image(&(scene->texture[2]), scene->west);
	load_image(&(scene->texture[3]), scene->east);
	load_image(&(scene->texture[4]), scene->sprite);
	for (int i=0; i<scene->nb_map_lines; i++)
		printf("%s\n", scene->map[i]);
	render(scene);
	mlx_hook(g_ptr.win, 2, 1L << 0, key_press, scene);
	mlx_loop_hook(g_ptr.mlx, render, scene);
	mlx_loop(g_ptr.mlx);
	return(0);
}
