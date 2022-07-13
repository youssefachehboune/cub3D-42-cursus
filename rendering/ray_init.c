/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:25:32 by yachehbo          #+#    #+#             */
/*   Updated: 2022/07/13 16:49:54 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	ray->p_check_x is the x coordinae on which we will check for a wall
**	ray->p_check_y is the y coordinae on which we will check for a wall
**	ray->r_dir_x and ray->r_dir_y are used to know which direction the ray is going
**	ray->r_step_x is the distance between the points of intersection of the ray with the *horizontal* lines
**	ray->r_step_y is the distance between the points intersection of the ray with the *vertical* lines
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
**	ray->r_dir_y is neg if the ray goes to the bottom, and pos if it goes to the top
*/

void	init_ray_2(t_ray *ray)
{
	if (ray->r_dir_x < 0)
	{
		ray->increm_x = -1;
		ray->r_len_x = (ray->p_dx_pos - ((double)ray->p_check_x))
			* ray->r_step_x;
	}
	else
	{
		ray->increm_x = 1;
		ray->r_len_x = ((double)(ray->p_check_x + 1) - ray->p_dx_pos)
			* ray->r_step_x;
	}
	if (ray->r_dir_y < 0)
	{
		ray->increm_y = -1;
		ray->r_len_y = (ray->p_dy_pos - (double)ray->p_check_y)
			* ray->r_step_y;
	}
	else
	{
		ray->increm_y = 1;
		ray->r_len_y = ((double)(ray->p_check_y + 1) - ray->p_dy_pos)
			* ray->r_step_y;
	}
}

/*
**	ray->wall_hit = 1 only if the ray hit the wall.
**	while the loop is running the ray->r_length is the distance between the player
**	and the intersetion of the ray with horizontal and vertical lines one after the other.
**	at the end of the loop ray->r_length will be the distance between the player and the wall.
**	if side = 1 the wall is either on the right or the left, else it's on top or bottom.
**	we start by the first intersetion then the second and so on.
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
