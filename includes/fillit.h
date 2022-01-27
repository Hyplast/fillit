/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:38:28 by marius            #+#    #+#             */
/*   Updated: 2022/01/23 18:55:47 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define START_NAME 'A'
# define MAX_TETRIMINOS 26
# define EMPTY_CHAR '.'
# define VALID_CHAR '#'

typedef struct s_node
{
	struct s_node			*up;
	struct s_node			*down;
	struct s_node			*left;
	struct s_node			*right;
	struct s_row			*row;
}							t_node;

typedef struct s_col
{
	struct s_node			*head;
	int						length;
}							t_col;

typedef struct s_row
{
	struct s_row			*down;
	struct s_row			*up;
	int						tetr[4][2];
	int						length;
	char					name;
	struct s_node			*head;
}							t_row;

void	solve(t_row *puzzle);
void	read_to_array(int fd);
int		chk_vld_add_stru(char *tetrimino, t_row **root);
int		chk_out_of_bounds(char *tetr);
int		chk_edges_connected(char *tetr, int nxn_size);
int		chk_vld_add_stru(char *tetrimino, t_row **root);
void	add_to_list(t_row *row, t_row **root, char name);
void	error(int res);
void	link_matrix(t_row *root, t_col **col, int size);
void	destroy_matrix(t_row *root, t_col **col_ptr, int nxn_size);
void	print_solution(t_row **solutions, int count, int nxn_size, int i);
int		algorithm_x(t_row *root, t_row ***solutions, int count, int depth);
t_row	*add_to_header(t_row *root, int nxn_size);
void	ft_putnchar(char *str, int n);

#endif
