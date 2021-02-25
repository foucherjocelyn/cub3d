/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:25:24 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/25 17:41:10 by jfoucher         ###   ########.fr       */
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
	(void)line;
	scene->nb_map_lines += 1;
}

void	parse_map(char *file, t_scene *scene)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	i = 0;
	scene->map = malloc(sizeof(char*) * scene->nb_map_lines);
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == ' ' || line[0] == '1')
		{
			scene->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	free(line);
	close(fd);
}
