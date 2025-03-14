/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:32:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:18:32 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minirt.h"

t_rgb	create_rgb(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int	validate_rgb(t_rgb color)
{
	return (color.r >= 0 && color.r <= 255
		&& color.g >= 0 && color.g <= 255
		&& color.b >= 0 && color.b <= 255);
} 