/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:00:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/06 11:14:15 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

int	double_array_length(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Initializes the scene struct, setting counts to 0 and pointers to NULL.
 * This is crucial before parsing begins, especially for dynamic arrays.
 *
 * @param scene The scene struct to initialize.
 */
void	init_scene(t_scene *scene)
{
	if (!scene)
		return;
	// Initialize counts
	scene->num_lights = 0;
	scene->num_planes = 0;
	scene->num_cylinders = 0;
	// Initialize pointers (important if they are dynamically allocated later)
	scene->lights = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	// Initialize mandatory elements to identifiable invalid states
	scene->ambient.intensity = -1.0; // Indicate not set yet
	scene->camera.fov = -1.0;       // Indicate not set yet
}

// Placeholder for free_scene - ensure it frees allocated arrays
void	free_scene(t_scene *scene)
{
	if (!scene)
		return;
	free(scene->lights);
	free(scene->planes);
	free(scene->cylinders);
	// Do NOT free the scene pointer itself here, caller allocated it.
	// Only free the internal arrays.
}

// Placeholder for add_light (assuming dynamic array)
// Needs reallocation logic (e.g., realloc)
int	add_light(t_scene *scene, t_light light)
{
	// Simple implementation without dynamic resizing (for fixed array or testing)
	// if (scene->num_lights < MAX_LIGHTS) { // If using fixed array
	//     scene->lights[scene->num_lights] = light;
	//     scene->num_lights++;
	//     return (1);
	// }
	// return (0); // Failed to add

	// Basic dynamic array implementation (example)
	t_light *new_lights = realloc(scene->lights, (scene->num_lights + 1) * sizeof(t_light));
	if (!new_lights) {
		perror("Failed to realloc lights array");
		return (0); // Allocation failed
	}
	scene->lights = new_lights;
	scene->lights[scene->num_lights] = light;
	scene->num_lights++;
	return (1);
}

// Placeholder for add_plane (assuming dynamic array)
int	add_plane(t_scene *scene, t_plane plane)
{
	t_plane *new_planes = realloc(scene->planes, (scene->num_planes + 1) * sizeof(t_plane));
	if (!new_planes) {
		perror("Failed to realloc planes array");
		return (0);
	}
	scene->planes = new_planes;
	scene->planes[scene->num_planes] = plane;
	scene->num_planes++;
	return (1);
}

// Placeholder for add_cylinder (assuming dynamic array)
int	add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder *new_cylinders = realloc(scene->cylinders, (scene->num_cylinders + 1) * sizeof(t_cylinder));
	if (!new_cylinders) {
		perror("Failed to realloc cylinders array");
		return (0);
	}
	scene->cylinders = new_cylinders;
	scene->cylinders[scene->num_cylinders] = cylinder;
	scene->num_cylinders++;
	return (1);
}

int	validate_scene(t_scene *scene)
{
	// This function might be redundant now if parsing functions do all checks,
	// or it could double-check for mandatory elements.
	if (!scene || scene->ambient.intensity < 0.0 || scene->camera.fov <= 0)
	{
		fprintf(stderr, "Error: Scene validation failed (Missing A or C?).\n");
		return (-1); // Indicate failure
	}
	// Add more checks if needed
	return (0); // Indicate success
}
