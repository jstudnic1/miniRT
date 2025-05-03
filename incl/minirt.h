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
/*#include <bits/pthreadtypes.h>*/
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
# define N_THREADS 12
# define EPSILON 1e-6

typedef struct s_data	t_data;

typedef enum e_core_state
{
	core_run,
	core_stop,
	core_finish
}	t_e_core_state;

typedef enum e_render_state
{
	render_run,
	render_finished,
	render_restart
}	t_e_render_state;

/**
 * @brief
 *
 */
typedef struct s_core
{
	pthread_t		tid;
	pthread_mutex_t	*print;
	pthread_mutex_t	state_mtx;
	t_e_core_state	state;
	int				id;
	int				x_start;
	int				y_start;
	int				x_end;
	int				y_end;
}	t_core;

/**
 * @brief
 *
 */
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

/**
 * @brief
 *
 */
typedef struct s_data
{
	t_window			window;
	t_scene				*scene;
	t_e_render_state	rendering;
	t_core				cores[N_THREADS];
	pthread_mutex_t		print;
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

/* WINDOW */
int			window_init(t_window *window);
void		key_handler(mlx_key_data_t key, void *param);

/* THREADS */
int			deploy_threads(t_data *data);
void		change_cores_state(t_data *data, t_e_core_state new_state);

/* INTERSECTIONS */
t_collision	plane_ray_collision(t_ray inc_ray, t_plane plane);
t_collision	sphere_ray_collision(t_ray ray, t_sphere sphere);
t_collision	cylinder_ray_collision(t_ray ray, t_cylinder cylinder);

/* UTILS */
uint64_t	ft_get_time(void);
int			str_comp(const char *str1, const char *str2);

/* DEBUG */
void		print_scene(t_scene *scene);
void		print_vector(const char *vec_name, t_vector *vector);

/* RENDER UTILS */
t_vector	raypoint(t_ray ray, double t);
t_collision	init_collision(void);
bool		solve_quadratic(t_quadratic *q);

// Typedefs for function pointers if needed (example)
// typedef double (*t_intersect_func)(const t_ray *, const void *, double);

#endif
