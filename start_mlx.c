/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:34:57 by yachehbo          #+#    #+#             */
/*   Updated: 2022/06/27 09:44:27 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	struct_allocation(t_mlx *mlx)
{
	mlx->player = malloc(sizeof(t_player));
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if (!mlx->player || !mlx->txt)
		return (1);
	return (0);
}

int	start_mlx(t_mlx *mlx, t_file *file)
{
	if (init_mlx(mlx, file))
		return (1);
	return (0);
}
