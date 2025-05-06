/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:00:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:03:03 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <stdbool.h>
#include <unistd.h>

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
		return ;
	scene->num_lights = 0;
	scene->num_planes = 0;
	scene->num_spheres = 0;
	scene->num_cylinders = 0;
	scene->lights = NULL;
	scene->planes = NULL;
	scene->spheres = NULL;
	scene->cylinders = NULL;
	scene->ambient_parsed = false;
	scene->camera_parsed = false;
	scene->ambient.intensity = -1.0;
	scene->camera.fov = -1.0;
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->lights);
	free(scene->planes);
	free(scene->spheres);
	free(scene->cylinders);
}

int	validate_scene(t_scene *scene)
{
	if (!scene || scene->ambient.intensity < 0.0 || scene->camera.fov <= 0)
	{
		fprintf(stderr, "Error: Scene validation failed (Missing A or C?).\n");
		return (-1);
	}
	return (0);
}

bool	check_filename(char *fn)
{
	int	i;

	i = 0;
	if (!fn)
		return (false);
	while (fn[i] != '\0')
		i++;
	if (i < 3)
		return (false);
	if (fn[i - 1] != 't' || fn[i - 2] != 'r' || fn[i - 3] != '.')
	{
		printf("Unknown file type: %s\n", fn);
		return (false);
	}
	else
		return (true);
}
