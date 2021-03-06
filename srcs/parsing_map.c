/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:25:24 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 03:09:37 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		charinstr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	count_map_lines(t_scene *scene, char *line)
{
	int	i;

	i = 0;
	if (!scene->r_width || !scene->r_height || !scene->north || !scene->south
			|| !scene->west || !scene->east || !scene->sprite
			|| scene->floor == -1 || scene->ceiling == -1)
	{
		free(line);
		error(scene, "element missing or invalid");
	}
	while (line[i])
		if (!(charinstr(" 012NSEW", line[i++])))
			error(scene, "invalid char in map");
	scene->nb_map_lines += 1;
}

void	parse_map(char *file, t_scene *scene)
{
	char	*line;
	int		fd;
	int		i;

	if (scene->nb_map_lines <= 0)
		error(scene, "map missing");
	fd = open(file, O_RDONLY);
	i = 0;
	if (!(scene->map = malloc(sizeof(char*) * scene->nb_map_lines)))
		error(scene, "malloc error");
	while (get_next_line(fd, &line) == 1 && line[0] != '1' && line[0] != ' ')
		free(line);
	scene->map[i] = ft_strdup(line);
	i++;
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		scene->map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	free(line);
	close(fd);
}
