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
	printf("%s:\tx:%0.3f\ty:%0.3f\tz:%0.3f\n", name, vector.x, vector.y, vector.z);
}

static t_vector	rotate_y(t_vector v, double angle_rad)
{
	t_vector result;
	double cos_a = cos(angle_rad);
	double sin_a = sin(angle_rad);

	result.x =  cos_a * v.x + sin_a * v.z;
	result.y =  v.y;
	result.z = -sin_a * v.x + cos_a * v.z;
	return result;
}

static t_vector rotate_z(t_vector v, double angle_rad)
{
	t_vector result;
	double cos_a = cos(angle_rad);
	double sin_a = sin(angle_rad);

	result.x = cos_a * v.x - sin_a * v.y;
	result.y = sin_a * v.x + cos_a * v.y;
	result.z = v.z;
	return result;
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
		window->data->scene->camera.orientation = rotate_z(window->data->scene->camera.orientation, 0.01);
		window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating up\n");
	}
	else if (key.key == MLX_KEY_KP_2)
	{
		window->data->scene->camera.orientation = rotate_z(window->data->scene->camera.orientation, -0.01);
		window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating down\n");
	}
	else if (key.key == MLX_KEY_KP_4)
	{
		window->data->scene->camera.orientation = rotate_y(window->data->scene->camera.orientation, 0.01);
		// window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating left\n");
	}
	else if (key.key == MLX_KEY_KP_6)
	{
		window->data->scene->camera.orientation = rotate_y(window->data->scene->camera.orientation, -0.01);
		// window->data->scene->camera.orientation = vec_normalize(window->data->scene->camera.orientation);
		window->data->rendering = render_restart;
		printf("Camera rotating right\n");
	}
	else if (key.key == MLX_KEY_PAGE_UP)
	{
		if (window->data->scene->camera.fov > 10.0)
			window->data->scene->camera.fov -= 5.0;
		window->data->rendering = render_restart;
	}
	else if (key.key == MLX_KEY_PAGE_DOWN)
	{
		if (window->data->scene->camera.fov < 175.0)
			window->data->scene->camera.fov += 5.0;
		window->data->rendering = render_restart;
	}
	vec_print("position", window->data->scene->camera.position);
	vec_print("orientation", window->data->scene->camera.orientation);
	printf("FOV: %f\n", window->data->scene->camera.fov);
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