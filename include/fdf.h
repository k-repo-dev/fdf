/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:50:00 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 12:17:47 by krepo            ###   ########.fr       */
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

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# define X_ROT_DEFAULT_RAD	0.523599
# define Y_ROT_DEFAULT_RAD	0.523599
# define Z_ROT_DEFAULT_RAD	0.0

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
# define T_KEY 116
# define G_KEY 103
# define RESET_KEY 112

# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

typedef struct s_pixel
{
	float	x;
	float	y;
	float	z;
}	t_pixel;

typedef struct s_app
{
	char	*file_path;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_pixels;
	int		bpp;
	int		line_len;
	int		endian;
	int		matrix_width;
	int		matrix_height;
	float	img_scalar;
	float	x_rot_angle;
	float	y_rot_angle;
	float	z_rot_angle;
	float	z_scalar;
	int		x_move_view;
	int		y_move_view;
	float	proj_min_x;
	float	proj_max_x;
	float	proj_min_y;
	float	proj_max_y;
	t_pixel	**world;
	t_pixel	**screen;
}	t_app;

typedef struct s_line_calc
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
}	t_line_calc;

enum e_error_types
{
	MALLOC_ERR,
	FILETYPE_ERR,
	FD_ERR,
	FDF_STRUCT_ERR,
	MLX_INIT_ERR,
	MLX_WIN_ERR,
	MLX_IMG_ERR,
	PARSING_ERR,
	GET_NEXT_LINE_ERR
};

// Function prototypes fdf.c
void	pixel_to_img(t_app *fdf, int x, int y, int color);

// Function prototypes parse.c
t_pixel	**parse_fdf_file(t_app *fdf);

// Function prototypes parse_utils.c
int		count_matrix_dimensions(t_app *fdf);
void	count_matrix_width(t_app *fdf, char *line);
t_pixel	**init_pixel_matrix(t_app *fdf);
void	save_pixel_cordinates(t_pixel **space, int x, int y, int z);

// Function prototypes draw.c
void	draw_pixel_to_img(t_app *fdf);
void	update_img(t_app *fdf);

// Function prototypes draw_line.c
void	draw_line(t_app *fdf, t_pixel p0, t_pixel p1);

// Function protoypes calculate.c
void	calculate_projection_and_update_bounds(t_app *fdf);
void	calculate_centering_offset(t_app *fdf);

// Function prototypes roations.c
void	rotate_x(t_pixel *point, float angle);
void	rotate_y(t_pixel *point, float angle);
void	rotate_z(t_pixel *point, float angle);

// Function prototypes hooks.c
void	init_hooks(t_app *fdf);
int		mouse_hook(int button, int x, int y, void *param);
int		destroy_notify_hook(void *param);
int		keypress_hook(int keycode, void *param);

// Function prototypes manipulate_view.c
void	move_view(t_app *fdf, int keycode);
void	zoom_view(t_app *fdf, int button);
void	rotate_view(t_app *fdf, int keycode);
void	reset_view_settings(t_app *fdf);
void	reset_view(t_app *fdf);

// Function prototypes memory.c
void	exit_success(t_app *fdf);
void	exit_error(t_app *fdf, int error);
void	free_memory(t_app *fdf);
void	reset_img(t_app *fdf);

#endif
