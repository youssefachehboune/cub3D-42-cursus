/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_something.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:08:20 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/09 15:59:36 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	continue_filling_lst(t_file *file, t_list *lst, char *line, int fd)
{
	int	i;

	while (line)
	{
		i = -1;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[++i])
			if (!ft_isascii(line[i]))
				return (printf("Error\nUnvalid chars\n"), free(line), 1);
		lst = ft_lstnew(line);
		if (!lst)
			return (perror("Error\nmalloc"), ft_lstclear(&file->map, free), 1);
		ft_lstadd_back(&file->map, lst);
	}
	return (0);
}

int	fill_lst(t_file *file, int fd)
{
	t_list	*lst;
	char	*line;
	int		i;

	i = -1;
	lst = NULL;
	line = get_next_line(fd);
	if (!line)
		return (perror("Error\nmalloc"), 1);
	while (line[++i])
		if (!ft_isascii(line[i]))
			return (printf("Error\nUnvalid chars\n"), free(line), 1);
	file->map = ft_lstnew(line);
	if (!file->map)
		return (perror("Error\nmalloc"), free(line), 1);
	if (continue_filling_lst(file, lst, line, fd))
		return (1);
	if (close(fd) == -1)
		return (perror("Error\nclose"), 1);
	return (0);
}

int	fill_scene(t_file *file)
{
	int	i;

	i = 0;
	file->scene = malloc((ft_lstsize(file->map) + 1) * sizeof(char *));
	if (!file->scene)
		return (1);
	while (file->map)
	{
		file->height++;
		file->scene[i] = ft_strtrim(file->map->content, "\n");
		ft_lstdelone(file->map, free);
		if (!file->scene[i])
			return (1);
		file->map = file->map->next;
		i++;
	}
	file->scene[i] = NULL;
	return (0);
}

int	fill_ceilling(t_file *file, char c, int color)
{
	if (c == 'C')
	{
		if (file->ceilling != -1)
			return (printf("Error\nMany ceilling colors\n"), 1);
		file->ceilling = color;
	}
	else if (c == 'F')
	{
		if (file->floor != -1)
			return (printf("Error\nMany floor colors\n"), 1);
		file->floor = color;
	}
	return (0);
}

int	fill_textures(t_file *file, char **str)
{
	if (!ft_strncmp(str[0], "NO", 2))
	{
		if (file->no)
			return (printf("Error\nMany NO textures\n"), 1);
		file->no = ft_strdup(str[1]);
	}
	else if (!ft_strncmp(str[0], "SO", 2))
	{
		if (file->so)
			return (printf("Error\nMany SO textures\n"), 1);
		file->so = ft_strdup(str[1]);
	}
	else if (!ft_strncmp(str[0], "WE", 2))
	{
		if (file->we)
			return (printf("Error\nMany WE textures\n"), 1);
		file->we = ft_strdup(str[1]);
	}
	else if (!ft_strncmp(str[0], "EA", 2))
	{
		if (file->ea)
			return (printf("Error\nMany EA textures\n"), 1);
		file->ea = ft_strdup(str[1]);
	}
	return (0);
}
