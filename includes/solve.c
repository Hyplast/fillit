/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:04:48 by severi            #+#    #+#             */
/*   Updated: 2022/01/24 18:18:52 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	calc_size(int n)
{
	int	size;

	size = 2;
	while (size * size / 4 < n)
	{
		size++;
	}
	return (size);
}

void	create_columns(t_col ***col, int size)
{
	int	i;

	i = 0;
	*col = (t_col **)malloc(sizeof(t_col *) * (size_t)(size * size));
	if (!(*col))
		error(4);
	while (i < size * size)
	{
		(*col)[i] = (t_col *)malloc(sizeof(t_col));
		if (!(*col)[i])
			error(4);
		(*col)[i++]->length = 0;
	}
}

t_row	*create(t_row *puzzle, t_col ***col_ptr, int *size)
{
	t_row	*root;
	t_row	*row_header;

	row_header = add_to_header(puzzle, *size);
	while (row_header == NULL)
		row_header = add_to_header(puzzle, ++(*size));
	create_columns(col_ptr, *size);
	root = (t_row *)malloc(sizeof(t_row));
	if (!root)
		error(4);
	root->name = 0;
	root->down = row_header;
	root->up = row_header->up;
	root->up->down = root;
	root->down->up = root;
	return (root);
}

void	free_puzzle(t_row *puzzle)
{
	t_row	*temp;
	t_row	*last;

	last = puzzle->up;
	while (puzzle != last)
	{
		temp = puzzle;
		puzzle = puzzle->down;
		free(temp);
	}
	free(puzzle);
}

void	solve(t_row *puzzle)
{
	int		nxn_size;
	int		count;
	t_row	*root;
	t_col	**col_ptr;
	t_row	**solutions;

	col_ptr = NULL;
	count = puzzle->up->name - START_NAME + 1;
	solutions = (t_row **)malloc(sizeof(t_row *) * (size_t)count);
	if (!solutions)
		error(4);
	nxn_size = calc_size(count);
	root = create(puzzle, &col_ptr, &nxn_size);
	link_matrix(root, col_ptr, nxn_size);
	while (algorithm_x(root, &solutions, count, 0) != 1)
	{
		destroy_matrix(root, col_ptr, nxn_size++);
		root = create(puzzle, &col_ptr, &nxn_size);
		link_matrix(root, col_ptr, nxn_size);
	}
	print_solution(solutions, count, nxn_size, -1);
	free(solutions);
	free_puzzle(puzzle);
	destroy_matrix(root, col_ptr, nxn_size);
}
