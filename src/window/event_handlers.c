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

void	key_handler(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->window.mlx, MLX_KEY_ESCAPE))
	{
		printf("esc pressed\n");
		mlx_close_window(data->window.mlx);
	}
}
