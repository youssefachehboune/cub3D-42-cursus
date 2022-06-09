/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:01:02 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/09 15:59:04 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_first_line(t_file *file)
{
	int	i;

	i = -1;
	while (file->scene[0][++i])
	{
		if (file->scene[0][i] == '0')
			return (1);
	}
	return (0);
}

int	check_last_line(t_file *file)
{
	int	i;

	i = -1;
	while (file->scene[file->height - 1][++i])
	{
		if (file->scene[file->height - 1][i] == '0')
			return (1);
	}
	return (0);
}

int	check_left_wall(t_file *file)
{
	int	i;
	int	j;

	i = 0;
	while (file->scene[i] && file->scene[i][0])
	{
		j = 0;
		while (file->scene[i][j] == ' ' || file->scene[i][j] == '\t')
			j++;
		if (file->scene[i][j] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	check_right_wall(t_file *file)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(file->scene[0]) - 1;
	while (file->scene[i] && file->scene[i][len])
	{
		while (file->scene[i][len] == ' ' || file->scene[i][len] == '\t')
			len--;
		if (file->scene[i][len] == '0')
			return (1);
		i++;
		len = ft_strlen(file->scene[i]) - 1;
	}
	return (0);
}

int	check_middle_lines(t_file *file)
{
	int	i;
	int	j;

	i = -1;
	while (file->scene[++i])
	{
		j = -1;
		while (file->scene[i][++j])
		{
			if ((file->scene[i][j] == ' ' || file->scene[i][j] == '\t')
			&& ((i - 1 >= 0 && file->scene[i - 1][j] == '0')
			|| (i + 1 < file->height && file->scene[i + 1][j] == '0')
			|| (j - 1 >= 0 && file->scene[i][j - 1] == '0')
			|| (j + 1 < (int)ft_strlen(file->scene[i])
			&& file->scene[i][j + 1] == '0')))
				return (1);
		}
	}
	return (0);
}
