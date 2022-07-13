/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:03:53 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/07/13 16:59:15 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_file *file)
{
	file->ceilling = -1;
	file->floor = -1;
	file->ea = 0;
	file->no = 0;
	file->so = 0;
	file->we = 0;
	file->height = 0;
}

void	free_2d_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
	free (str);
}

void	free_file(t_file *file)
{
	free(file->no);
	free(file->so);
	free(file->ea);
	free(file->we);
	free_2d_array(file->scene);
}

void	free_all(t_mlx *mlx)
{
	free_file(mlx->file);
	free(mlx->player);
	free(mlx->ray);
	free(mlx->txt);
}

int	main(int ac, char **av)
{
	t_file	file;
	t_mlx	mlx;

	if (parsing(&file, ac, av))
		return (1);
	if (start_mlx(&mlx, &file))
		return (free_all(&mlx), 1);
	mlx_loop(mlx.init_ptr);
	return (free_all(&mlx), 0);
}
