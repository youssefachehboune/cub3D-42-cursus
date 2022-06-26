/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:03:53 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/26 18:33:58 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int struct_allocation(t_mlx *mlx)
{
	mlx->player = malloc(sizeof(t_player));
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if(!mlx->player || !mlx->txt)
		return(1);
	return(0);
}

void init_player_dir(t_mlx *mlx, int x, int y)
{
	if(mlx->file->scene[x][y] == 'N')
		mlx->player->player_dir = M_PI_2;
	else if(mlx->file->scene[x][y] == 'S')
		mlx->player->player_dir = M_PI_2 * 3;
	else if(mlx->file->scene[x][y] == 'W')
		mlx->player->player_dir = 0;
	else if(mlx->file->scene[x][y] == 'E')
		mlx->player->player_dir = M_PI;
}

void init_player(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (mlx->file->scene[i])
	{
		j = 0;
		while (mlx->file->scene[i][j])
		{
			if (ft_strchr("WSNE", mlx->file->scene[i][j]))
			{
				mlx->player->x_pos = i;
				mlx->player->y_pos = j;
				init_player_dir(mlx, i, j);
			}
			j++;
		}
		i++;
	}
}

int txt_adr_ptr(t_mlx *mlx, char *path, int dir)
{
	mlx->txt[dir].txt_ptr = mlx_xpm_file_to_image(mlx->init_ptr, path, &mlx->txt[dir].w , &mlx->txt[dir].h);
	if(!mlx->txt[dir].txt_ptr)
		return(1);
	mlx->txt[dir].txt_adr = mlx_get_data_addr(mlx->txt[dir].txt_ptr, &mlx->txt[dir].bpp, &mlx->txt[dir].len, &mlx->txt[dir].endian);
	if(!mlx->txt[dir].txt_adr)
		return(1);
	
	return(0);
}

int init_txt(t_mlx *mlx)
{
	if(txt_adr_ptr(mlx, ft_strtrim(mlx->file->we, " \n\t"), 0))
		return(1);
	if(txt_adr_ptr(mlx, ft_strtrim(mlx->file->no, " \n\t"), 1))
		return(1);
	if(txt_adr_ptr(mlx, ft_strtrim(mlx->file->ea, " \n\t"), 2))
		return(1);
	if(txt_adr_ptr(mlx, ft_strtrim(mlx->file->so, " \n\t"), 3))
		return(1);
	return(0);
}

int init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->file = file;
	mlx->player = NULL;
	mlx->txt = NULL;
	mlx->win = NULL;
	mlx->init_ptr  = mlx_init();
	if(!mlx->init_ptr)
		return(1);
	if(struct_allocation(mlx))
		return(1);
	init_player(mlx);
	if(init_txt(mlx))
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
/////////////////***//////////////
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
	mlx_loop(mlx.init_ptr);
	return (0);
}
