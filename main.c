/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-14 17:14:29 by smelicha          #+#    #+#             */
/*   Updated: 2025-03-14 17:14:29 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "incl/minirt.h"

typedef struct s_data
{
	mlx_t	*mlx;
}	t_data;

void	key_handler(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

int main()
{
	t_data	data;

	data.mlx = mlx_init(640, 480, "Test", 1);
	mlx_loop_hook(data.mlx, key_handler, &data);
	mlx_loop(data.mlx);
	return (0);
}