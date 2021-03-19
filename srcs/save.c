/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 01:42:46 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 02:56:28 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bmp_header(t_scene *scene, t_data *img, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 54 + 4 * scene->r_width * scene->r_height;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &(scene->r_width), 4);
	write(fd, &(scene->r_height), 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &(img->bits_per_pixel), 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	save_bmp(t_scene *scene, t_data *img)
{
	int	fd;
	int	x;
	int	y;

	fd = open("./save.bmp", O_CREAT | O_RDWR);
	bmp_header(scene, img, fd);
	y = scene->r_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < scene->r_width)
		{
			write(fd, img->addr + (y * img->line_length + x *
						(img->bits_per_pixel / 8)), 4);
			x++;
		}
		y--;
	}
	close(fd);
	mlx_destroy_image(scene->mlx_ptr, img->img);
	ft_exit(scene);
}
