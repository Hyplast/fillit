/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:43:41 by severi            #+#    #+#             */
/*   Updated: 2022/01/21 21:33:28 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	uncover(t_row *stack[], int *stack_id)
{
	t_row	*row;
	t_node	*node;
	int		length;

	while (*stack_id > 0)
	{
		row = stack[--(*stack_id)];
		node = row->head;
		length = row->length;
		while (length--)
		{
			node->up->down = node;
			node->down->up = node;
			node = node->right;
		}
		row->up->down = row;
		row->down->up = row;
	}
}

t_row	*cover_row(t_row *row)
{
	t_node	*node;
	int		length;

	node = row->head;
	length = row->length;
	while (length--)
	{
		node->up->down = node->down;
		node->down->up = node->up;
		node = node->right;
	}
	row->up->down = row->down;
	row->down->up = row->up;
	return (row);
}

void	cover(t_row *(*stack)[], int *stack_id, t_row *temp)
{
	t_node	*row_node;
	t_node	*col_node;
	int		do_while_fake;

	do_while_fake = 1;
	row_node = temp->head;
	while (row_node != temp->head || do_while_fake--)
	{
		col_node = row_node->down;
		while (col_node != row_node)
		{
			(*stack)[(*stack_id)++] = cover_row(col_node->row);
			col_node = col_node->down;
		}
		row_node = row_node->right;
	}
	(*stack)[(*stack_id)++] = cover_row(temp);
}

void	destroy_matrix(t_row *root, t_col **col, int nxn_size)
{
	t_row	*free_row;
	t_row	*last_row;
	t_node	*free_node;
	int		i;

	last_row = root->up;
	while (root != last_row)
	{
		free_row = root;
		root = root->down;
		free(free_row);
	}
	free(root);
	i = -1;
	while (++i < nxn_size * nxn_size)
	{
		while (col[i]->length--)
		{
			free_node = col[i]->head;
			col[i]->head = col[i]->head->down;
			free(free_node);
		}
		free(col[i]);
	}
	free(col);
}	

int	algorithm_x(t_row *root, t_row ***solutions, int count, int depth)
{
	t_row	*stack[1000];
	t_row	*temp;
	int		stack_id;

	stack_id = 0;
	temp = root->down;
	while (temp != root && temp->name != START_NAME + depth)
		temp = temp->down;
	while (temp != root && temp->name == START_NAME + depth)
	{
		(*solutions)[depth] = temp;
		cover(&stack, &stack_id, temp);
		if (algorithm_x(root, solutions, count, depth + 1) == 1)
		{
			uncover(stack, &stack_id);
			return (1);
		}
		uncover(stack, &stack_id);
		temp = temp->down;
	}
	if (count == depth)
		return (1);
	return (0);
}
