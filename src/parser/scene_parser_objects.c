/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:17:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:18:03 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

static int	parse_light(char *line, t_scene *scene)
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

static int	parse_plane(char *line, t_scene *scene)
{
	char	**tokens;
	t_plane	plane;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	plane.point = parse_vector(tokens[1]);
	plane.normal = parse_vector(tokens[2]);
	plane.color = parse_color(tokens[3]);
	ft_free_split(tokens);
	if (isnan(plane.point.x) || isnan(plane.normal.x) || plane.color.r == -1)
		return (0);
	return (add_plane(scene, plane));
}

static int	parse_cylinder(char *line, t_scene *scene)
{
	char		**tokens;
	t_cylinder	cylinder;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4] || !tokens[5])
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	cylinder.center = parse_vector(tokens[1]);
	cylinder.axis = parse_vector(tokens[2]);
	cylinder.diameter = ft_atof(tokens[3]);
	cylinder.height = ft_atof(tokens[4]);
	cylinder.color = parse_color(tokens[5]);
	ft_free_split(tokens);
	if (isnan(cylinder.center.x) || isnan(cylinder.axis.x) || cylinder.color.r == -1)
		return (0);
	return (add_cylinder(scene, cylinder));
}

int	parse_objects(char *line, t_scene *scene)
{
	if (line[0] == 'L')
		return (parse_light(line, scene));
	else if (line[0] == 'p' && line[1] == 'l')
		return (parse_plane(line, scene));
	else if (line[0] == 'c' && line[1] == 'y')
		return (parse_cylinder(line, scene));
	return (0);
} 