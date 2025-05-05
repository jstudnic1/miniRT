/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:33:07 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/05 23:16:07 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

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
	printf("Key handler called; key = %i\n", key.key);
	if (key.key == MLX_KEY_ESCAPE)
	{
		printf("esc pressed\n");
		window->exit = true;
	}
	else if (key.key == MLX_KEY_UP)
	{
		printf("Camera moving up\n");
		tmp_vec = vec_mult_scalar(window->data->scene->camera.orientation, 0.1);
		window->data->scene->camera.position = vec_add(window->data->scene->camera.position, tmp_vec);
		window->data->rendering = render_restart;
	}
	else if (key.key == MLX_KEY_DOWN)
	{
		tmp_vec = vec_mult_scalar(window->data->scene->camera.orientation, 0.1);
		window->data->scene->camera.position = vec_sub(window->data->scene->camera.position, tmp_vec);
		window->data->rendering = render_restart;
		printf("Camera moving down\n");
	}
	else if (key.key == MLX_KEY_LEFT)
	{
		window->data->scene->camera.position.y -= 0.1;
		window->data->rendering = render_restart;
		printf("Camera moving left\n");
	}
	else if (key.key == MLX_KEY_RIGHT)
	{
		window->data->scene->camera.position.y += 0.1;
		window->data->rendering = render_restart;
		printf("Camera moving right\n");
	}
	else if (key.key == MLX_KEY_KP_8)
	{
		window->data->scene->camera.orientation.y += 0.05;
		window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating up\n");
	}
	else if (key.key == MLX_KEY_KP_2)
	{
		window->data->scene->camera.orientation.y -= 0.05;
		window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating down\n");
	}
	else if (key.key == MLX_KEY_KP_4)
	{
		window->data->scene->camera.orientation.z -= 0.05;
		window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating left\n");
	}
	else if (key.key == MLX_KEY_KP_6)
	{
		window->data->scene->camera.orientation.z += 0.05;
		window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating right\n");
	}
}

	// else if (key.key == MLX_KEY_R)
	// {
	// 	printf("telling cores to run\n");
	// 	change_cores_state(window->data, core_run);
	// }
	// else if (key.key == MLX_KEY_S)
	// {
	// 	printf("telling cores to stop\n");
	// 	change_cores_state(window->data, core_stop);
	// }
	// else if (key.key == MLX_KEY_F)
	// {
	// 	printf("telling cores to finish\n");
	// 	change_cores_state(window->data, core_finish);
	// }