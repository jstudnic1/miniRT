/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 13:31:25 by smelicha          #+#    #+#             */
/*   Updated: 2025-03-15 13:31:25 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <stdint.h>
#include <stdint.h>

void	test_image_fill(t_window *window)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	x = 0;
	y = 0;
	color = 0;
	while (y < window->height)
	{
		while (x < window->width)
		{
			mlx_put_pixel(window->image, x, y, color++);
			if (color == UINT32_MAX)
				color = 0;
			printf("x: %i, x_max: %i, y: %i, y_max %i, color %u\n", x, window->width, y, window->height, color);
			x++;
		}
		mlx_image_to_window(window->mlx, window->image, 0, 0);
		x = 0;
		y++;
	}
}

void	resize_handler(int new_x, int new_y, void *param)
{
	t_window	*window;

	window = param;
	if (window->height == (uint32_t)new_y && window->width == (uint32_t)new_y)
		return ;
	window->width = new_x;
	window->height = new_y;
	mlx_delete_image(window->mlx, window->image);
	window->image = mlx_new_image(window->mlx, new_x, new_y);
	test_image_fill(window);
}

int	window_init(t_data *data)
{
	data->window.mlx = mlx_init(data->window.width, data->window.height, "miniRT", 1);
	mlx_loop_hook(data->window.mlx, key_handler, &data);
	mlx_resize_hook(data->window.mlx, resize_handler, &data->window);
	data->window.image = mlx_new_image(data->window.mlx, data->window.width, data->window.height);
	mlx_image_to_window(data->window.mlx, data->window.image, 0, 0);
	test_image_fill(&data->window);
	printf("before mlx loop\n");
	mlx_loop(data->window.mlx);
	printf("after mlx loop\n");
	return (0);
}
