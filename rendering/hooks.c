/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:50 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/03 15:30:00 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->init_ptr, mlx->img);
	mlx_destroy_window(mlx->init_ptr, mlx->win);
	exit(0);
}
/*
** see: https://github.com/qst0/ft_libgfx/blob/master/keys.h
*/

// void print(t_mlx *mlx)
// {
//     printf("up : %d\n", mlx->player->up);
// 	printf("down : %d\n", mlx->player->down);
// 	printf("left : %d\n", mlx->player->left);
// 	printf("right : %d\n", mlx->player->right);
// 	printf("rot_left : %d\n", mlx->player->rot_left);
// 	printf("rot_right : %d\n", mlx->player->rot_right);
// }

int	press(int key, t_mlx *mlx)
{
    if (key == 53)
        close_win(mlx);
    else if (key == 13)
        mlx->player->up = 1;
    else if (key == 1)
        mlx->player->down = 1;
    else if (key == 0)
        mlx->player->left = 1;
    else if (key == 2)
        mlx->player->right = 1;
    else if (key == 123)
        mlx->player->rot_left = 1;
    else if (key == 124)
        mlx->player->rot_right = 1;
   // print(mlx);
    return(0);
}

int	release(int key, t_mlx *mlx)
{
    if (key == 13)
        mlx->player->up = 0;
    else if (key == 1)
        mlx->player->down = 0;
    else if (key == 0)
        mlx->player->left = 0;
    else if (key == 2)
        mlx->player->right = 0;
    else if (key == 123)
        mlx->player->rot_left = 0;
    else if (key == 124)
        mlx->player->rot_right = 0;
    //print(mlx);
    return(0);
}