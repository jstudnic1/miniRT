/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 13:33:07 by smelicha          #+#    #+#             */
/*   Updated: 2025-03-15 13:33:07 by smelicha         ###   ########.fr       */
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

	window = param;
	printf("Key handler called\n");
	if (key.key == MLX_KEY_ESCAPE)
	{
		printf("esc pressed\n");
		window->exit = true;
	}
	else if (key.key == MLX_KEY_R)
	{
		printf("telling cores to run\n");
		change_cores_state(window->data, run);
	}
	else if (key.key == MLX_KEY_S)
	{
		printf("telling cores to stop\n");
		change_cores_state(window->data, stop);
	}
	else if (key.key == MLX_KEY_F)
	{
		printf("telling cores to finish\n");
		change_cores_state(window->data, finish);
	}
}
