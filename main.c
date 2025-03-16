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
	data->window.mlx = NULL;
	data->window.image = NULL;
	data->window.width = 640;
	data->window.height = 480;
	data->scene = NULL;
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 1)
		return (0);
	data_init(&data);
	scene_init(&data, argv);
	deploy_threads(&data);
	window_init(&data.window);
	if (data.window.image)
		mlx_delete_image(data.window.mlx, data.window.image);
	return (0);
}
