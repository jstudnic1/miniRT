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
static t_vector raypoint(t_ray ray, double t)
{
	t_vector point;

	point = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
	return (point);
}

// t_collision	plane_ray_collision(t_ray inc_ray, t_sphere sphere)
// {
// 	t_collision collision_data;
// 	//TODO
// 	return (collision_data);
// }

t_collision	plane_ray_collision(t_ray ray, t_plane plane)
{
	t_collision	collision_data;
	double		denominator;
	double		numerator;
	double		t;
	t_vector	p0_minus_ray_origin;
	// static int debug_count = 0;

	collision_data.hit = false;
	collision_data.t = INFINITY;
	collision_data.normal = (t_vector){0, 0, 0};
	collision_data.point = (t_vector){0, 0, 0};
	collision_data.color = (t_rgb){0, 0, 0};

	// Compute the denominator (dot product of ray direction and plane normal)
	denominator = dot_product(ray.direction, plane.normal);

	// Check if ray is parallel to the plane (denominator close to 0)
	if (fabs(denominator) < 0.00001)
	{
		return (collision_data);  // No intersection
	}

	// Compute the numerator (dot product of (plane point - ray origin) and plane normal)
	p0_minus_ray_origin = vec_sub(plane.point, ray.origin);
	numerator = dot_product(p0_minus_ray_origin, plane.normal);

	// Calculate the distance t along the ray
	t = numerator / denominator;

	// Print debug info for the first 5 rays only
	// if (debug_count < 5)
	// {
	// 	printf("=== Plane Intersection Debug #%d ===\n", debug_count++);
	// 	printf("Ray: origin=(%f, %f, %f), direction=(%f, %f, %f)\n",
	// 		ray.origin.x, ray.origin.y, ray.origin.z,
	// 		ray.direction.x, ray.direction.y, ray.direction.z);
	// 	printf("Plane: point=(%f, %f, %f), normal=(%f, %f, %f)\n",
	// 		plane.point.x, plane.point.y, plane.point.z,
	// 		plane.normal.x, plane.normal.y, plane.normal.z);
	// 	printf("Calculation: dot(dir, normal)=%f, dot(point-origin, normal)=%f\n",
	// 		denominator, numerator);
	// 	printf("Result: t=%f\n", t);
	// }

	// Check if intersection is in the valid range (in front of the ray origin)
	if (t > RAY_T_MIN && t < RAY_T_MAX)
	{
		// Valid intersection found
		collision_data.hit = true;
		collision_data.t = t;
		collision_data.point = raypoint(ray, t);
		collision_data.normal = plane.normal;
		collision_data.color = plane.color;

		// if (debug_count <= 5) {
		// 	printf("Hit found at point (%f, %f, %f), t=%f\n\n",
		// 		collision_data.point.x, collision_data.point.y, collision_data.point.z, t);
		// }
	}
	// else if (debug_count <= 5)
	// {
	// 	printf("No hit - t outside valid range [%f, %f]\n\n", RAY_T_MIN, RAY_T_MAX);
	// }

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
 * @param t_max The current maximum allowed t value (closest intersection found so far).
 *              Used to ensure we only return intersections closer than existing ones.
 * @return double The distance 't' along the ray to the intersection point,
 *         or RAY_T_MAX if there is no intersection within the valid range
 *         [RAY_T_MIN, t_max).
 */
/*
double intersect_plane(const t_ray *ray, const t_plane *plane, double t_max)
{
	// 1. Calculate the denominator: dot product of ray direction and plane normal.
	//    double denom = dot_product(ray->direction, plane->normal);

	// 2. Check if the ray is parallel to the plane.
	//    If the absolute value of the denominator is very close to zero (e.g., < 1e-6),
	//    the ray is parallel or lies within the plane. Treat as no intersection.
	//    if (fabs(denom) < 1e-6)
	//        return (RAY_T_MAX); // Or just t_max if using that convention

	// 3. Calculate the numerator: dot product of (plane point - ray origin) and plane normal.
	//    t_vector p0_to_o = vec_sub(plane->point, ray->origin);
	//    double numerator = dot_product(p0_to_o, plane->normal);

	// 4. Calculate t (the distance along the ray).
	//    double t = numerator / denom;

	// 5. Check if the intersection is within the valid range.
	//    The intersection must be in front of the ray (t >= RAY_T_MIN)
	//    and closer than any previously found intersection (t < t_max).
	//    if (t >= RAY_T_MIN && t < t_max)
	//        return (t); // Valid intersection found

	// 6. If not parallel and t is not in the valid range, return no hit.
	//    return (RAY_T_MAX); // Or t_max
}
*/
