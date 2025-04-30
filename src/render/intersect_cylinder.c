/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:51:03 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/08 14:30:00 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <math.h> // For sqrt()

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

static void	calculate_cylinder_quadratic(t_cyl_hit_params *params)
{
	*(params->oc) = vec_sub(params->ray.origin, params->cylinder.center);
	params->q->a = dot_product(params->ray.direction, params->ray.direction)
		- pow(dot_product(params->ray.direction, params->cylinder.axis), 2);
	params->q->b = 2.0 * (dot_product(params->ray.direction, *(params->oc))
		- dot_product(params->ray.direction, params->cylinder.axis)
		* dot_product(*(params->oc), params->cylinder.axis));
	params->q->c = dot_product(*(params->oc), *(params->oc))
		- pow(dot_product(*(params->oc), params->cylinder.axis), 2)
		- params->cylinder.radius * params->cylinder.radius;
	params->q->discriminant = params->q->b * params->q->b
		- 4 * params->q->a * params->q->c;
}

static bool	solve_quadratic(t_quadratic *q)
{
	if (fabs(q->a) < EPSILON || q->discriminant < 0)
		return (false);
	q->sqrt_discriminant = sqrt(q->discriminant);
	q->t0 = (-q->b - q->sqrt_discriminant) / (2.0 * q->a);
	q->t1 = (-q->b + q->sqrt_discriminant) / (2.0 * q->a);
	return (true);
}

// Placeholder function
static bool	check_caps(t_cyl_hit_params *params)
{
	(void)params;
	return (false);
}

static void	check_single_side_hit(double t, t_cyl_hit_params *params)
{
	t_vector	p;
	t_vector	normal_at_hit;
	double		m;

	m = dot_product(params->ray.direction, params->cylinder.axis) * t
		+ dot_product(*(params->oc), params->cylinder.axis);
	if (t >= RAY_T_MIN && t < params->closest_hit->t
		&& m >= -params->cylinder.height / 2.0
		&& m <= params->cylinder.height / 2.0)
	{
		params->closest_hit->t = t;
		params->closest_hit->hit = true;
		p = raypoint(params->ray, t);
		params->closest_hit->point = p;
		normal_at_hit = vec_sub(p, params->cylinder.center);
		normal_at_hit = vec_sub(normal_at_hit,
				vec_mult_scalar(params->cylinder.axis,
					dot_product(vec_sub(p, params->cylinder.center),
									params->cylinder.axis)));
		params->closest_hit->normal = vec_normalize(normal_at_hit);
		params->closest_hit->color = params->cylinder.color;
	}
}

static void	process_cylinder_hits(t_cyl_hit_params *params)
{
	check_single_side_hit(params->q->t0, params);
	check_single_side_hit(params->q->t1, params);
	check_caps(params);
}

t_collision	cylinder_ray_collision(t_ray ray, t_cylinder cylinder)
{
	t_collision	closest_hit;
	t_quadratic	q;
	t_vector	oc;
	t_cyl_hit_params	params;

	params.ray = ray;
	params.cylinder = cylinder;
	params.closest_hit = &closest_hit;
	params.q = &q;
	params.oc = &oc;
	closest_hit = init_collision();
	calculate_cylinder_quadratic(&params);
	if (!solve_quadratic(&q))
	{
		check_caps(&params);
		return (closest_hit);
	}
	process_cylinder_hits(&params);
	return (closest_hit);
}
