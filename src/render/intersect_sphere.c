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
#include <math.h> // For sqrt()

// Helper function to calculate a point along a ray (duplicate for now)
// TODO: Move this to a shared utility file
static t_vector raypoint(t_ray ray, double t)
{
	t_vector point;

	point = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
	return (point);
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
t_collision sphere_ray_collision(t_ray ray, t_sphere sphere)
{
	t_collision	collision_data;
	t_vector	oc;          // Vector from sphere center to ray origin (O - C)
	double		a;
	double		b;
	double		c;
	double		delta;       // Discriminant (b^2 - 4ac)
	double		sqrt_delta;
	double		t0;
	double		t1;
	double		closest_t;

	// 1. Initialize collision data
	collision_data.hit = false;
	collision_data.t = INFINITY; // Use INFINITY as the initial 'no hit' distance
	collision_data.normal = (t_vector){0, 0, 0};
	collision_data.point = (t_vector){0, 0, 0};
	collision_data.color = (t_rgb){0, 0, 0}; // Initialize color

	// 2. Calculate vector oc = O - C
	oc = vec_sub(ray.origin, sphere.center);

	// 3. Calculate quadratic coefficients a, b, c
	// Note: Assuming ray.direction is normalized, a = dot(d, d) = 1.
	// Calculating it explicitly handles non-normalized directions robustly.
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - sphere.radius * sphere.radius;

	// 4. Calculate the discriminant
	delta = b * b - 4.0 * a * c;

	// printf("sphere delta: %f\n", delta);
	// 5. Check if ray misses the sphere
	// if (delta < 0)
	// {
	// 	return (collision_data); // No real roots, no intersection
	// }

	// 6. Calculate potential intersection distances t0 and t1
	sqrt_delta = sqrt(delta);
	t0 = (-b - sqrt_delta) / (2.0 * a);
	t1 = (-b + sqrt_delta) / (2.0 * a);

	// 7. Determine the closest valid intersection point in front of the ray
	closest_t = INFINITY;
	if (t0 > RAY_T_MIN && t0 < RAY_T_MAX) {
		closest_t = t0;
	}
	// Check t1 only if it's valid and potentially closer than t0
	if (t1 > RAY_T_MIN && t1 < RAY_T_MAX && t1 < closest_t) {
		closest_t = t1;
	}

	// 8. If a valid intersection was found
	if (closest_t != INFINITY)
	{
		t_vector hit_to_center_vec;

		collision_data.hit = true;
		collision_data.t = closest_t;
		collision_data.point = raypoint(ray, closest_t);
		// Normal at the hit point is the normalized vector from center to point
		hit_to_center_vec = vec_sub(collision_data.point, sphere.center);
		collision_data.normal = hit_to_center_vec; // Assign the vector
		normalize_vec(&collision_data.normal);    // Normalize it in place
		collision_data.color = sphere.color;
	}
	// Else: No hit within the valid [RAY_T_MIN, RAY_T_MAX) range

	// 9. Return the result
	return (collision_data);
}
