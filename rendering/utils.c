/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:20:58 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/13 16:51:52 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	These variables are 1 if the keys related to them are pressed,
**	and 0 if released.
*/

void	init_press_var(t_player *player)
{
	player->up = 0;
	player->down = 0;
	player->left = 0;
	player->right = 0;
	player->rot_left = 0;
	player->rot_right = 0;
}

/*
**  allocate for a player, a ray and 4 textures, because each wall need 4 textures.
*/

int	struct_allocation(t_mlx *mlx)
{
	mlx->player = malloc(sizeof(t_player));
	mlx->ray = malloc(sizeof(t_ray));
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if (!mlx->player || !mlx->txt || !mlx->ray)
		return (1);
	return (0);
}

/*
**	this function goes to the byte that contains the pixel and changes its value to the desired color
*/

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr_img + (y * mlx->sl + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
**	this function goes to the byte that contains the color and returns its value
*/

int	get_txt_color(t_txt *txt, int x, int y)
{
	int		color;
	char	*dst;

	dst = txt->txt_adr + (y * txt->len + x * (txt->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

int	dir_wall(t_ray *ray)
{
	if (ray->side == 0 && ray->r_dir_x < 0)
		return (0);
	else if (ray->side == 0 && ray->r_dir_x > 0)
		return (2);
	else if (ray->side == 1 && ray->r_dir_y < 0)
		return (3);
	else
		return (1);
}
