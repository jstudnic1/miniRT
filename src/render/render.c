/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:08 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/14 14:49:12 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <stdint.h>

#define R_SHIFT 24
#define G_SHIFT 16
#define B_SHIFT 8

/**
 * @brief Creates ray from camera through the pixel in a view plane,
 checks if it hits object and returns value of the pixel
 * 
 * @param x 
 * @param y 
 * @param scene 
 * @return t_rgb 
 */
static t_rgb	get_pixel_val(int x, int y, t_scene *scene)
{
	t_rgb	pixel_value;
	//TODO collision check with scene things and get the color of the
	//pixel based on the color of the thing it hit and light or the color
	//of background
	x -= 1;
	x += 1;
	y -= 1;
	y += 1;
	scene++;
	scene--;
	pixel_value.r = 0;
	pixel_value.g = 0;
	pixel_value.b = 250;
	return (pixel_value);
}

static uint32_t	rgb_to_int(t_rgb color)
{
	uint32_t	val;

	val = 0;
	val |= color.r << R_SHIFT;
	val |= color.g << G_SHIFT;
	val |= color.b << B_SHIFT;
	val |= 255;
	return (val);
}

/**
 * @brief Takes scene and its objects, casts rays and puts pixel values
 to the mlx image, checks if the resolution changed and recomputes the image
 if true
 * 
 * @param data 
 * @return int 
 */
int	render(t_data *data)
{
	static uint32_t	x;
	static uint32_t	y;
	t_rgb		color;

	color = get_pixel_val(x, y, data->scene);
	if (data->rendering == render_finished)
		return (0);
	else if (data->rendering == render_restart)
	{
		x = 0;
		y = 0;
		data->rendering = render_run;
	}
	else if (data->rendering == render_run)
	{
		while (x < data->window.width)
		{
			mlx_put_pixel(data->window.image, x, y, rgb_to_int(color));
			x++;
		}
		x = 0;
			y++;
		if (y < data->window.height)
			return (1);
		data->rendering = render_finished;
	}
	return (0);
}
