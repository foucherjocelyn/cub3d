/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:15:27 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 15:02:51 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(char *line, int *i)
{
	int	result;

	result = 0;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		result *= 10;
		result += line[*i] - '0';
		(*i)++;
	}
	return (result);
}

int	res_atoi(t_scene *scene, char *line)
{
	static int	is_resy = 0;
	static int	i = 1;
	int			result;

	result = 0;
	while (line[i] == ' ')
		i++;
	result = ft_atoi(line, &i);
	if (is_resy == 1 && line[i] != 0)
	{
		free(line);
		error(scene, "resolution is invalid");
	}
	is_resy = 1;
	return (result);
}

int	color_atoi(t_scene *scene, char *line, int *i)
{
	int			result;
	static int	call = 0;

	result = 0;
	call++;
	while (line[*i] == ' ')
		(*i)++;
	if (call > 1 && line[(*i)++] != ',')
	{
		free(line);
		error(scene, "invalid color");
	}
	while (line[*i] == ' ')
		(*i)++;
	result = ft_atoi(line, i);
	if ((call == 3 && line[*i]) || result < 0 || result > 255)
	{
		free(line);
		error(scene, "invalid color");
	}
	if (call == 3)
		call = 0;
	return (result);
}
