/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:00:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 16:33:50 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
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

// Placeholder for free_scene - ensure it frees allocated arrays
void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->lights);
	free(scene->planes);
	free(scene->spheres);
	free(scene->cylinders);
}

void	ft_calloc_mmcp(char *src, char *dst, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		dst[i] = src[i];
		i++;
	}
}

void	*ft_realloc(void *old_ptr, size_t new_size, size_t old_size)
{
	char	*new_ptr;
	char	*tmp;

	new_ptr = NULL;
	tmp = old_ptr;
	if (old_ptr == NULL && old_size == 0)
	{
		new_ptr = malloc(new_size);
		return ((void *)new_ptr);
	}
	else if ((old_ptr == NULL && old_size != 0))
		return (NULL);
	else if (old_ptr && new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	ft_calloc_mmcp(tmp, new_ptr, old_size);
	free(old_ptr);
	return ((void *)new_ptr);
}

int	add_light(t_scene *scene, t_light light)
{
	t_light	*new_lights;

	new_lights = ft_realloc(scene->lights,
			(scene->num_lights + 1) * sizeof(t_light),
			scene->num_lights * sizeof(t_light));
	if (!new_lights)
	{
		perror("Failed to realloc lights array");
		return (0);
	}
	scene->lights = new_lights;
	scene->lights[scene->num_lights] = light;
	scene->num_lights++;
	return (1);
}

int	add_plane(t_scene *scene, t_plane plane)
{
	t_plane	*new_planes;

	new_planes = ft_realloc(scene->planes,
			(scene->num_planes + 1) * sizeof(t_plane),
			scene->num_planes * sizeof(t_plane));
	if (!new_planes)
	{
		perror("Failed to realloc planes array");
		return (0);
	}
	scene->planes = new_planes;
	scene->planes[scene->num_planes] = plane;
	scene->num_planes++;
	return (1);
}

int	add_sphere(t_scene *scene, t_sphere sphere)
{
	t_sphere	*new_spheres;

	new_spheres = ft_realloc(scene->spheres,
			(scene->num_spheres + 1) * sizeof(t_sphere),
			scene->num_spheres * sizeof(t_sphere));
	if (!new_spheres)
	{
		perror("Failed to realloc spheres array");
		return (0);
	}
	scene->spheres = new_spheres;
	scene->spheres[scene->num_spheres] = sphere;
	scene->num_spheres++;
	return (1);
}

int	add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder	*new_cylinders;

	new_cylinders = ft_realloc(scene->cylinders,
			(scene->num_cylinders + 1) * sizeof(t_cylinder),
			scene->num_cylinders * sizeof(t_cylinder));
	if (!new_cylinders)
	{
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
	if (!scene || scene->ambient.intensity < 0.0 || scene->camera.fov <= 0)
	{
		fprintf(stderr, "Error: Scene validation failed (Missing A or C?).\n");
		return (-1);
	}
	return (0);
}
