/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 23:57:31 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 22:06:08 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void			print_grid(t_env *env)
{
	int i,j;

	i =0;
	j=0;
	while (i < env->max_size)
	{
		j=0;
		while(j < env->max_size)
		{
			printf("%d ", env->grid[j][i]->value);
			j++;
		}
		i++;
	}
	return ;
}

int				main(int argc, char **argv)
{
	t_env	*env;
	srand(time(NULL));
	(void)argc;
	(void)argv;
	env = new_Env(4);
	setup(env);
	print_grid(env);
	return (0);
}


void			moveTile(t_tile *tile, t_index cell, t_env env)
{
	env.grid[tile->x][tile->y] = NULL;
	env.grid[cell.x][cell.y] = tile;
	updatePosition(tile, cell);
	return ;
}

void			move_process(int direction, t_env *env)
{
	t_env		self;
	t_vector	vector;

	self = *env;
	if (isGameTerminated(self))
		return ;
	prepareTiles(self);
	vector = getVector(direction);
	foreachXY(env, vector);
	if (env->moved)
	{
		if (addRandomTile(self) == NULL)
			return ;
		if (!ismovesAvailable(self))
		{
			env->over = 1; // Game over!
		}
	}
	return ;
}


void			foreachXY(t_env *env, t_vector vector)
{
	int			x;
	int			y;
	t_index		cell;
	t_tile		*tile;
	int			**traversals;

	traversals = buildTraversals(vector, env->max_size);
	x = 0;
	while (x < env->max_size)
	{
		y = 0;
		while (y < env->max_size)
		{
			cell.y = traversals[Y][y];
			cell.x = traversals[X][x];
			tile = getcellContent(cell, *env);
			mergeAndmove(env, cell, tile, vector);
			if (positionsEqual(tile, cell))
				env->moved = 1;
			y++;
		}
		x++;
	}
	tabFree((void **)traversals, 2);
	return ;
}


void			mergeAndmove(t_env *env, t_index cell, t_tile *tile, t_vector vector)
{
	t_target	target;
	t_tile		*next;
	t_tile		*merge;

	next = NULL;
	if (tile != NULL)
	{
		target = findFarthestPosition(cell, vector, *env);
		next = getcellContent(target.next, *env);
	}
	if (next && next->value == tile->value
		&& tile->merged == 0)
	{
		merge = new_tile(target.next, tile->value * 2);
		merge->merged = 1;
		insertTile(merge, *env);
		updatePosition(tile, target.next);
		removeTile(next, *env);
		env->score += merge->value;
		if (merge->value == WIN_VALUE)
			env->won = 1;
	}
	else
		moveTile(tile, target.farthest, *env);
	return ;
}

t_tile			*addRandomTile(t_env env)
{
	int		value;
	t_tile	*tile;

	tile = NULL;
	if (iscellsAvailable(env))
	{
		value = ((rand() % 10) < 9) ? 2 : 4;
		if((tile = new_tile(randomAvailableCell(env), value)) == NULL)
			return (NULL);
		insertTile(tile, env);
	}
	return (tile);
}

int				ismovesAvailable(t_env env)
{
	return (iscellsAvailable(env) || istileMatchesAvailable(env));
}


int				istileMatchesAvailable(t_env env)
{
	t_tile		*tile;
	t_index		i;

	i.x = 0;
	while (i.x < env.max_size)
	{
		i.y = 0;
		while (i.y < env.max_size)
		{
			tile = getcellContent(i, env);
			if (tile)
			{
				if (checkforMatches(env, i, tile))
					return (1);
			}
			i.y++;
		}
		i.x++;
	}
	return (0);
}

int				checkforMatches(t_env env, t_index pos, t_tile *tile)
{
	int			k;
	t_vector	vector;
	t_index		cell;
	t_tile		*other;

	k = 0;
	while (k < 4)
	{
		vector = getVector(k);
		cell.x = pos.x + vector.x;
		cell.y = pos.y + vector.y;
		other  = getcellContent(cell, env);
		if (other && other->value == tile->value)
			return (1);
		k++;
	}
	return (0);
}

void			prepareTiles(t_env env)
{
	t_index		i;
	t_tile		*tile;

	i.x = 0;
	while (i.x < env.max_size)
	{
		i.y = 0;
		while (i.y < env.max_size)
		{
			if ((tile = getcellContent(i, env)) != NULL)
			{
				tile->merged = 0;
				savePosition(tile);
			}
			i.y++;
		}
		i.x++;
	}
	return ;
}

void			setup(t_env *env)
{
	if ((env->grid  = new_Grid(env)) == NULL)
		exit(0);
	env->score = 0;
	env->over  = 0;
	env->won = 0;
	env->keep_playing = 0;
	addStartTiles(*env);
}

void			addStartTiles(t_env env)
{
	int		i;

	i = 0;
	while (i++ < env.start_tile)
	{
		addRandomTile(env);
	}
	return ;
}


void			keepPlaying(t_env *env)
{
	env->keep_playing = 1;
}

// Return true if the game is lost, or has won and the user hasn't kept playing
int				isGameTerminated(t_env env)
{
	return (env.over || (env.won && !env.keep_playing));
}

int				positionsEqual(t_tile *tile, t_index pos)
{
	return (tile->x == pos.x && tile->y == pos.y);
}
