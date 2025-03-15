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
#include <stdint.h>

void	key_handler(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

int	window_init(t_data *data)
{
	data->mlx = mlx_init(640, 480, "Test", 1);
	mlx_loop_hook(data->mlx, key_handler, &data);
	mlx_loop(data->mlx);
	return (0);
}

int	scene_init(t_data *data, char **argv)
{
	printf("");
	if (double_array_length(argv) != 1)
		return (-1);
	data->scene = parse_scene(argv[1]);
	return (0);
}

void	data_init(t_data *data)
{
	data->mlx = NULL;
	data->scene = NULL;
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 1)
		return (0);
	data_init(&data);
	scene_init(&data, argv);
	window_init(&data);
	return (0);
}
