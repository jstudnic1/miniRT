/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:08 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/13 13:10:25 by smelicha         ###   ########.fr       */
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


	mlx_put_pixel(data->window.image, x, y, color);
	if (x < data->window.width)
		x++;
	else
	{
		x = 0;
		y++;
	}
	if (y < data->window.height)
		return (1);
	data->rendering = false;
	return (0);
}
