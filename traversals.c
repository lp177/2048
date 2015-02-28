/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 18:09:02 by llaffile          #+#    #+#             */
/*   Updated: 2015/02/28 23:13:20 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"


int				**buildTraversals(t_vector vector, size_t max)
{
	int		**traversals;
	size_t		i;

	i = 0;
	if ((traversals = (int **)tabAlloc(2, max, sizeof(int))) == NULL)
		return (NULL);
	while (i < max)
	{
		traversals[X][i] = i;
		traversals[Y][i] = i;
		i++;
	}
	if (vector.x == 1)
		traversals[X] = (int *)reverse(traversals[X], max, sizeof(int));
	if (vector.y == 1)
		traversals[Y] = (int *)reverse(traversals[Y], max, sizeof(int));
	return (traversals);
}


t_vector		getVector(int direction)
{
	t_vector	vector;

	if (direction == UP)
	{
		vector.x = 0;
		vector.y = -1;
	}
	if (direction == RIGHT)
	{
		vector.x = 1;
		vector.y = 0;
	}
	if (direction == DOWN)
	{
		vector.x = 0;
		vector.y = 1;
	}
	if (direction == LEFT)
	{
		vector.x = -1;
		vector.y = 0;
	}
	return (vector);
}

t_target		findFarthestPosition(t_index cell, t_vector vector, t_env env)
{
	t_index		previous;
	t_target	target;

//	ft_putstr("in findFarthestPosition\n");
	while (1)
	{
//		ft_putstr("in lopp findFarthestPosition\n");
		previous = cell;
		cell.x = previous.x + vector.x;
		cell.y = previous.y + vector.y;
		if (!isWithinBounds(cell, env.max_size) || !iscellAvailable(cell, env))
			break ;
	}
	target.farthest = previous;
	target.next = cell;
	return (target);
}
