/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:16:23 by jstudnic          #+#    #+#             */
/*   Updated: 2024/06/06 18:07:37 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minirt.h"

double	vec_len(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

double	dot_product(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double cross_product(t_vector u, t_vector v)
{
	t_vector	res;

	return t_vector()
}
