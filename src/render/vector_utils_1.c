/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:32:23 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 22:35:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

double	vec_len(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

double	dot_product(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}
