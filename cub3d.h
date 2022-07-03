/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <yachehbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:04:17 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/07/03 18:55:26 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "mlx.h"
# include "math.h"

# define WIN_W	1080
# define WIN_H	1080
# define FOV	60

typedef struct s_ray
{
	double		p_dx_pos;
	double		p_dy_pos;
	int			p_check_x;
	int			p_check_y;
	double		r_dir_x;
	double		r_dir_y;
	double		r_step_x;
	double		r_step_y;
	double		r_len_x;
	double		r_len_y;
	double		r_length;
	int			increm_x;
	int			increm_y;
	int			wall_hit;
	double		hit_x;
	double		hit_y;
	int			side;
	double		wall_len;
	int			wall_height;
} t_ray;


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

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	double	dx_pos;
	double	dy_pos;
	double	player_dir;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}	t_player;

typedef struct s_txt
{
	void    *txt_ptr;
	char    *txt_adr;
	int     w;
	int     h;
	int     bpp;
	int     len;
	int     endian;
}	t_txt;

typedef struct s_mlx
{
	void		*init_ptr;
	void		*win;
	void		*img;
	char		*addr_img;
	int			bpp;
	int			sl;
	int			en;
	t_file		*file;
	t_player	*player;
	t_txt		*txt;
	t_ray		*ray;
}	t_mlx;

int		parsing(t_file *file, int ac, char **av);
void	free_2d_array(char **str);
void	free_file(t_file *file);
int		check_first_and_last_line(t_file *file);
int		check_left_wall(t_file *file);
int		check_right_wall(t_file *file);
int		check_middle_lines(t_file *file);
void	init_vars(t_file *file);
int		fill_scene(t_file *file);
int		fill_lst(t_file *file, int fd);
int		fill_ceilling(t_file *file, char c, int color);
int		fill_textures(t_file *file, char **str);
int		check_elements(t_file *file, char **str);
char	**ft_split2(char *str, char *charset);

void	init_player_dir(t_mlx *mlx, int x, int y);
void	init_player(t_mlx *mlx);
int		init_txt(t_mlx *mlx);
int		init_mlx(t_mlx *mlx, t_file *file);

int		struct_allocation(t_mlx *mlx);
int		txt_adr_ptr(t_mlx *mlx, char *path, int dir);
int		start_mlx(t_mlx *mlx, t_file *file);
int		cast_ray(t_mlx *mlx, t_player *p, t_ray *ray);
int		close_win(t_mlx *mlx);
int		press(int key, t_mlx *mlx);
int		release(int key, t_mlx *mlx);
int update(void *mlx_v);
#endif
