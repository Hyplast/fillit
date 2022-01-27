/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:13:35 by severi            #+#    #+#             */
/*   Updated: 2022/01/21 21:16:08 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	insert_in_col(t_node *head, t_node *new)
{
	new->down = head;
	new->up = head->up;
	new->up->down = new;
	new->down->up = new;
}

void	insert_in_row(t_node *head, t_node *new)
{
	new->right = head;
	new->left = head->left;
	new->left->right = new;
	new->right->left = new;
}

void	add_node(t_row *row, t_col *col)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		error(4);
	node->row = row;
	if (row->length == 0)
	{
		row->head = node;
		node->left = node;
		node->right = node;
	}
	else
		insert_in_row(row->head, node);
	row->length++;
	if (col->length == 0)
	{
		col->head = node;
		node->up = node;
		node->down = node;
	}
	else
		insert_in_col(col->head, node);
	col->length++;
}

void	link_matrix(t_row *root, t_col **col, int size)
{
	t_row	*row;
	int		i;
	int		col_id;

	row = root->down;
	while (row != root)
	{
		i = 0;
		while (i < 4)
		{
			col_id = row->tetr[i][1] * size + row->tetr[i][0];
			add_node(row, col[col_id]);
			i++;
		}
		row = row->down;
	}
}
