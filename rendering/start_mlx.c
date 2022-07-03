/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:34:57 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/03 19:46:23 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**  allocate for a player, a ray and 4 textures, and protect it.
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
**	ray->p_check_x is the x coordinae on which we will check for a wall
**	ray->p_check_y is the y coordinae on which we will check for a wall
**	ray->r_dir_x and ray->r_dir_y are used to know which direction the ray is going
**	ray->r_step_x is the distance between each x coordinate of the intersection of the ray with the *horizontal* lines
**	ray->r_step_y is the distance between each y coordinate of the intersection of the ray with the *vertical* lines
**	see : https://permadi.com/1996/05/ray-casting-tutorial-7/
*/

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

/*
**	ray->r_len_x: the distance between p_dx_pos and the intersection of the ray with the first *horizontal* line
**	ray->r_len_y: the distance between p_dx_pos and the intersection of the ray with the first *vertical* line
**	ray->increm_x = 1 if the ray is going up
**	ray->increm_x = -1 if the ray is going down
**	ray->increm_y = 1 if the ray is going to the right
**	ray->increm_y = -1 if the ray is going to the left
**	ray->r_dir_x is neg if the ray goes to left, and pos if it goes to the right
**	ray->r_dir_y is neg if the ray goes to bottom, and pos if it goes to the top
*/

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
/*
**	ray->wall_hit = 1 only if the ray hit the wall
**	while the loop is running the ray->r_length is the distance between the player an the intersetion of the ray with horizontal and vertical lines one after the other
**	at the end of the loop ray->r_length will be the distance between the player and **	e wall
**	if side = 1 the wall is either on the right or the left, else it's on top or bottom
**	we start by the first intersetion then the second and so on
**	see : https://permadi.com/1996/05/ray-casting-tutorial-7/
*/
void	find_wall(t_ray *ray, t_file *file)
{
	while (ray->wall_hit != 1)
	{
		if (ray->r_len_x < ray->r_len_y)
		{
			ray->p_check_x += ray->increm_x;
			ray->r_length = ray->r_len_x;
			ray->r_len_x += ray->r_step_x;
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
			ray->wall_hit = 1;	
	}
	ray->hit_x = ray->p_dx_pos + ray->r_dir_x * ray->r_length;
	ray->hit_y = ray->p_dy_pos + ray->r_dir_y * ray->r_length;	
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

static int	get_texel_color(t_txt *txt, int x, int y)
{
	int		color;
	char	*dst;

	dst = txt->txt_adr + (y * txt->len + x * (txt->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static int	dir_wall(t_ray *ray)
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

/*
**	see : https://permadi.com/1996/05/ray-casting-tutorial-7/
*/

int draw_wall(t_mlx *mlx, t_ray *ray, int y)
{
	int dirc;
	int col;
	int d_wall;
	double	text_x;
	double	text_x_step;

	d_wall = (int)((WIN_H + ray->wall_len) * 0.5);
	dirc = dir_wall(ray);
	col = (int)((ray->hit_x + ray->hit_y) * mlx->txt[dirc].w) % mlx->txt[dirc].w;
	text_x = 0.00;
	text_x_step = (mlx->txt[dirc].h - 1) / (double)ray->wall_len;
	
	while (ray->wall_height < d_wall)
	{
		if (ray->wall_height >= 0 && ray->wall_height <= WIN_H - 1)
			pixel_put(mlx, y, ray->wall_height,
				get_texel_color(&mlx->txt[dirc], col, (int)text_x));
		ray->wall_height++;
		text_x += text_x_step;
	}
	return (ray->wall_height);
}

void	draw_column(int x, t_ray *ray, t_mlx *mlx)
{
	int	y;

	y = -1;
	ray->wall_height = (int)((WIN_H - ray->wall_len) / 2);
	while (++y < ray->wall_height)
		pixel_put(mlx, x, y, mlx->file->ceilling);
	y = draw_wall(mlx, ray, x);
	while (y < WIN_H)
	{
		pixel_put(mlx, x, y, mlx->file->floor);
		y++;
	}
}

/*
**	ray_angle is the angle between the x axis and the ray
**	camera_angle is the angle between the z axis and the ray
**	ray->wall_len is the heigth of the projected wall
**	see: https://permadi.com/1996/05/ray-casting-tutorial-8/
**	and https://permadi.com/1996/05/ray-casting-tutorial-9/
*/
int	cast_ray(t_mlx *mlx, t_player *p, t_ray *ray)
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
		find_wall(ray, mlx->file);
		ray->wall_len = WIN_H / (ray->r_length * cos(camera_angle));
		draw_column(x + WIN_W / 2, ray, mlx);
		x++;
	}
	return (0);
}
/*
**	The mlx_new_image(); will create a new image in memory, and return a void * needed to manipulate this image later.
**	The mlx_get_data_addr(): will bring the addr of the img.
**	The mlx_put_image_to_window(); will put the image in the window.
**	see : https://gontjarow.github.io/MiniLibX/mlx_new_image.html
*/
int	create_image(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	if (!mlx->img)
		return (1);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->en);
	cast_ray(mlx, mlx->player, mlx->ray);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}

/*
**	mlx_hook() calls a function when a specific event is being triggered
**  see: https://harm-smits.github.io/42docs/libs/minilibx/hooks.html
*/
int	start_mlx(t_mlx *mlx, t_file *file)
{
	if (init_mlx(mlx, file))
		return (1);
	if (create_image(mlx))
		return (1);
	mlx_hook(mlx->win, 17, 1L<<17, close_win, mlx);
	mlx_hook(mlx->win, 2, 1L<<0, press, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, release, mlx);
	mlx_loop_hook(mlx->init_ptr, update, mlx);
	return (0);
}
