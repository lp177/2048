/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 17:53:39 by llaffile          #+#    #+#             */
/*   Updated: 2015/02/28 20:49:13 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"


int				iscellAvailable(t_index cell, t_env env)
{
	return (!iscellOccupied(cell, env));
}

int				iscellOccupied(t_index cell, t_env env)
{
	return (getcellContent(cell, env) != NULL);
}

t_tile			*getcellContent(t_index cell, t_env env)
{
	if (isWithinBounds(cell, env.max_size))
		return (env.grid[cell.x][cell.y]);
	else
		return (NULL);
}

int				iscellsAvailable(t_env env)
{
	t_index		cells_a[16];
	int			lenght;

	lenght = 0;
	ft_bzero(cells_a, 16 * sizeof(t_index));
	getAvailableCells(env, cells_a);
	while (lenght < 16 && cells_a[lenght] != 0)
		lenght++;
	return (!!lenght)
}

t_index			*getAvailablecells(t_env env, t_index *cells_a)
{
	t_index		i;
	t_tile		*tile;
	int			cnt;

	i = 0;
	cnt = 0;
	while (i.x < env.max_size)
	{
		i.y = 0;
		while (i.y < env.max_size)
		{
			if ((tile = getcellContent(i, env)) == NULL)
				cells_a[cnt++] = i;
			i.y++;
		}
		i.x++;
	}
	return (cells_a);
}

int				isWhitinBounds(t_index pos, size_t max)
{
	return ((pos.x >= 0 && pos.x < max)
			&& (pos.y >= 0 && pos.y < max));
}

t_index			randomAvailableCell(t_env env)
{
	t_index		cells_a[16];
	int			lenght;

	lenght = 0;
	ft_bzero(cells_a, 16 * sizeof(t_index));
	getAvailableCells(env, cells_a);
	while (lenght < 16 && cells_a[lenght] != 0)
		lenght++;
	return (cells_a[rand() % lenght]);
}

t_tile			***new_Grid(t_env *env)
{
	if((env->grid = empty(env->max_size)) == NULL)
		return (NULL);
	return (env->grid)
}

// Build a grid of the specified size
t_tile			***empty(size_t size)
{
	t_tile		***grid;

	if ((grid = (t_tile ***)tabAlloc(size, size, sizeof(t_tile *))) == NULL)
		return (NULL);
	return (grid)
}
