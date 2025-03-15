/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:47:15 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:27:41 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "color.h"
# include "objects.h"
# include "libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	uint32_t	width;
	uint32_t	height;
}	t_window;

typedef struct s_data
{
	t_window	window;
	t_scene		*scene;
}	t_data;

/* VECTOR UTILS*/
double		vec_len(t_vector vector);
double		dot_product(t_vector u, t_vector v);
t_vector	cross_product(t_vector u, t_vector v);
double		vec_len2(t_vector vector);
t_vector	create_vector(double x, double y, double z);

/* VECTORS */
double		normalize_vec(t_vector *vector);
t_vector	vec_add(t_vector u, t_vector v);
t_vector	vec_sub(t_vector u, t_vector v);
t_vector	vec_mult(t_vector u, t_vector v);
t_vector	vec_div(t_vector u, t_vector v);

/* RAYS */
t_ray		create_ray(t_vector origin, t_vector direction);

/* SCENE PARSER */
t_scene		*parse_scene(char *filename);
void		init_scene(t_scene *scene);
void		free_scene(t_scene *scene);
int			add_light(t_scene *scene, t_light light);
int			add_plane(t_scene *scene, t_plane plane);
int			add_cylinder(t_scene *scene, t_cylinder cylinder);
int			validate_scene(t_scene *scene);
int			parse_objects(char *line, t_scene *scene);
t_vector	parse_vector(char *str);
t_rgb		parse_color(char *str);
int			double_array_length(char **array);

/* WINDOW */
int		window_init(t_data *data);
void	key_handler(void *param);

#endif
