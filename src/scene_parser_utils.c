/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:00:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:18:22 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

void	init_scene(t_scene *scene)
{
	scene->lights = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->num_lights = 0;
	scene->num_planes = 0;
	scene->num_cylinders = 0;
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->lights)
		free(scene->lights);
	if (scene->planes)
		free(scene->planes);
	if (scene->cylinders)
		free(scene->cylinders);
	free(scene);
}

int	add_light(t_scene *scene, t_light light)
{
	t_light	*new_lights;

	new_lights = malloc(sizeof(t_light) * (scene->num_lights + 1));
	if (!new_lights)
		return (0);
	if (scene->lights)
	{
		ft_memcpy(new_lights, scene->lights,
			sizeof(t_light) * scene->num_lights);
		free(scene->lights);
	}
	new_lights[scene->num_lights] = light;
	scene->lights = new_lights;
	scene->num_lights++;
	return (1);
}

int	add_plane(t_scene *scene, t_plane plane)
{
	t_plane	*new_planes;

	new_planes = malloc(sizeof(t_plane) * (scene->num_planes + 1));
	if (!new_planes)
		return (0);
	if (scene->planes)
	{
		ft_memcpy(new_planes, scene->planes,
			sizeof(t_plane) * scene->num_planes);
		free(scene->planes);
	}
	new_planes[scene->num_planes] = plane;
	scene->planes = new_planes;
	scene->num_planes++;
	return (1);
}

int	add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder	*new_cylinders;

	new_cylinders = malloc(sizeof(t_cylinder) * (scene->num_cylinders + 1));
	if (!new_cylinders)
		return (0);
	if (scene->cylinders)
	{
		ft_memcpy(new_cylinders, scene->cylinders,
			sizeof(t_cylinder) * scene->num_cylinders);
		free(scene->cylinders);
	}
	new_cylinders[scene->num_cylinders] = cylinder;
	scene->cylinders = new_cylinders;
	scene->num_cylinders++;
	return (1);
}

int	validate_scene(t_scene *scene)
{
	// Check if we have exactly one camera
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (0);
	
	// Check if we have exactly one ambient light
	if (scene->ambient.intensity < 0 || scene->ambient.intensity > 1)
		return (0);
	
	// Validate all vectors are normalized where needed
	normalize_vec(&scene->camera.orientation);
	for (int i = 0; i < scene->num_planes; i++)
		normalize_vec(&scene->planes[i].normal);
	for (int i = 0; i < scene->num_cylinders; i++)
		normalize_vec(&scene->cylinders[i].axis);
	
	return (1);
} 