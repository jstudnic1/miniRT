/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:16:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:35:47 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <math.h>

t_vector	cross_product(t_vector u, t_vector v)
{
	t_vector	cross;

	cross.x = u.y * v.z - u.z * v.y;
	cross.y = u.z * v.x - u.x * v.z;
	cross.z = u.x * v.y - u.y * v.x;
	return (cross);
}

double	vec_len2(t_vector vector)
{
	return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

t_vector	create_vector(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/**
 * @brief Multiplies each component of a vector by a scalar value.
 *
 * @param vec The vector to scale.
 * @param scalar The scalar value to multiply by.
 * @return t_vector The resulting scaled vector.
 */
t_vector	vec_mult_scalar(t_vector vec, double scalar)
{
	t_vector	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}

/**
 * @brief Checks if a vector is normalized (its length squared is close to 1).
 *
 * @param vec The vector to check.
 * @return bool True if the vector is normalized, false otherwise.
 */
bool	is_normalized(t_vector vec)
{
	double	len_sq;

	len_sq = vec_len2(vec);
	return (fabs(len_sq - 1.0) < EPSILON);
}
