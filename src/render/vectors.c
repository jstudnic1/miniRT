/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:16:26 by jstudnic          #+#    #+#             */
/*   Updated: 2024/06/07 10:17:21 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

double	normalize_vec(t_vector *vector)
{
	double	len;

	len = vec_len(*vector);
	vector->x /= len;
	vector->y /= len;
	vector->z /= len;
	return (len);
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

	div.x = u.x / v.x;
	div.y = u.y / v.y;
	div.z = u.z / v.z;
	return (div);
}
