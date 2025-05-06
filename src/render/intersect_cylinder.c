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
		- pow(params->cylinder.diameter / 2.0, 2);
	params->q->discriminant = params->q->b * params->q->b
		- 4 * params->q->a * params->q->c;
}

// Helper function to check intersection with a single cap
static void intersect_single_cap(t_cyl_hit_params *params, t_vector cap_center, t_vector cap_normal)
{
	double	t;
	t_vector	p_intersect;
	t_vector	vec_to_intersect;
	double	denom;
	double	radius_sq;

	radius_sq = pow(params->cylinder.diameter / 2.0, 2);
	denom = dot_product(params->ray.direction, cap_normal);

	// Check if ray is parallel to the cap plane
	if (fabs(denom) < EPSILON)
		return;

	t = dot_product(vec_sub(cap_center, params->ray.origin), cap_normal) / denom;

	// Check if intersection is valid and closer than previous hits
	if (t < RAY_T_MIN || t >= params->closest_hit->t)
		return;

	p_intersect = raypoint(params->ray, t);
	vec_to_intersect = vec_sub(p_intersect, cap_center);

	// Check if intersection point is within the cap's radius
	if (dot_product(vec_to_intersect, vec_to_intersect) <= radius_sq)
	{
		params->closest_hit->t = t;
		params->closest_hit->hit = true;
		params->closest_hit->point = p_intersect;
		params->closest_hit->normal = cap_normal; // Normal is the cap's normal
		params->closest_hit->color = params->cylinder.color;
	}
}

// Placeholder function
static void	check_caps(t_cyl_hit_params *params)
{
	t_vector	top_cap_center;
	t_vector	bottom_cap_center;
	t_vector	top_cap_normal;
	t_vector	bottom_cap_normal;
	double		half_height;

	half_height = params->cylinder.height / 2.0;

	// Top cap
	top_cap_center = vec_add(params->cylinder.center,
		vec_mult_scalar(params->cylinder.axis, half_height));
	top_cap_normal = params->cylinder.axis; // Normal points along the axis
	intersect_single_cap(params, top_cap_center, top_cap_normal);

	// Bottom cap
	bottom_cap_center = vec_sub(params->cylinder.center,
		vec_mult_scalar(params->cylinder.axis, half_height));
	// Normal points opposite to the axis
	bottom_cap_normal = vec_mult_scalar(params->cylinder.axis, -1.0);
	intersect_single_cap(params, bottom_cap_center, bottom_cap_normal);
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
	// Check cylinder sides first
	if (params->q->t0 > RAY_T_MIN)
		check_single_side_hit(params->q->t0, params);
	if (params->q->t1 > RAY_T_MIN)
		check_single_side_hit(params->q->t1, params);

	// Then check caps, potentially overwriting side hit if cap is closer
	check_caps(params);
}

t_collision	cylinder_ray_collision(t_ray ray, t_cylinder cylinder)
{
	t_collision			closest_hit;
	t_quadratic			q;
	t_vector			oc;
	t_cyl_hit_params	params;

	params.ray = ray;
	params.cylinder = cylinder;
	params.closest_hit = &closest_hit;
	params.q = &q;
	params.oc = &oc;
	closest_hit = init_collision();
	calculate_cylinder_quadratic(&params);
	if (!solve_quadratic(params.q))
	{
		// If no intersection with infinite cylinder, only check caps
		check_caps(&params);
		return (closest_hit);
	}
	process_cylinder_hits(&params);
	return (closest_hit);
}
