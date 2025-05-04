/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:51:03 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/07 18:10:23 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

t_rgb	calculate_ambient(t_ambient ambient, t_rgb surface_color)
{
	t_rgb	ambient_color;

	ambient_color.r = (int)(ambient.intensity * ambient.color.r
			* surface_color.r / 255.0);
	ambient_color.g = (int)(ambient.intensity * ambient.color.g
			* surface_color.g / 255.0);
	ambient_color.b = (int)(ambient.intensity * ambient.color.b
			* surface_color.b / 255.0);
	return (ambient_color);
}

t_rgb	calculate_diffuse(t_light light, t_vector light_dir, t_vector normal,
						t_rgb surface_color)
{
	t_rgb	diffuse_color;
	double	diffuse_factor;

	diffuse_factor = dot_product(normal, light_dir);
	if (diffuse_factor < 0)
		diffuse_factor = 0;
	diffuse_color.r = (int)(light.brightness * light.color.r
			* surface_color.r * diffuse_factor / 255.0);
	diffuse_color.g = (int)(light.brightness * light.color.g
			* surface_color.g * diffuse_factor / 255.0);
	diffuse_color.b = (int)(light.brightness * light.color.b
			* surface_color.b * diffuse_factor / 255.0);
	return (diffuse_color);
}

static t_rgb	add_colors(t_rgb color1, t_rgb color2)
{
	t_rgb	result;

	result.r = min(color1.r + color2.r, 255);
	result.g = min(color1.g + color2.g, 255);
	result.b = min(color1.b + color2.b, 255);
	return (result);
}

static void	apply_light_contribution(
	t_collision hit, t_light light, t_rgb *final_color)
{
	t_vector	light_dir;
	t_rgb		diffuse_color;

	light_dir = vec_sub(light.position, hit.point);
	light_dir = vec_normalize(light_dir);
	diffuse_color = calculate_diffuse(light, light_dir, hit.normal, hit.color);
	*final_color = add_colors(*final_color, diffuse_color);
}

t_rgb	calculate_lighting(t_collision hit, t_scene *scene, t_vector view_dir)
{
	t_rgb		final_color;
	t_rgb		ambient_color;
	int			i;

	(void)view_dir;
	final_color.r = 0;
	final_color.g = 0;
	final_color.b = 0;
	ambient_color = calculate_ambient(scene->ambient, hit.color);
	final_color = ambient_color;
	i = 0;
	while (i < scene->num_lights)
	{
		apply_light_contribution(hit, scene->lights[i], &final_color);
		i++;
	}
	return (final_color);
}
