/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:04:17 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/06/08 19:11:54 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_file
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		ceilling;
	int		floor;
	int		height;
	t_list	*map;
	char	**scene;
}	t_file;

int		parsing(t_file *file, int ac, char **av);
void	free_2d_array(char **str);
void	free_file(t_file *file);
int		check_first_line(t_file *file);
int		check_last_line(t_file *file);
int		check_left_wall(t_file *file);
int		check_right_wall(t_file *file);
int		check_middle_lines(t_file *file);
void	init_vars(t_file *file);
int		fill_scene(t_file *file);
int		fill_lst(t_file *file, int fd);
int		fill_ceilling(t_file *file, char c, int color);
int		fill_textures(t_file *file, char **str);
int		check_elements(t_file *file, char **str);

#endif
