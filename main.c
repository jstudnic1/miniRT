/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:29 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/13 13:32:20 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "incl/minirt.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define EPSILON if not already defined globally (e.g., in minirt.h)
// #ifndef EPSILON
// # define EPSILON 1e-6
// #endif

/**
 * @brief Calls parser and validates input file
 *
 * @param data main data struct
 * @param filename Path to the scene file.
 * @return int 0 - OK, -1 - Error
 */
int	scene_init(t_data *data, char *filename)
{
	printf("Parsing scene file: %s\n", filename);
	data->scene = parse_scene(filename);
	if (!data->scene)
	{
		fprintf(stderr, "Error: Failed to parse scene file.\n");
		return (-1);
	}
	if (validate_scene(data->scene) != 0)
	{
		fprintf(stderr, "Error: Invalid scene configuration.\n");
		free_scene(data->scene);
		data->scene = NULL;
		return (-1);
	}
	printf("Scene parsing successful.\n");
	// Normalize camera orientation vector ONCE here
	data->scene->camera.orientation = vec_normalize(data->scene->camera.orientation);
	data->scene->width_pixels = &data->window.width;
	data->scene->height_pixels = &data->window.height;
	return (0);
}

void	data_init(t_data *data)
{
	data->rendering = render_restart;
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
	if (scene_init(&data, argv[1]) < 0)
		return (-1);
	// deploy_threads(&data);
	window_init(&data.window);
	if (data.window.image)
		mlx_delete_image(data.window.mlx, data.window.image);
	return (0);
}
