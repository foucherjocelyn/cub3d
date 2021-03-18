/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:31:31 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/17 18:34:48 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(0);
}

int		ft_exit(void)
{
	exit(0);
	return (0);
}
