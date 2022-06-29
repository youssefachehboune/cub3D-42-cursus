/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:34:57 by yachehbo          #+#    #+#             */
/*   Updated: 2022/06/29 21:06:23 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	struct_allocation(t_mlx *mlx)
{
	mlx->player = malloc(sizeof(t_player));
	mlx->ray = malloc(sizeof(t_ray));
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if (!mlx->player || !mlx->txt || !mlx->ray)
		return (1);
	return (0);
}

void	init_ray(t_ray *ray, t_player *player, double ray_angle)
{
	ray->p_dx_pos = player->dx_pos;
	ray->p_dy_pos = player->dy_pos;
	ray->p_check_x = (int)ray->p_dx_pos;
	ray->p_check_y = (int)ray->p_dy_pos;
}

int	put_ray(t_mlx *mlx, t_player *p, t_ray *ray)
{
	int		x;
	double	ray_angle;
	double	camera_angle;

	x = -1 * (WIN_W / 2);
	while (x < (WIN_W / 2))
	{
		ray_angle = p->player_dir + (double)x * (FOV / WIN_W) * (M_PI / 180);
		camera_angle = (double)x * (FOV / WIN_W) * (M_PI / 180);
		init_ray(ray, p, ray_angle);
		x++;
	}
	return (0);
}

int	create_image(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	if (!mlx->img)
		return (1);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->en);
	put_ray(mlx, mlx->player, mlx->ray);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	start_mlx(t_mlx *mlx, t_file *file)
{
	if (init_mlx(mlx, file))
		return (1);
	if (create_image(mlx))
		return (1);
	return (0);
}
