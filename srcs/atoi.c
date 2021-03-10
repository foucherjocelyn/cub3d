/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:15:27 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/09 19:11:38 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	res_atoi(char *line)
{
	static int	is_resy = 0;
	static int	i = 1;
	int			result;

	result = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		result *= 10;
		result += line[i] - '0';
		i++;
	}
	if (is_resy == 1 && line[i] != 0)
		error("resolution is invalid");
	is_resy = 1;
	return (result);
}

int	color_atoi(char *line, int *i)
{
	int			result;
	static int	call = 0;

	result = 0;
	call++;
	while (line[*i] == ' ')
		(*i)++;
	if (call > 1 && line[(*i)++] != ',')
		error("invalid color");
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		result *= 10;
		result += line[*i] - '0';
		(*i)++;
	}
	if ((call == 3 && line[*i]) || result < 0 || result > 255)
		error("invalid color");
	if (call == 3)
		call = 0;
	return (result);
}
