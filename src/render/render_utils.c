/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:00 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/14 16:00:00 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

/**
 * @brief Calculates a point along a ray at distance t.
 *
 * @param ray The ray.
 * @param t The distance along the ray.
 * @return t_vector The calculated point.
 */
t_vector	raypoint(t_ray ray, double t)
{
	t_vector	point;

	point = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
	return (point);
}

/**
 * @brief Initializes a t_collision struct to default 'no hit' values.
 *
 * @return t_collision The initialized struct.
 */
t_collision	init_collision(void)
{
	t_collision	collision_data;

	collision_data.hit = false;
	collision_data.t = INFINITY;
	collision_data.normal = (t_vector){0, 0, 0};
	collision_data.point = (t_vector){0, 0, 0};
	collision_data.color = (t_rgb){0, 0, 0};
	return (collision_data);
}

/**
 * @brief Solves the quadratic equation at^2 + bt + c = 0.
 * Assumes coefficients and discriminant are pre-calculated in q.
 *
 * @param q Pointer to t_quadratic struct holding coefficients and results.
 * @return true If real roots exist.
 * @return false If no real roots or a is near zero.
 */
bool	solve_quadratic(t_quadratic *q)
{
	if (fabs(q->a) < EPSILON || q->discriminant < 0)
		return (false);
	q->sqrt_discriminant = sqrt(q->discriminant);
	q->t0 = (-q->b - q->sqrt_discriminant) / (2.0 * q->a);
	q->t1 = (-q->b + q->sqrt_discriminant) / (2.0 * q->a);
	return (true);
}
