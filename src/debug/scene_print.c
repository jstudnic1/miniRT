/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:49:51 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 19:54:40 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

void	print_vector(const char *vec_name, t_vector *vector)
{
	printf("Vector: %s\n", vec_name);
	printf("x: %f\ny: %f\nz: %f\n\n", vector->x, vector->y, vector->z);
}

void	print_scene(t_scene *scene)
{
	if (!scene)
	{
		printf("Scene pointer is NULL, nothing to print\n");
		return ;
	}
	printf("\n\nScene:\n");
	printf("ambient light: %f; %ir %ig %ib\n", scene->ambient.intensity, \
	scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	printf("camera: %ffov; %fxo, %fyo, %fzo; %fxp, %fyp, %fzp\n",
		scene->camera.fov, scene->camera.orientation.x,
		scene->camera.orientation.y,
		scene->camera.orientation.z, scene->camera.position.x,
		scene->camera.position.y, scene->camera.position.z);
	printf("number of cylinders: %i @array %p\n", scene->num_cylinders,
		scene->cylinders);
	printf("number of lights: %i @array %p\n", scene->num_lights,
		scene->lights);
	printf("number of planes: %i @array %p\n", scene->num_planes,
		scene->planes);
}
