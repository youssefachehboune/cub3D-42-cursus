/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:03:53 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/26 13:17:28 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->file = file;
	mlx->player = NULL;
	mlx->txt = NULL;
	mlx->win = NULL;
	mlx->init_ptr  = mlx_init();
	if(!mlx->init_ptr)
		return(1);
	mlx->win = mlx_new_window(mlx->init_ptr, 1080, 1080, "Cub3D");
	if(!mlx->win)
		return(1);
	return(0);
}

int start_mlx(t_mlx *mlx, t_file *file)
{
	if(init_mlx(mlx, file))
		return(1);
	return(0);
}
////////////////////////////////////////////***//////////////
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

int	main(int ac, char **av)
{
	t_file	file;
	t_mlx	mlx;

	if (parsing(&file, ac, av))
		return (1);
	if (start_mlx(&mlx, &file))
		return (1);
	free_file(&file);
	return (0);
}
