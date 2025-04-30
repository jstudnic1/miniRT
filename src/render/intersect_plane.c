/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:51:03 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/07 18:10:46 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

// Helper function to calculate a point along a ray
static t_vector	raypoint(t_ray ray, double t)
{
	t_vector	point;

	point = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
	return (point);
}

static t_collision	init_collision(void)
{
	t_collision	collision_data;

	collision_data.hit = false;
	collision_data.t = INFINITY;
	collision_data.normal = (t_vector){0, 0, 0};
	collision_data.point = (t_vector){0, 0, 0};
	collision_data.color = (t_rgb){0, 0, 0};
	return (collision_data);
}

t_collision	plane_ray_collision(t_ray ray, t_plane plane)
{
	t_collision	collision_data;
	double		denominator;
	double		numerator;
	double		t;
	t_vector	p0_minus_ray_origin;

	collision_data = init_collision();
	denominator = dot_product(ray.direction, plane.normal);
	if (fabs(denominator) < EPSILON)
		return (collision_data);
	p0_minus_ray_origin = vec_sub(plane.point, ray.origin);
	numerator = dot_product(p0_minus_ray_origin, plane.normal);
	t = numerator / denominator;
	if (t > RAY_T_MIN && t < RAY_T_MAX)
	{
		collision_data.hit = true;
		collision_data.t = t;
		collision_data.point = raypoint(ray, t);
		collision_data.normal = plane.normal;
		collision_data.color = plane.color;
	}
	return (collision_data);
}

/**
 * @brief Calculates the intersection of a ray with a plane.
 *
 * Plane equation: (P - P0) . n = 0
 * Ray equation: R(t) = O + t*d
 * Substitute R(t) for P: (O + t*d - P0) . n = 0
 * Solve for t: t = ((P0 - O) . n) / (d . n)
 *
 * Where:
 *  P0 is a point on the plane (plane->point)
 *  n is the normal vector of the plane (plane->normal, assumed normalized)
 *  O is the ray origin (ray->origin)
 *  d is the ray direction (ray->direction, assumed normalized)
 *  . is the dot product
 *
 * @param ray The ray to intersect with the plane.
 * @param plane The plane to check for intersection.
 * @param t_max Current max t value (closest intersection found so far).
 *              Ensures we only return closer intersections.
 * @return double Distance 't' along the ray to the intersection,
 *         or RAY_T_MAX if no intersection in range [RAY_T_MIN, t_max).
 */
