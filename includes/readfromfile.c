/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfromfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:22:10 by severi            #+#    #+#             */
/*   Updated: 2022/01/23 01:53:01 by ssavukos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	error(int res)
{
	ft_putstr("error\n");
	exit(res);
	return ;
}

void	init_root(t_row **root)
{
	*root = (t_row *) malloc (sizeof(t_row));
	(*root)->down = NULL;
	(*root)->up = *root;
	(*root)->name = '\0';
}

void	return_tetrimino(char buf[], char **tetrimino)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 19)
	{
		if (i != 4 && i != 9 && i != 14)
			tetrimino[0][j++] = buf[i];
		i++;
	}
	if (buf[4] != '\n' || buf[9] != '\n' || buf[14] != '\n' || buf[19] != '\n')
		ft_strclr(*tetrimino);
}

int	get_lines(int fd, t_row **root, char **tetrimino)
{
	int		ret;
	char	buf[20 + 1];
	int		max;

	ret = 20;
	max = 0;
	while (ret == 20)
	{
		ret = (int)read(fd, &buf, 20);
		if (ret != 20)
			error(-1);
		buf[20] = '\0';
		return_tetrimino(buf, tetrimino);
		if (++max > 26 || chk_vld_add_stru(*tetrimino, root) != 0)
			return (3);
		buf[0] = '\0';
		ret = (int)read(fd, &buf, 1);
		if (ret == 1 && buf[0] == '\n')
			ret = 20;
		else if (ret == 0)
			return (0);
	}
	return (-1);
}

void	read_to_array(int fd)
{
	t_row	*root;
	char	*tetrimino;
	int		result;

	tetrimino = ft_strnew(16);
	init_root(&root);
	result = get_lines(fd, &root, &tetrimino);
	ft_strdel(&tetrimino);
	if (result == 0)
		solve(root);
	else
		error(result);
}
