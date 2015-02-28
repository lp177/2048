/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <llaffile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 23:57:31 by luperez           #+#    #+#             */
/*   Updated: 2015/02/28 23:14:08 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void			print_grid(t_env *env)
{
	int i,j;

	i =0;
	j=0;
	printf("%p %d %d %d %d %d %d %d\n",  env->grid,env->moved, env->score, env->won, env->over, env->keep_playing, env->start_tile, env->max_size);
	while (i < env->max_size)
	{
		j=0;
		while(j < env->max_size)
		{
			if (env->grid[j][i] != NULL)
				printf("%d\t", env->grid[j][i]->value);
			else
				printf("false\t");
			j++;
		}
		printf("\n");
		i++;
	}
	return ;
}

int				main(int argc, char **argv)
{
	t_env	*env;
	int i=0;
	srand(time(NULL));
	(void)argc;
	(void)argv;
	env = new_Env(4);
	ft_putstr("flag1\n");
	setup(env);
	ft_putstr("flag4\n");
	print_grid(env);
	while (i++ < 20)
	{
		move_process(rand() % 4, env);
		print_grid(env);
	}
	return (0);
}


void			moveTile(t_tile *tile, t_index cell, t_env env)
{
	if (tile == NULL)
		return ;
//	printf("in moveTile\n");
	env.grid[tile->x][tile->y] = NULL;
//	ft_putstr("ok1\n");
	env.grid[cell.x][cell.y] = tile;
//	ft_putstr("ok2\n");
	updatePosition(tile, cell);
//	ft_putstr("ok3\n");
	return ;
}

void			move_process(int direction, t_env *env)
{
	t_env		self;
	t_vector	vector;

	self = *env;
//	printf("in move_process\n");
	if (isGameTerminated(self))
		return ;
//	printf("game not isGameTerminated\n");
	prepareTiles(self);
//	printf("prepareTiles ok\n");
	vector = getVector(direction);
//	printf("vector ok %d  %d\n", vector.x, vector.y);
	foreachXY(env, vector);
//	printf("foreachXY OK\n");
	if (env->moved)
	{
//		printf("in moved\n");
		if (addRandomTile(self) == NULL)
			{
//				printf("succes add\n");
				return ;
			}
		if (!ismovesAvailable(self))
		{
//			printf("over\n");
			env->over = 1; // Game over!
		}
	}
//	printf("out of move_process\n");
	return ;
}


void			foreachXY(t_env *env, t_vector vector)
{
	int			x;
	int			y;
	t_index		cell;
	t_tile		*tile;
	int			**traversals;

//	printf("in foreachXY\n");
	traversals = buildTraversals(vector, env->max_size);
	x = 0;
//	printf("traversals ok\n");
	while (x < env->max_size)
	{
		y = 0;
//		printf("loop x %d\n", x);
		while (y < env->max_size)
		{
//			printf("loop y %d\n", y);
			cell.y = traversals[Y][y];
//			printf("%d\n", cell.y);
			cell.x = traversals[X][x];
//			printf("%d\n", cell.x);
			tile = getcellContent(cell, *env);
//			printf("%p\n", tile);
			mergeAndmove(env, cell, tile, vector);
//			printf("mergeAndmove alright\n");
			if (positionsEqual(tile, cell))
				env->moved = 1;
//			printf("positionsEqual alright\n");
			y++;
		}
		x++;
	}
	tabFree((void **)traversals, 2);
//	printf("tabFree ok\n");
	return ;
}


void			mergeAndmove(t_env *env, t_index cell, t_tile *tile, t_vector vector)
{
	t_target	target;
	t_tile		*next;
	t_tile		*merge;

//	printf("in mergeAndmove\n");
	next = NULL;
	if (tile != NULL)
	{
//		printf("in mergeAndmove tile != NULL\n");
		target = findFarthestPosition(cell, vector, *env);
//		ft_putstr("findFarthestPosition ok\n");
		next = getcellContent(target.next, *env);
//		printf("%p getcellContent ok\n", next);
	}
	if (next && next->value == tile->value
		&& tile->merged == 0)
	{
//		printf("needto merge\n");
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
	{
//		ft_putstr("needto moveTile in mergeAndmove\n");
		moveTile(tile, target.farthest, *env);
	}
	return ;
}

t_tile			*addRandomTile(t_env env)
{
	int		value;
	t_tile	*tile;

	tile = NULL;
//	printf("in addRandomTile\n");
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
//				printf("in prepareTiles\n");
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
		return ;
//	ft_putstr("flag2\n");
	env->score = 0;
	env->over  = 0;
	env->won = 0;
	env->keep_playing = 0;
	env->start_tile = 2;
	addStartTiles(*env);
//	ft_putstr("flag3\n");
}

void			addStartTiles(t_env env)
{
	int		i;

	i = 0;
//	printf("in addStartTiles\n");
	while (i++ < env.start_tile)
	{
//		printf("in addStartTiles loop nb %d\n", i);
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
	if (tile == NULL)
		return (0);
	return (tile->x == pos.x && tile->y == pos.y);
}
