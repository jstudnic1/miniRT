/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:33:07 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/06 01:04:42 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

void	vec_print(char *name, t_vector vector)
{
	printf("%s:\tx:%0.3f\ty:%0.3f\tz:%0.3f\n", name, vector.x,
		vector.y, vector.z);
}

static void	key_handler_cont_2(mlx_key_data_t key, t_window *window)
{
	if (key.key == MLX_KEY_PAGE_UP)
	{
		if (window->data->scene->camera.fov > 10.0)
			window->data->scene->camera.fov -= 5.0;
	}
	else if (key.key == MLX_KEY_PAGE_DOWN)
	{
		if (window->data->scene->camera.fov < 175.0)
			window->data->scene->camera.fov += 5.0;
	}
	window->data->rendering = render_restart;
	vec_print("position", window->data->scene->camera.position);
	vec_print("orientation", window->data->scene->camera.orientation);
	printf("FOV: %f\n", window->data->scene->camera.fov);
}

static void	key_handler_cont_1(mlx_key_data_t key, t_window *window)
{
	if (key.key == MLX_KEY_KP_2)
	{
		window->data->scene->camera.orientation = rotate_z(
				window->data->scene->camera.orientation, -0.01);
		window->data->scene->camera.orientation = vec_normalize(
				window->data->scene->camera.orientation);
	}
	else if (key.key == MLX_KEY_KP_4)
	{
		window->data->scene->camera.orientation = rotate_y(
				window->data->scene->camera.orientation, 0.01);
		window->data->scene->camera.orientation = vec_normalize(
				window->data->scene->camera.orientation);
	}
	else if (key.key == MLX_KEY_KP_6)
	{
		window->data->scene->camera.orientation = rotate_y(
				window->data->scene->camera.orientation, -0.01);
		window->data->scene->camera.orientation = vec_normalize(
				window->data->scene->camera.orientation);
	}
	key_handler_cont_2(key, window);
}

static void	key_handler_cont(mlx_key_data_t key, t_window *window)
{
	if (key.key == MLX_KEY_LEFT)
		window->data->scene->camera.position.y -= 0.1;
	else if (key.key == MLX_KEY_RIGHT)
		window->data->scene->camera.position.y += 0.1;
	else if (key.key == MLX_KEY_KP_8)
	{
		window->data->scene->camera.orientation = rotate_z(
				window->data->scene->camera.orientation, 0.01);
		window->data->scene->camera.orientation = vec_normalize(
				window->data->scene->camera.orientation);
	}
	key_handler_cont_1(key, window);
}

/**
 * @brief Handles key presses...
 *
 * @param key
 * @param param
 */
void	key_handler(mlx_key_data_t key, void *param)
{
	t_window	*window;
	t_vector	tmp_vec;

	window = param;
	if (key.key == MLX_KEY_ESCAPE)
		window->exit = true;
	else if (key.key == MLX_KEY_UP)
	{
		tmp_vec = vec_mult_scalar(
				window->data->scene->camera.orientation, 0.1);
		window->data->scene->camera.position = vec_add(
				window->data->scene->camera.position, tmp_vec);
	}
	else if (key.key == MLX_KEY_DOWN)
	{
		tmp_vec = vec_mult_scalar(
				window->data->scene->camera.orientation, 0.1);
		window->data->scene->camera.position = vec_sub(
				window->data->scene->camera.position, tmp_vec);
	}
	key_handler_cont(key, window);
}
