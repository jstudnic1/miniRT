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

static void	update_plane_hit(
	t_collision *data, double t, t_ray ray, t_plane plane)
{
	data->hit = true;
	data->t = t;
	data->point = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
	data->normal = plane.normal;
	data->color = plane.color;
}

t_collision	plane_ray_collision(t_ray ray, t_plane plane)
{
	t_collision	collision_data;
	double		denominator;
	double		numerator;
	double		t;
	t_vector	p0_minus_ray_origin;

	collision_data.hit = false;
	collision_data.t = INFINITY;
	collision_data.normal = (t_vector){0, 0, 0};
	collision_data.point = (t_vector){0, 0, 0};
	collision_data.color = (t_rgb){0, 0, 0};
	denominator = dot_product(ray.direction, plane.normal);
	if (fabs(denominator) < EPSILON)
		return (collision_data);
	p0_minus_ray_origin = vec_sub(plane.point, ray.origin);
	numerator = dot_product(p0_minus_ray_origin, plane.normal);
	t = numerator / denominator;
	if (t > RAY_T_MIN && t < RAY_T_MAX)
	{
		update_plane_hit(&collision_data, t, ray, plane);
	}
	return (collision_data);
}
