/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:31:25 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 16:24:37 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <stdint.h>
#include <stdint.h>

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
	mlx_image_to_window(window->mlx, window->image, 0, 0);
	window->data->rendering = render_restart;
}

void	exit_routine(t_window *window)
{
	mlx_delete_image(window->mlx, window->image);
	window->image = NULL;
	window->mlx = NULL;
	if (window->data->scene->lights)
		free(window->data->scene->lights);
	if (window->data->scene->planes)
		free(window->data->scene->planes);
	if (window->data->scene->spheres)
		free(window->data->scene->spheres);
	if (window->data->scene->cylinders)
		free(window->data->scene->cylinders);
	if (window->data->scene)
		free(window->data->scene);
	return ;
}

void	refresh_routine(t_window *window)
{
	mlx_image_to_window(window->mlx, window->image, 0, 0);
}

void	loop(void *param)
{
	t_window	*window;

	window = param;
	render(window->data);
	if (window->exit)
		mlx_close_window(window->mlx);
	if (window->data->rendering == render_finished)
		usleep(200000);
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
	mlx_loop(window->mlx);
	exit_routine(window);
	return (0);
}
