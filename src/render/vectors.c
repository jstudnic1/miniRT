/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:16:26 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:35:12 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

/**
 * @brief Normalizes a vector (makes its length 1) and returns its original
 * length.
 * Usage in MiniRT:
 * - Normalizing ray direction vectors after calculating them
 *   (e.g., from camera).
 * - Normalizing surface normal vectors at intersection points for
 *   lighting calcs.
 * - Normalizing the light vector (from intersection point to light source).
 * - Normalizing the view vector (from intersection point to camera).
 *
 * @param vector The vector to normalize.
 * @return double The original length of the vector.
 */
t_vector	vec_normalize(t_vector vector)
{
	double		len;
	t_vector	normalized_vector;

	len = vec_len(vector);
	if (len == 0.0)
		return (vector);
	normalized_vector.x = vector.x / len;
	normalized_vector.y = vector.y / len;
	normalized_vector.z = vector.z / len;
	return (normalized_vector);
}

/**
 * @brief Adds two vectors component-wise (u + v).
 * Usage in MiniRT:
 * - Calculating a point along a ray:
 *   P = Origin + t * Direction (requires scalar mult first).
 * - Translating points or origins.
 * - Combining color contributions from different lights or components
 *   (ambient + diffuse + specular).
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return t_vector The resulting vector sum.
 */
t_vector	vec_add(t_vector u, t_vector v)
{
	t_vector	sum;

	sum.x = u.x + v.x;
	sum.y = u.y + v.y;
	sum.z = u.z + v.z;
	return (sum);
}

/**
 * @brief Subtracts vector v from vector u component-wise (u - v).
 * Usage in MiniRT:
 * - Finding the direction vector between two points:
 *   Direction = TargetPoint - OriginPoint.
 * - Calculating the light vector: L = LightPosition - IntersectionPoint.
 * - Calculating the view vector: V = CameraPosition - IntersectionPoint.
 * - Used in intersection tests (e.g., ray origin relative to object center).
 *
 * @param u The vector to subtract from.
 * @param v The vector to subtract.
 * @return t_vector The resulting vector difference.
 */
t_vector	vec_sub(t_vector u, t_vector v)
{
	t_vector	sub;

	sub.x = u.x - v.x;
	sub.y = u.y - v.y;
	sub.z = u.z - v.z;
	return (sub);
}

/**
 * @brief Multiplies two vectors component-wise (Hadamard product).
 * Usage in MiniRT:
 * - Color blending: FinalColor.r = SurfaceColor.r * LightColor.r.
 * - Modulating light intensity by surface color in diffuse/specular terms.
 *
 * NOTE: This is NOT the dot product (scalar result) or cross product
 *       (vector result).
 * NOTE: To scale a vector by a scalar 's', use vec_scale(vector, s)
 *       (needs implementation) or vec_mult(vector, create_vector(s, s, s)).
 *
 * @param u The first vector.
 * @param v The second vector.
 * @return t_vector The resulting component-wise product.
 */
t_vector	vec_mult(t_vector u, t_vector v)
{
	t_vector	mult;

	mult.x = u.x * v.x;
	mult.y = u.y * v.y;
	mult.z = u.z * v.z;
	return (mult);
}

/**
 * @brief Divides vector u by vector v component-wise (u / v).
 * Usage in MiniRT:
 * - Less common in basic ray tracing.
 * - Potentially used in advanced techniques or specific color
 *   space conversions.
 *
 * NOTE: Potential division by zero if any component of v is zero.
 *       Needs careful handling.
 *
 * @param u The dividend vector.
 * @param v The divisor vector.
 * @return t_vector The resulting component-wise division.
 */
t_vector	vec_div(t_vector u, t_vector v)
{
	t_vector	div;

	if (v.x == 0.0 || v.y == 0.0 || v.z == 0.0)
		return (create_vector(0.0, 0.0, 0.0));
	div.x = u.x / v.x;
	div.y = u.y / v.y;
	div.z = u.z / v.z;
	return (div);
}
