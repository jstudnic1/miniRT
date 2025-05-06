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

t_vector	vec_add(t_vector u, t_vector v)
{
	t_vector	sum;

	sum.x = u.x + v.x;
	sum.y = u.y + v.y;
	sum.z = u.z + v.z;
	return (sum);
}

t_vector	vec_sub(t_vector u, t_vector v)
{
	t_vector	sub;

	sub.x = u.x - v.x;
	sub.y = u.y - v.y;
	sub.z = u.z - v.z;
	return (sub);
}

t_vector	vec_mult(t_vector u, t_vector v)
{
	t_vector	mult;

	mult.x = u.x * v.x;
	mult.y = u.y * v.y;
	mult.z = u.z * v.z;
	return (mult);
}

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
