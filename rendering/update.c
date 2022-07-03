/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:51:47 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/03 22:35:14 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void update_player_pos(t_mlx *mlx)
{
	if (mlx->player->up == 1)
		move_up(mlx);
	if (mlx->player->down == 1)
		move_down(mlx);
	if (mlx->player->left == 1)
		move_left(mlx);
	if (mlx->player->right == 1)
		move_right(mlx);
    if (mlx->player->rot_left == 1)
        mlx->player->player_dir -= SPEED;
    if (mlx->player->rot_right == 1)
        mlx->player->player_dir += SPEED;
}

int update(void *mlx_v)
{
    t_mlx   *mlx;

    mlx = (t_mlx *)mlx_v;
    update_player_pos(mlx);
    cast_ray(mlx, mlx->player, mlx->ray);
    mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
    return(0);
}
