/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:33:07 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/06 11:34:56 by jstudnic         ###   ########.fr       */
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
	t_data	*data;

	data = param;
	printf("Key handler called\n");
	if (key.key == MLX_KEY_ESCAPE)
	{
		printf("esc pressed\n");
		mlx_close_window(data->window.mlx);
	}
	else if (key.key == MLX_KEY_R)
	{
		printf("telling cores to run\n");
		change_cores_state(data, run);
	}
	else if (key.key == MLX_KEY_S)
	{
		printf("telling cores to stop\n");
		change_cores_state(data, stop);
	}
	else if (key.key == MLX_KEY_F)
	{
		printf("telling cores to finish\n");
		change_cores_state(data, finish);
	}
}
