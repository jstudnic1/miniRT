/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:00:00 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/08 10:00:00 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <math.h>

static void	calculate_quadratic(t_ray ray, t_sphere sphere,
						t_quadratic *q, t_vector *oc)
{
	*oc = vec_sub(ray.origin, sphere.center);
	q->a = dot_product(ray.direction, ray.direction);
	q->b = 2.0 * dot_product(*oc, ray.direction);
	q->c = dot_product(*oc, *oc) - sphere.radius * sphere.radius;
	q->discriminant = q->b * q->b - 4 * q->a * q->c;
}

static bool	find_intersection_t(t_quadratic *q)
{
	if (q->discriminant < 0)
		return (false);
	q->sqrt_discriminant = sqrt(q->discriminant);
	q->t1 = (-q->b - q->sqrt_discriminant) / (2.0 * q->a);
	q->t2 = (-q->b + q->sqrt_discriminant) / (2.0 * q->a);
	if (q->t1 >= RAY_T_MIN && q->t1 < RAY_T_MAX)
		q->t = q->t1;
	else if (q->t2 >= RAY_T_MIN && q->t2 < RAY_T_MAX)
		q->t = q->t2;
	else
		return (false);
	if (q->t2 >= RAY_T_MIN && q->t2 < RAY_T_MAX && q->t2 < q->t)
		q->t = q->t2;
	return (true);
}

/**
 * @brief Calculates the intersection of a ray with a sphere.
 *
 * Uses the quadratic formula derived from substituting the ray equation
 * into the sphere equation: ||P - C||^2 = r^2
 * Leads to at^2 + bt + c = 0, where:
 * a = d . d (direction dot direction, should be 1 if normalized)
 * b = 2 * (O - C) . d (origin-center dot direction)
 * c = ||O - C||^2 - r^2
 *
 * @param ray The ray to intersect with the sphere.
 * @param sphere The sphere to check for intersection.
 * @return t_collision A struct containing hit information (hit status,
 *         distance t, intersection point, normal, and color).
 */
t_collision	sphere_ray_collision(t_ray ray, t_sphere sphere)
{
	t_collision	collision_data;
	t_quadratic	q;
	t_vector	oc;
	t_vector	hit_point;

	collision_data = init_collision();
	calculate_quadratic(ray, sphere, &q, &oc);
	if (!find_intersection_t(&q))
		return (collision_data);
	collision_data.hit = true;
	collision_data.t = q.t;
	hit_point = raypoint(ray, q.t);
	collision_data.point = hit_point;
	collision_data.normal = vec_normalize(vec_sub(hit_point, sphere.center));
	collision_data.color = sphere.color;
	return (collision_data);
}
