/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:52:49 by jstudnic          #+#    #+#             */
/*   Updated: 2024/06/12 14:26:51 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
