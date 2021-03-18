/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@11.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1010/11/01 11:11:11 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/18 22:52:42 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2 || argc > 3)
		error("invalid arguments");
	if (ft_strlen(argv[1]) < 5 || !ft_str_at_end(argv[1], ".cub") ||
			(argc == 3 && (ft_strlen(argv[2]) != 6 ||
					(!ft_str_at_end(argv[2], "--save")))))
		error("invalid arguments");
	if (!(scene = malloc(sizeof(t_scene))))
		error("malloc error");
	scene->mlx_ptr = mlx_init();
	if (!(scene->texture = malloc(sizeof(t_data) * 5)))
		error("malloc error");
	parsing(argv[1], scene);
	init(scene);
	scene->win_ptr = mlx_new_window(scene->mlx_ptr,
			scene->r_width, scene->r_height, "cub3d");
	call_load(scene);
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
		render(scene, 1);
	mlx_loop_hook(scene->mlx_ptr, render, scene);
	mlx_hook(scene->win_ptr, 33, 1L << 17, ft_exit, 0);
	mlx_hook(scene->win_ptr, 2, 1L << 0, key_press, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}

void	call_load(t_scene *scene)
{
	load_image(scene, &(scene->texture[0]), scene->north);
	load_image(scene, &(scene->texture[1]), scene->south);
	load_image(scene, &(scene->texture[2]), scene->west);
	load_image(scene, &(scene->texture[3]), scene->east);
	load_image(scene, &(scene->texture[4]), scene->sprite);
	scene->t_color = *(unsigned int*)scene->texture[4].addr;
}
