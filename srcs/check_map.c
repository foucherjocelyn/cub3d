/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 00:50:28 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/10 19:42:10 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_scene *scene)
{
//	for(int i=0;i < scene->nb_map_lines;i++)
//		printf("%d : %s\n", i, scene->map[i]);
	count_players(scene);
	is_map_closed(scene);
}

void	count_players(t_scene *scene)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (charinstr("NSEW", scene->map[i][j]))
				count++;
			if (count > 1)
				error("more than 1 player");
			j++;
		}
		i++;
	}
	if (count == 0)
		error("player is missing");
}

void	is_map_closed(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (charinstr("02NSEW", scene->map[i][j]))
			{
				if (i == 0 || j == 0 || i == scene->nb_map_lines - 1 || j == ft_strlen(scene->map[i]) - 1)
					error("map not closed");
				else if (j >= ft_strlen(scene->map[i - 1]) || j >= ft_strlen(scene->map[i + 1]))
					error("map not closed");
				else
					are_space_around(scene, i, j);
			}
			j++;
		}
		i++;
	}
}

void	are_space_around(t_scene *scene, int i, int j)
{
	if (scene->map[i - 1][j] == ' ' || scene->map[i + 1][j] == ' ' || scene->map[i][j - 1] == ' ' || scene->map[i][j + 1] == ' ')
		error("map not closed");
}
