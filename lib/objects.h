/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:37:11 by jstudnic          #+#    #+#             */
/*   Updated: 2024/06/12 14:25:27 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	double	RAY_T_MIN;
	double	RAY_T_MAX;
}			t_ray;

typedef struct s_plane
{
	t_vector	normal;
	t_vector	point;
	t_rgb		color;
}			t_plane;

#endif
