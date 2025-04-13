/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:31:25 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/13 13:39:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <stdint.h>
#include <stdint.h>

/**
 * @brief Dummy function, just to put some distinctive pixels to the image
 * 
 * @param window 
 */
void	test_image_fill(t_window *window)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	x = 0;
	y = 0;
	color = 2;
	while (y < window->height)
	{
		while (x < window->width)
		{
			mlx_put_pixel(window->image, x, y, color);
			color += 10000;
			if (color > (UINT32_MAX - 2000))
				color = 2;
			// printf("x: %i, x_max: %i, y: %i, y_max %i, color %u\n", x, window->width, y, window->height, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(window->mlx, window->image, 0, 0);
}

/**
 * @brief Updates the image based on the new window resolution
 * 
 * @param new_x - new width
 * @param new_y - new height
 * @param param - pointer to window struct
 */
void	resize_handler(int new_x, int new_y, void *param)
{
	t_window	*window;

	window = param;
	if (window->height == (uint32_t)new_y && window->width == (uint32_t)new_y)
		return ;
	window->width = new_x;
	window->height = new_y;
	mlx_delete_image(window->mlx, window->image);
	window->image = NULL;
	window->image = mlx_new_image(window->mlx, new_x, new_y);
	window->data->rendering = render_restart;
}

void	exit_routine(t_window *window)
{
	mlx_delete_image(window->mlx, window->image);
	window->image = NULL;
	mlx_close_window(window->mlx);
	window->mlx = NULL;
	return ;
}

void	refresh_routine(t_window *window)
{
	mlx_image_to_window(window->mlx, window->image, 0, 0);
}

void	loop(void *param)
{
	t_window	*window;
	uint64_t	current_ts;
	static uint64_t	refresh_ts;

	window = param;
	current_ts = ft_get_time();
	if (refresh_ts == 0)
	{
		refresh_ts = current_ts + 100000;
		return ;
	}
	render(window->data);
	if (current_ts > refresh_ts)
	{
		refresh_routine(window);
		refresh_ts = current_ts + 1000000;
	}
	if (window->exit)
		exit_routine(window);
	if (window->data->rendering == render_finished)
		usleep(20000);
}

/**
 * @brief Creates window and image of size defined by width and height
 * 
 * @param window - data struct with data about window
 * @return int 0 - success, -1 - fail
 */
int	window_init(t_window *window)
{
	window->mlx = mlx_init(window->width, window->height, "miniRT", 1);
	mlx_key_hook(window->mlx, key_handler, window);
	mlx_resize_hook(window->mlx, resize_handler, window);
	mlx_loop_hook(window->mlx, loop, window);
	window->image = mlx_new_image(window->mlx, window->width, window->height);
	mlx_image_to_window(window->mlx, window->image, 0, 0);
	// test_image_fill(window);
	printf("before mlx loop\n");
	mlx_loop(window->mlx);
	printf("after mlx loop\n");
	return (0);
}
