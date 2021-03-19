/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_at_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:31:53 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 15:43:41 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_str_at_end(char *str, char *end)
{
	int i;
	int	j;
	int len_end;
	int len_str;

	len_end = ft_strlen(end);
	len_str = ft_strlen(str);
	i = len_str - len_end;
	j = 0;
	while (str[i])
	{
		if (str[i] != end[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}
