/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:51:03 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/07 17:37:55 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

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
	if (color.r < 0 || color.r > 255 ||
		color.g < 0 || color.g > 255 ||
		color.b < 0 || color.b > 255)
		return (0);
	return (1);
}

/**
 * @brief Converts an t_rgb struct (0-255 components) to a uint32_t
 *        for MLX42 (typically RGBA, with A=255).
 *
 * @param color The t_rgb color struct.
 * @return uint32_t The color packed into a 32-bit integer.
 */
uint32_t	rgb_to_uint32(t_rgb color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	// Clamp RGB values between 0 and 255
	r = (uint8_t)min(max(color.r, 0), 255);
	g = (uint8_t)min(max(color.g, 0), 255);
	b = (uint8_t)min(max(color.b, 0), 255);
	a = 255; // Fully opaque

	// Pack in ARGB order for MLX42
	return ((uint32_t)a << 24 | (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
