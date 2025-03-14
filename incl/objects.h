/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:37:11 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 15:56:58 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "color.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	double	RAY_T_MIN;
	double	RAY_T_MAX;
}			t_ray;

typedef struct s_plane
{
	t_vector	normal;
	t_vector	point;
	t_rgb		color;
}			t_plane;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	double		brightness;
	t_rgb		color;
}				t_light;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	double		diameter;
	double		height;
	t_rgb		color;
}				t_cylinder;

typedef struct s_ambient
{
	double		intensity;
	t_rgb		color;
}				t_ambient;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			num_lights;
	int			num_planes;
	int			num_cylinders;
}				t_scene;

#endif
