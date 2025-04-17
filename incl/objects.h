/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:37:11 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/06 11:08:04 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "color.h"
// #include <cstdint>
#include <stdbool.h>
#include <stdint.h>

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
	double		t_min;
	double		t_max;
}			t_ray;

typedef struct s_plane
{
	t_vector	point;     // A point on the plane
	t_vector	normal;    // The normal vector to the plane
	t_rgb		color;     // Color of the plane
} t_plane;

typedef struct s_sphere
{
	t_vector	center;    // Center point of the sphere
	double		radius;    // Radius of the sphere
	t_rgb		color;     // Color of the sphere
} t_sphere;

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
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	int			num_lights;
	int			num_planes;
	int			num_spheres;
	int			num_cylinders;
	uint32_t	*width_pixels;
	uint32_t	*height_pixels;
	bool		ambient_parsed;
	bool		camera_parsed;
}				t_scene;

/**
 * @brief Holds information about a ray-object intersection.
 *
 * @param hit Boolean indicating if an intersection occurred.
 * @param t Distance along the ray to the intersection point.
 * @param point The coordinates (x, y, z) of the intersection point.
 * @param normal The surface normal vector at the intersection point.
 * @param color The color of the object at the intersection point.
 */
typedef struct s_collision
{
	bool		hit;
	double		t;
	t_vector	point;
	t_vector	normal;
	t_rgb		color;
	// Add pointer to the object hit? (optional)
}			t_collision;

#endif
