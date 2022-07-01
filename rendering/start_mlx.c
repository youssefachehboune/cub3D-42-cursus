/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:34:57 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/01 08:44:10 by yachehbo         ###   ########.fr       */
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
	ray->r_dir_x = cos(ray_angle);
	ray->r_dir_y = sin(ray_angle);
	ray->r_step_x = 1 / fabs(ray->r_dir_x);
	ray->r_step_y = 1 / fabs(ray->r_dir_y);
	ray->r_len_x = 0;
	ray->r_len_y = 0;
	ray->wall_hit = 0;
	ray->r_length = 0;
	ray->side = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
}

void	init_ray_2(t_ray *ray)
{
	if (ray->r_dir_x < 0)
	{
		ray->increm_x = -1;
		ray->r_len_x = (ray->p_dx_pos - ((double)ray->p_check_x)) * ray->r_step_x;
	}
	else
	{
		ray->increm_x = 1;
		ray->r_len_x = ((double)(ray->p_check_x + 1) - ray->p_dx_pos) * ray->r_step_x;
	}
	if (ray->r_dir_y < 0)
	{
		ray->increm_y = -1;
		ray->r_len_y = (ray->p_dy_pos - (double)ray->p_check_y) * ray->r_step_y;
	}
	else
	{
		ray->increm_y = 1;
		ray->r_len_y = ((double)(ray->p_check_y + 1) - ray->p_dy_pos) * ray->r_step_y;
	}
}

void	find_wall(double max, t_ray *ray, t_file *file)
{
	while (ray->wall_hit != 1 && ray->r_length < max)
	{
		
		if (ray->r_len_x < ray->r_len_y)
		{
			ray->p_check_x += ray->increm_x;
			ray->r_length = ray->r_len_x;/////
			ray->r_len_x += ray->r_step_x;////
			ray->side = 0;
		}
		else 
		{
			ray->p_check_y += ray->increm_y;
			ray->r_length = ray->r_len_y;
			ray->r_len_y += ray->r_step_y;
			ray->side = 1;
		}
		if (file->scene[ray->p_check_y][ray->p_check_x] == '1')
		{
			ray->wall_hit = 1;
		}
	}
	if (ray->wall_hit == 1)
	{
		ray->hit_x = ray->p_dx_pos + ray->r_dir_x * ray->r_length;
		ray->hit_y = ray->p_dy_pos + ray->r_dir_y * ray->r_length;
	}
	
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr_img + (y * mlx->sl + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(int x, t_ray *ray, t_mlx *mlx)
{
	int	y;
	int	wall_height;

	y = -1;
	wall_height = (int)((WIN_H - ray->wall_len) / 2);
	while (++y < wall_height)
		pixel_put(mlx, x, y, mlx->file->ceilling);
	while (y < WIN_H)
	{
		pixel_put(mlx, x, y, mlx->file->floor);
		y++;
	}
}

int	put_ray(t_mlx *mlx, t_player *p, t_ray *ray)
{
	int		x;
	double	ray_angle;
	double	camera_angle;

	x = -1 * (WIN_W / 2);
	while (x < (WIN_W / 2))
	{
		ray_angle = p->player_dir + (double)x * ((double)FOV / WIN_W) * (M_PI / 180);
		camera_angle = (double)x * ((double)FOV / WIN_W) * (M_PI / 180);
		init_ray(ray, p, ray_angle);
		init_ray_2(ray);
		find_wall(MAX_R_LEN, ray, mlx->file);
		ray->wall_len = WIN_H / (ray->r_length * cos(camera_angle));
		draw_column(x + WIN_W / 2, ray, mlx);
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
