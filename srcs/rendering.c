/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:11:12 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/25 21:04:51 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		render(t_scene *scene)
{
	t_data		img;
	t_ray_var	var;
	int			x;

	x = 0;
	scene->sprite_order = malloc(sizeof(int) * scene->nb_sprites);
	scene->sprite_distance = malloc(sizeof(double) * scene->nb_sprites);
	img.img = mlx_new_image(scene->mlx_ptr, scene->r_width, scene->r_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	&img.line_length, &img.endian);
	while (x < scene->r_width)
	{
		ray_casting(scene, &var, x);
		draw_wall(scene, &var, &img, x);
		x++;
	}
	sprite_casting(scene, &img);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, img.img, 0, 0);
	mlx_destroy_image(scene->mlx_ptr, img.img);
	free(scene->sprite_order);
	free(scene->sprite_distance);
	return (0);
}

void	load_image(t_scene *scene, t_data *img, char *path)
{
	img->img = mlx_xpm_file_to_image(scene->mlx_ptr, path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
	&(img->line_length), &(img->endian));
}
