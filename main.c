/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:29 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/06 11:07:44 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "incl/minirt.h"
#include "incl/render.h"
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
	normalize_vec(&data->scene->camera.orientation);
	return (0);
}

void	data_init(t_data *data)
{
	data->window.mlx = NULL;
	data->window.image = NULL;
	data->window.width = 640;
	data->window.height = 480;
	data->scene = NULL;
	// Mutex needed only for threaded version
	// pthread_mutex_init(&data->print, NULL);
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
	{
		fprintf(stderr, "Usage: %s <scene_file.rt>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	data_init(&data);

	// Initialize scene from argument
	if (scene_init(&data, argv[1]) != 0)
	{
		return (EXIT_FAILURE);
	}

	// Initialize window and image buffer
	if (window_init(&data.window) != 0)
	{
		free_scene(data.scene);
		return (EXIT_FAILURE);
	}

	// Render the scene to the image buffer
	render_scene(&data);

	// Display the window and handle events (like closing)
	printf("Displaying window. Press ESC or close window to exit.\n");
	mlx_loop(data.window.mlx);

	// Cleanup
	printf("Cleaning up...\n");
	// mlx_delete_image is often handled by mlx_terminate
	mlx_terminate(data.window.mlx);
	free_scene(data.scene);
	// pthread_mutex_destroy(&data.print); // Only if mutex was initialized

	printf("Exiting.\n");
	return (EXIT_SUCCESS);
}
