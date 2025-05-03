/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:17:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 16:44:48 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

int	parse_light(char *line, t_scene *scene)
{
	char	**tokens;
	t_light	light;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	light.position = parse_vector(tokens[1]);
	light.brightness = ft_atof(tokens[2]);
	light.color = parse_color(tokens[3]);
	ft_free_split(tokens);
	if (isnan(light.position.x) || light.color.r == -1)
		return (0);
	return (add_light(scene, light));
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	plane;
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (double_array_length(tokens) != 4)
	{
		fprintf(stderr,
			"Error: Invalid plane definition (expected 4 tokens)\n");
		return (0);
	}
	plane.point = parse_vector(tokens[1]);
	plane.normal = parse_vector(tokens[2]);
	plane.color = parse_color(tokens[3]);
	ft_free_split(tokens);
	if (isnan(plane.point.x) || isnan(plane.normal.x) || plane.color.r == -1
		|| !is_normalized(plane.normal))
	{
		fprintf(stderr,
			"Error: Invalid plane values (vector, color, or \
			non-normalized normal)\n");
		return (0);
	}
	return (add_plane(scene, plane));
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	cylinder;
	char		**tokens;

	tokens = ft_split(line, ' ');
	if (double_array_length(tokens) != 6)
	{
		fprintf(stderr, "Error: Invalid cylinder definition \
			(expected 6 tokens)\n");
		return (0);
	}
	cylinder.center = parse_vector(tokens[1]);
	cylinder.axis = parse_vector(tokens[2]);
	cylinder.diameter = ft_atof(tokens[3]) / 2;
	cylinder.height = ft_atof(tokens[4]);
	cylinder.color = parse_color(tokens[5]);
	ft_free_split(tokens);
	if (isnan(cylinder.center.x) || isnan(cylinder.axis.x)
		|| cylinder.color.r == -1 || !is_normalized(cylinder.axis)
		|| cylinder.diameter <= 0 || cylinder.height <= 0)
	{
		fprintf(stderr, "Error: Invalid cylinder values (vector\
			, color, non-normalized axis, or non-positive size)\n");
		return (0);
	}
	return (add_cylinder(scene, cylinder));
}

int	parsed_sphere_check(char **tokens, t_sphere sphere, t_scene *scene)
{
	if (sphere.radius <= 0)
	{
		fprintf(stderr, "Error: Sphere radius must be positive:\
			 %s\n", tokens[2]);
		return (0);
	}
	if (!validate_rgb(sphere.color))
	{
		fprintf(stderr, "Error: Invalid RGB color for sphere:\
			 %s\n", tokens[3]);
		return (0);
	}
	if (!add_sphere(scene, sphere))
	{
		fprintf(stderr, "Error adding sphere to scene\n");
		return (0);
	}
	return (1);
}

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	sphere;
	char		**tokens;

	tokens = ft_split(line, ' ');
	if (double_array_length(tokens) != 4)
	{
		fprintf(stderr, "Error: Invalid sphere definition:\
			 %s %s %s %s\n",
			tokens[0], tokens[1], tokens[2], tokens[3]);
		return (0);
	}
	sphere.center = parse_vector(tokens[1]);
	sphere.radius = ft_atof(tokens[2]) / 2;
	sphere.color = parse_color(tokens[3]);
	ft_free_split(tokens);
	return (parsed_sphere_check(tokens, sphere, scene));
}
