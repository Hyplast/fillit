/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:36:24 by severi            #+#    #+#             */
/*   Updated: 2022/01/21 23:15:00 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	add_to_list(t_row *row, t_row **root, char name)
{
	row->name = name;
	row->down = *root;
	row->up = (*root)->up;
	row->down->up = row;
	row->up->down = row;
}

int	fits(t_row *fig, int nxn_size, int x, int y)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (fig->tetr[i][0] + x >= nxn_size || fig->tetr[i][1] + y >= nxn_size)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	add_row(t_row **header, t_row *fig, int x, int y)
{
	t_row	*row;
	int		i;

	i = 0;
	row = (t_row *)malloc(sizeof(t_row));
	if (!row)
		error(4);
	row->length = 0;
	row->name = fig->name;
	row->up = row;
	row->down = row;
	if (*header != NULL)
	{
		row->up = *header;
		row->down = (*header)->down;
		row->up->down = row;
		row->down->up = row;
	}
	while (i < 4)
	{
		row->tetr[i][0] = fig->tetr[i][0] + x;
		row->tetr[i][1] = fig->tetr[i][1] + y;
		i++;
	}
	*header = row;
}

t_row	*add_to_header(t_row *root, int nxn_size)
{
	t_row	*temp;
	t_row	*row_header;
	int		x;
	int		y;

	row_header = NULL;
	temp = root->down;
	while (temp != root)
	{
		y = -1;
		while (++y < nxn_size)
		{
			x = -1;
			while (++x < nxn_size)
			{
				if (fits(temp, nxn_size, x, y) == 1)
					add_row(&row_header, temp, x, y);
			}
		}
		temp = temp->down;
	}
	if (row_header)
		return (row_header->down);
	return (NULL);
}

void	print_solution(t_row **sol, int count, int n_size, int i)
{
	char	*str;
	int		obj;
	int		str_obj;

	str = ft_strnew((size_t)(n_size * n_size));
	while (++i < n_size * n_size)
		str[i] = '.';
	i = -1;
	while (++i < count)
	{
		obj = -1;
		while (++obj < 4)
		{
			str_obj = sol[i]->tetr[obj][1] * n_size + sol[i]->tetr[obj][0];
			str[str_obj] = sol[i]->name;
		}
	}
	i = -1;
	while (++i < n_size)
	{
		ft_putnchar(str + i * n_size, n_size);
		ft_putchar('\n');
	}
	ft_strdel(&str);
}
