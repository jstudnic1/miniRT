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

/**
 * @brief Calls parser and validates input file
 TODO test the working state of the parser
 * 
 * @param data main data struct
 * @param argv command line argument
 * @return int 0 - OK, -1 - NOK
 */
int	scene_init(t_data *data, char **argv)
{
	if (double_array_length(argv) != 2)
		return (-1);
	data->scene = parse_scene(argv[1]);
	printf("scene poiner: %p\n", data->scene);
	print_scene(data->scene);
	return (0);
}

void	data_init(t_data *data)
{
	data->window.mlx = NULL;
	data->window.image = NULL;
	data->window.width = 640;
	data->window.height = 480;
	data->scene = NULL;
	data->window.exit = false;
	data->window.data = data;
}

/**
 * @brief 
 TODO check for returns of the functions like scene init which should validate the input file, perhaps make an "development check exception"
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	data_init(&data);
	scene_init(&data, argv);
	deploy_threads(&data);
	window_init(&data.window);
	if (data.window.image)
		mlx_delete_image(data.window.mlx, data.window.image);
	return (0);
}
