/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:29:19 by yachehbo          #+#    #+#             */
/*   Updated: 2022/06/29 18:12:21 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_dir(t_mlx *mlx, int x, int y)
{
	if (mlx->file->scene[x][y] == 'N')
		mlx->player->player_dir = M_PI_2;
	else if (mlx->file->scene[x][y] == 'S')
		mlx->player->player_dir = M_PI_2 * 3;
	else if (mlx->file->scene[x][y] == 'W')
		mlx->player->player_dir = 0;
	else if (mlx->file->scene[x][y] == 'E')
		mlx->player->player_dir = M_PI;
}

void	init_player(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->file->scene[i])
	{
		j = 0;
		while (mlx->file->scene[i][j])
		{
			if (ft_strchr("WSNE", mlx->file->scene[i][j]))
			{
				mlx->player->x_pos = i;
				mlx->player->dx_pos = (double)i + 0.5;
				mlx->player->y_pos = j;
				mlx->player->dy_pos = (double)j + 0.5;
				init_player_dir(mlx, i, j);
			}
			j++;
		}
		i++;
	}
}

int	txt_adr_ptr(t_mlx *mlx, char *path, t_txt txt)
{
	txt.txt_ptr = mlx_xpm_file_to_image(mlx->init_ptr,
			path, &txt.w, &txt.h);
	if (!txt.txt_ptr)
		return (1);
	txt.txt_adr = mlx_get_data_addr(txt.txt_ptr, &txt.bpp,
			&txt.len, &txt.endian);
	if (!txt.txt_adr)
		return (1);
	return (0);
}

int	init_txt(t_mlx *mlx)
{
	if (txt_adr_ptr(mlx, mlx->file->we, mlx->txt[0]))
		return (1);
	else if (txt_adr_ptr(mlx, mlx->file->no, mlx->txt[1]))
		return (1);
	else if (txt_adr_ptr(mlx, mlx->file->ea, mlx->txt[2]))
		return (1);
	else if (txt_adr_ptr(mlx, mlx->file->so, mlx->txt[3]))
		return (1);
	return (0);
}

int	init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->file = file;
	mlx->player = NULL;
	mlx->txt = NULL;
	mlx->win = NULL;
	mlx->ray = NULL;
	mlx->init_ptr = mlx_init();
	if (!mlx->init_ptr)
		return (1);
	if (struct_allocation(mlx))
		return (1);
	init_player(mlx);
	if (init_txt(mlx))
		return (1);
	mlx->win = mlx_new_window(mlx->init_ptr, WIN_W, WIN_H, "Cub3D");
	if (!mlx->win)
		return (1);
	return (0);
}
