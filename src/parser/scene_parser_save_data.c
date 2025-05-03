/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_save_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:01:23 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 22:05:14 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

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
