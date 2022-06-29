/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:01:02 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/29 14:10:30 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_first_and_last_line(t_file *file)
{
	int	i;
	int	j;

	i = -1;
	while (file->scene[0][++i])
	{
		if (file->scene[0][i] == '0')
			return (1);
	}
	j = -1;
	while (file->scene[file->height - 1][++j])
	{
		if (file->scene[file->height - 1][j] == '0')
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

int	check_middle_lines2(char **scene, int i, int j)
{
	if (scene[i][j - 1] == ' ' || scene[i][j - 1] == '\t'
	|| scene[i][j + 1] == ' ' || scene[i][j + 1] == '\t')
		return (1);
	if ((int)ft_strlen(scene[i - 1]) <= j || (int)ft_strlen(scene[i + 1]) <= j)
		return (1);
	else if (scene[i - 1][j] == ' ' || scene[i - 1][j] == '\t'
	|| scene[i + 1][j] == ' ' || scene[i + 1][j] == '\t')
		return (1);
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
			if (file->scene[i][j] != '1' && file->scene[i][j] != ' '
			&& file->scene[i][j] != '\t'
			&& check_middle_lines2(file->scene, i, j))
				return (1);
		}
	}
	return (0);
}
