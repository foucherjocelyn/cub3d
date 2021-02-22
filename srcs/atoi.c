/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:15:27 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/22 12:43:53 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	res_atoi(char *line)
{
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
	return (result);
}

int	color_atoi(char *line, int *i)
{
	int			result;

	result = 0;
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		result *= 10;
		result += line[*i] - '0';
		(*i)++;
	}
	return (result);
}

