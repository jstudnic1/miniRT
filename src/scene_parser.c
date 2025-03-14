/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:57:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:20:02 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minirt.h"

t_rgb	parse_color(char *str)
{
	t_rgb	color;
	char	**values;

	values = ft_split(str, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		if (values)
			ft_free_split(values);
		return ((t_rgb){-1, -1, -1});
	}
	color = create_rgb(ft_atoi(values[0]), 
		ft_atoi(values[1]), 
		ft_atoi(values[2]));
	ft_free_split(values);
	if (!validate_rgb(color))
		return ((t_rgb){-1, -1, -1});
	return (color);
}

t_vector	parse_vector(char *str)
{
	t_vector	vec;
	char		**values;

	values = ft_split(str, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		if (values)
			ft_free_split(values);
		return ((t_vector){NAN, NAN, NAN});
	}
	vec.x = ft_atof(values[0]);
	vec.y = ft_atof(values[1]);
	vec.z = ft_atof(values[2]);
	ft_free_split(values);
	return (vec);
}

static int	parse_ambient(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2])
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	scene->ambient.intensity = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
	ft_free_split(tokens);
	if (scene->ambient.color.r == -1)
		return (0);
	return (1);
}

static int	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	scene->camera.position = parse_vector(tokens[1]);
	scene->camera.orientation = parse_vector(tokens[2]);
	scene->camera.fov = ft_atof(tokens[3]);
	ft_free_split(tokens);
	if (isnan(scene->camera.position.x) || isnan(scene->camera.orientation.x))
		return (0);
	return (1);
}

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
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
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

t_scene	*parse_scene(char *filename)
{
	t_scene	*scene;
	int		fd;
	char	*line;
	int		success;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_scene(scene);
		return (NULL);
	}
	success = 1;
	while (success && (line = get_next_line(fd)))
	{
		if (line[0] == '#' || line[0] == '\0' || line[0] == '\n')
			free(line);
		else if (line[0] == 'A')
			success = parse_ambient(line, scene);
		else if (line[0] == 'C')
			success = parse_camera(line, scene);
		else if (line[0] == 'L')
			success = parse_light(line, scene);
		else if (line[0] == 'p' && line[1] == 'l')
			success = parse_plane(line, scene);
		else if (line[0] == 'c' && line[1] == 'y')
			success = parse_cylinder(line, scene);
		else
			success = 0;  // Invalid identifier
		if (line[0] != '#' && line[0] != '\0' && line[0] != '\n')
			free(line);
	}
	close(fd);
	if (!success)
	{
		free_scene(scene);
		scene = NULL;
	}
	return (scene);
} 