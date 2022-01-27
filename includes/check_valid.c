/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:32:58 by severi            #+#    #+#             */
/*   Updated: 2022/01/21 23:14:35 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	ft_strcountchr(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

int	chk_out_of_bounds(char *tetr)
{
	if (ft_strlen(tetr) != 16 || ft_strcountchr(tetr, '#') != 4 \
	|| ft_strcountchr(tetr, '.') != 12)
		return (0);
	return (1);
}

int	chk_connections_4_ways(char *tetr, int nxn_size, int i)
{
	int	connections;

	connections = 0;
	if (i % nxn_size != 3)
	{
		if (tetr[i + 1] == '#')
			connections++;
	}
	if (i < (nxn_size - 1) * nxn_size)
	{
		if (tetr[i + nxn_size] == '#')
			connections++;
	}
	if (i % nxn_size != nxn_size && i != 0)
	{
		if (tetr[i - 1] == '#')
			connections++;
	}
	if (i >= nxn_size)
	{
		if (tetr[i - nxn_size] == '#')
			connections++;
	}
	return (connections);
}

int	chk_edges_connected(char *tetr, int nxn_size)
{
	int	i;
	int	concs;

	i = -1;
	concs = 0;
	while (++i < nxn_size * nxn_size)
	{
		if (tetr[i] == '#')
			concs += chk_connections_4_ways(tetr, nxn_size, i);
	}
	return (concs);
}

void	ft_putnchar(char *str, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		ft_putchar(str[i]);
	}
}
