/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_caps.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-06 11:43:55 by smelicha          #+#    #+#             */
/*   Updated: 2025-05-06 11:43:55 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

// Helper function to check intersection with a single cap
static void	intersect_single_cap(t_cyl_hit_params *params,
	t_vector cap_center, t_vector cap_normal)
{
	double		t;
	t_vector	p_intersect;
	t_vector	vec_to_intersect;
	double		denom;
	double		radius_sq;

	radius_sq = pow(params->cylinder.diameter / 2.0, 2);
	denom = dot_product(params->ray.direction, cap_normal);
	if (fabs(denom) < EPSILON)
		return ;
	t = dot_product(vec_sub(cap_center, params->ray.origin),
			cap_normal) / denom;
	if (t < RAY_T_MIN || t >= params->closest_hit->t)
		return ;
	p_intersect = raypoint(params->ray, t);
	vec_to_intersect = vec_sub(p_intersect, cap_center);
	if (dot_product(vec_to_intersect, vec_to_intersect) <= radius_sq)
	{
		params->closest_hit->t = t;
		params->closest_hit->hit = true;
		params->closest_hit->point = p_intersect;
		params->closest_hit->normal = cap_normal;
		params->closest_hit->color = params->cylinder.color;
	}
}

void	check_caps(t_cyl_hit_params *params)
{
	t_vector	top_cap_center;
	t_vector	bottom_cap_center;
	t_vector	top_cap_normal;
	t_vector	bottom_cap_normal;
	double		half_height;

	half_height = params->cylinder.height / 2.0;
	top_cap_center = vec_add(params->cylinder.center,
			vec_mult_scalar(params->cylinder.axis, half_height));
	top_cap_normal = params->cylinder.axis;
	intersect_single_cap(params, top_cap_center, top_cap_normal);
	bottom_cap_center = vec_sub(params->cylinder.center,
			vec_mult_scalar(params->cylinder.axis, half_height));
	bottom_cap_normal = vec_mult_scalar(params->cylinder.axis, -1.0);
	intersect_single_cap(params, bottom_cap_center, bottom_cap_normal);
}
