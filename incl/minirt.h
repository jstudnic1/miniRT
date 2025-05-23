/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:47:15 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:26:47 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "color.h"
# include "objects.h"
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f
# define EPSILON 1e-6

typedef struct s_data	t_data;

typedef enum e_render_state
{
	render_run,
	render_finished,
	render_restart
}	t_e_render_state;

typedef struct s_window
{
	t_data			*data;
	mlx_t			*mlx;
	mlx_image_t		*image;
	uint32_t		width;
	uint32_t		height;
	bool			exit;
	bool			res_change;
}	t_window;

typedef struct s_data
{
	t_window			window;
	t_scene				*scene;
	t_e_render_state	rendering;
}	t_data;

// Structure to hold quadratic equation results for intersections
typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_discriminant;
	double	t0;
	double	t1;
	double	t2;
	double	t;
}	t_quadratic;

// Holds data for cylinder intersection calculations
typedef struct s_cyl_calc
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t0;
	double		t1;
	double		m0;
	double		m1;
	t_vector	p0;
	t_vector	p1;
	t_vector	normal;
}	t_cyl_calc;

// Structure to pass data between cylinder intersection helpers
typedef struct s_cyl_hit_params
{
	t_ray		ray;
	t_cylinder	cylinder;
	t_collision	*closest_hit;
	t_quadratic	*q;
	t_vector	*oc;
}	t_cyl_hit_params;

// Structure to pass data between parser helper functions (ps = parser)
typedef struct s_ps
{
	t_scene	*scene;
	int		fd;
	char	*line;
	int		success;
}	t_ps;

// Structure to pass data between helpre function for getting rgb value of the
// pixel (gpv = get pixel value)
typedef struct s_gpv
{
	t_rgb		pixel_value;
	t_ray		ray;
	t_collision	closest_hit;
	t_collision	current_hit;
	t_vector	view_dir;
	int			i;
}	t_gpv;

// Structure to pass data between helper function for generating the primary
// ray (gpr = generate primary ray)
typedef struct s_gpr
{
	t_ray		ray;
	t_camera	*cam;
	t_vector	cam_forward;
	t_vector	world_up;
	t_vector	cam_right;
	t_vector	cam_up;
	t_vector	direction;
	double		aspect_ratio;
	double		fov_rad;
	double		fov_scale;
	double		ndc_x ;
	double		ndc_y;
	double		screen_x;
	double		screen_y;
}	t_gpr;

/* VECTOR UTILS*/
double		vec_len(t_vector vector);
double		dot_product(t_vector u, t_vector v);
t_vector	cross_product(t_vector u, t_vector v);
double		vec_len2(t_vector vector);
t_vector	create_vector(double x, double y, double z);

/* VECTORS */
t_vector	vec_normalize(t_vector vector);
t_vector	vec_add(t_vector u, t_vector v);
t_vector	vec_sub(t_vector u, t_vector v);
t_vector	vec_mult(t_vector u, t_vector v);
t_vector	vec_div(t_vector u, t_vector v);

/* VECTOR SCALAR OPERATIONS */
t_vector	vec_mult_scalar(t_vector vec, double scalar);

/* VECTOR CHECKS */
bool		is_normalized(t_vector vec);

/* RAYS */
t_ray		create_ray(t_vector origin, t_vector direction);
t_ray		generate_primary_ray(int x, int y, t_scene *scene);

/* RENDERING */
int			render(t_data *data);
void		check_caps(t_cyl_hit_params *params);
t_rgb		calculate_ambient(t_ambient ambient, t_rgb surface_color);
t_rgb		calculate_diffuse(t_light light, t_vector light_dir,
				t_vector normal, t_rgb surface_color);
t_rgb		calculate_lighting(t_collision hit, t_scene *scene,
				t_vector view_dir);
t_ray		generate_primary_ray(int x, int y, t_scene *scene);

/* SCENE PARSER */
t_scene		*parse_scene(char *filename);
void		init_scene(t_scene *scene);
void		free_scene(t_scene *scene);
int			add_light(t_scene *scene, t_light light);
int			add_plane(t_scene *scene, t_plane plane);
int			add_sphere(t_scene *scene, t_sphere sphere);
int			add_cylinder(t_scene *scene, t_cylinder cylinder);
int			validate_scene(t_scene *scene);
int			parse_objects(char *identifier, char **tokens, t_scene *scene);
int			parse_plane(char *line, t_scene *scene);
int			parse_sphere(char *line, t_scene *scene);
int			parse_cylinder(char *line, t_scene *scene);
int			parse_light(char *line, t_scene *scene);
t_vector	parse_vector(char *str);
t_rgb		parse_color(char *str);
int			double_array_length(char **array);
bool		check_filename(char *fn);

/* WINDOW */
int			window_init(t_window *window);
void		key_handler(mlx_key_data_t key, void *param);
t_vector	rotate_z(t_vector v, double angle_rad);
t_vector	rotate_y(t_vector v, double angle_rad);

/* INTERSECTIONS */
t_collision	init_collision(void);
t_collision	plane_ray_collision(t_ray inc_ray, t_plane plane);
t_collision	sphere_ray_collision(t_ray ray, t_sphere sphere);
t_collision	cylinder_ray_collision(t_ray ray, t_cylinder cylinder);
t_collision	plane_ray_collision(t_ray inc_ray, t_plane plane);
t_vector	raypoint(t_ray ray, double t);

/* DEBUG */
void		print_scene(t_scene *scene);
void		print_vector(const char *vec_name, t_vector *vector);

/* RENDER UTILS */
bool		solve_quadratic(t_quadratic *q);

#endif
