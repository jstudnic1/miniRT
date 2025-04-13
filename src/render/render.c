/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:08 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/13 13:28:33 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

/**
 * @brief Creates ray from camera through the pixel in a view plane,
 checks if it hits object and returns value of the pixel
 * 
 * @param x 
 * @param y 
 * @param scene 
 * @return t_rgb 
 */
// static t_rgb	get_pixel_val(int x, int y, t_scene scene)
// {
// 	t_rgb	pixel_value;
// 	//TODO
// 	return (pixel_value);
// }


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
	uint32_t		color = 125843;

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
			mlx_put_pixel(data->window.image, x, y, color);
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
