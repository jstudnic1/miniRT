/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-06 12:17:20 by smelicha          #+#    #+#             */
/*   Updated: 2025-05-06 12:17:20 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

t_vector	rotate_y(t_vector v, double angle_rad)
{
	t_vector	result;
	double		cos_a;
	double		sin_a;

	cos_a = cos(angle_rad);
	sin_a = sin(angle_rad);
	result.x = cos_a * v.x + sin_a * v.z;
	result.y = v.y;
	result.z = -sin_a * v.x + cos_a * v.z;
	return (result);
}

t_vector	rotate_z(t_vector v, double angle_rad)
{
	t_vector	result;
	double		cos_a;
	double		sin_a;

	cos_a = cos(angle_rad);
	sin_a = sin(angle_rad);
	result.x = cos_a * v.x - sin_a * v.y;
	result.y = sin_a * v.x + cos_a * v.y;
	result.z = v.z;
	return (result);
}
