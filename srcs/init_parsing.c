/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:31:33 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/09 20:09:36 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parsing(t_scene *scene)
{
	scene->r_width = 0;
	scene->r_height = 0;
	scene->north = 0;
	scene->south = 0;
	scene->west = 0;
	scene->east = 0;
	scene->sprite = 0;
	scene->floor = -1;
	scene->ceiling = -1;
}
