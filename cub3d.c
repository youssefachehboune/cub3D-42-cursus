/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:03:53 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/08 18:27:39 by ylabtaim         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_file	file;

	if (parsing(&file, ac, av))
		return (1);
	free_file(&file);
	return (0);
}
