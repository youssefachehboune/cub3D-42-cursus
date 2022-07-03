/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:19:04 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/03 22:33:53 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**  To make the game more realistic the player will be blocked before he is 
**  too close from the wall. So we don't check if the player is touching 
**  the wall, but we check if is slightly away from it.
*/

int	wall_collision(t_mlx *mlx, double x, double y)
{
	if (mlx->file->scene[(int)(y + 0.2)][(int)x] == '1')
		return (1);
	if (mlx->file->scene[(int)y][(int)(x - 0.2)] == '1')
		return (1);
	if (mlx->file->scene[(int)(y - 0.2)][(int)x] == '1')
		return (1);
	if (mlx->file->scene[(int)y][(int)(x + 0.2)] == '1')
		return (1);
	return (0);
}

/*
**  cos = adjacent / hypotenuse .
**  sin = opposite / hypotenuse .
**  (new_dx_pos - mlx->player->dx_pos) is the length of the  adjacent.
**  (new_dy_pos - mlx->player->dy_pos) is the length of the opposite.
**  SPEED is the length of the hypotenuse.
*/

void	move_up(t_mlx *mlx)
{
	double	new_dx_pos;
	double	new_dy_pos;

	new_dx_pos = mlx->player->dx_pos + cos(mlx->player->player_dir) * SPEED;
	new_dy_pos = mlx->player->dy_pos + sin(mlx->player->player_dir) * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

/*
**  To move down we need the player_dir as if the player was looking the other way.
**  So we need the player_dir as if the player turned half a turn.
**  To do that we add M_PI to the player_dir or simply we multiply the value of cos and sin by -1.
*/

void	move_down(t_mlx *mlx)
{
	double	new_dx_pos;
	double	new_dy_pos;

	new_dx_pos = mlx->player->dx_pos - cos(mlx->player->player_dir) * SPEED;
	new_dy_pos = mlx->player->dy_pos - sin(mlx->player->player_dir)* SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

/*
**  The same as before, only this time we needed the player_dir as if the player turned
**  a quarter turn to the left.
**  We do that by substracting M_PI_2 from player_dir
*/

void	move_left(t_mlx *mlx)
{
	double	new_dx_pos;
	double	new_dy_pos;

	new_dx_pos = mlx->player->dx_pos + cos(mlx->player->player_dir - (M_PI_2)) * SPEED;
	new_dy_pos = mlx->player->dy_pos + sin(mlx->player->player_dir - (M_PI_2)) * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

/*
**  The same as before, only this time we needed the player_dir as if the player turned
**  a quarter turn to the right.
**  We do that by add M_PI_2 to player_dir
*/

void	move_right(t_mlx *mlx)
{
	double	new_dx_pos;
	double	new_dy_pos;

	new_dx_pos = mlx->player->dx_pos + cos(mlx->player->player_dir + (M_PI_2)) * SPEED;
	new_dy_pos = mlx->player->dy_pos + sin(mlx->player->player_dir + (M_PI_2)) * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}
