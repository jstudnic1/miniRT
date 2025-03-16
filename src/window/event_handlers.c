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

void	key_handler(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = param;
	printf("Key handler called\n");
	if (key.key == MLX_KEY_ESCAPE)
	{
		printf("esc pressed\n");
		mlx_delete_image(data->window.mlx, data->window.image);
		data->window.image = NULL;
		mlx_close_window(data->window.mlx);
		data->window.mlx = NULL;
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
