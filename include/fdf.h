/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:50:00 by krepo             #+#    #+#             */
/*   Updated: 2025/08/13 10:01:30 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <float.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define Q_KEY 113
# define E_KEY 101
# define R_KEY 114
# define F_KEY 102
# define RESET_KEY 112

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_app
{
	char			*file_path;
	void			*mlx;
	void			*win;
	void			*img;
	char			*pixels;
	int				bpp;
	int				line_len;
	int				endian;
	int				grid_w;
	int				grid_h;
	float			zoom;
	float			x_angle;
	float			y_angle;
	t_point			**world;
	t_point			**screen;
	float			z_scale;
	int				x_center_offset;
	int				y_center_offset;
	int				x_offset;
	int				y_offset;
	float			min_x_proj;
	float			max_x_proj;
	float			min_y_proj;
	float			max_y_proj;
	unsigned int	color;
}	t_app;

typedef struct s_line_vars
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line_vars;

enum e_error_types
{
	MALLOC_ERR,
	FILETYPE_ERR,
	FD_ERR,
	FDF_STRUCT_ERR,
	MLX_INIT_ERR,
	MLX_WIN_ERR,
	MLX_IMG_ERR,
	GRID_ERR,
	PARSING_ERR,
	GET_NEXT_LINE_ERR
};

enum e_coordinate
{
	x,
	y
};

// Function prototypes fdf.c
void	put_pixel(t_app *fdf, int x, int y, int color);

// Function prototypes parse.c
t_point	**parse_map(t_app *fdf);

// Function prototypes parse_utils.c
int		count_grid_dims(t_app *fdf);
void	count_grid_width(t_app *fdf, char *line);
void	save_point_coords(t_point **space, int x, int y, int z);
bool	parse_coords(t_app *fdf, char **coords, int x, int y);

// Function prototypes draw_points.c
void	render_frame(t_app *fdf);
void	draw_point(t_app *fdf, int x, int y);
void	refresh_win(t_app *fdf);

// Function prototypes draw_utils.c
float	deg_to_rad(float deg);
t_point	**init_point_grid(t_app *fdf);

// Function prototypes line_draw.c
void	draw_lines(t_app *fdf);

// Function prototypes line_draw_utils.c
void	set_line_start(t_app *fdf, t_line_vars *line, int x, int y);
void	set_line_end(t_app *fdf, t_line_vars *line, int x, int y);

// Function protoypes proj_calc.c
void	calc_projection(t_app *fdf, int x, int y);
void	calc_bounds(t_app *fdf);
void	calc_center_offset(t_app *fdf);

// Function prototypes input.c
void	setup_input(t_app *fdf);
int		mouse_press(int button, int x, int y, void *param);
int		close_win(void *param);
int		key_press(int keycode, void *param);

// Function prototypes view_control.c
void	move_view(t_app *fdf, int keycode);
void	rotate_view(t_app *fdf, int keycode);
void	reset_view_params(t_app *fdf);
void	change_z_scale(t_app *fdf, int keycode);

// Function prototypes reset.c
void	clear_image(t_app *fdf);
void	reset_view(t_app *fdf);

// Function prototypes mem_and_err.c
void	exit_success(t_app *fdf);
void	exit_error(t_app *fdf, int error);
void	cleanup(t_app *fdf);
void	free_str_array(char ***arr, int i);

// Function prototypes utils.c
void	trim_trailing_whitespace(char *str);
bool	ft_atoi_safe(const char *nptr, int *out);

#endif
