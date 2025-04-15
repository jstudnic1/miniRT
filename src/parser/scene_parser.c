/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:57:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/06 11:41:00 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

t_rgb	parse_color(char *str)
{
	t_rgb	color;
	char	**values;

	values = ft_split(str, ',');
	if (!values || double_array_length(values) != 3)
	{
		if (values)
			ft_free_split(values);
		return ((t_rgb){-1, -1, -1});
	}
	color = create_rgb(ft_atoi(values[0]), \
		ft_atoi(values[1]), \
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
	if (!values || double_array_length(values) != 3)
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
	if (!tokens || double_array_length(tokens) != 3)
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	scene->ambient.intensity = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
	ft_free_split(tokens);
	if (scene->ambient.color.r == -1 || scene->ambient.intensity < 0.0 || scene->ambient.intensity > 1.0)
		return (0);
	return (1);
}

static int	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || double_array_length(tokens) != 4)
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	scene->camera.position = parse_vector(tokens[1]);
	scene->camera.orientation = parse_vector(tokens[2]);
	scene->camera.fov = ft_atof(tokens[3]);
	ft_free_split(tokens);
	if (isnan(scene->camera.position.x) || isnan(scene->camera.orientation.x) ||
		!is_normalized(scene->camera.orientation) ||
		scene->camera.fov <= 0 || scene->camera.fov >= 180)
		return (0);
	return (1);
}

static int	parse_light(char *line, t_scene *scene)
{
	char	**tokens;
	t_light	light;

	tokens = ft_split(line, ' ');
	if (!tokens || double_array_length(tokens) != 4)
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	light.position = parse_vector(tokens[1]);
	light.brightness = ft_atof(tokens[2]);
	light.color = parse_color(tokens[3]);
	ft_free_split(tokens);
	if (isnan(light.position.x) || light.color.r == -1 || light.brightness < 0.0 || light.brightness > 1.0)
		return (0);
	return (add_light(scene, light));
}

static int	parse_plane(char *line, t_scene *scene)
{
	char	**tokens;
	t_plane	plane;

	tokens = ft_split(line, ' ');
	if (!tokens || double_array_length(tokens) != 4)
	{
		if (tokens)
			ft_free_split(tokens);
		return (0);
	}
	plane.point = parse_vector(tokens[1]);
	plane.normal = parse_vector(tokens[2]);
	plane.color = parse_color(tokens[3]);
	ft_free_split(tokens);
	if (isnan(plane.point.x) || isnan(plane.normal.x) || plane.color.r == -1 ||
	    !is_normalized(plane.normal))
		return (0);
	return (add_plane(scene, plane));
}

static int	parse_cylinder(char *line, t_scene *scene)
{
	char		**tokens;
	t_cylinder	cylinder;

	tokens = ft_split(line, ' ');
	if (!tokens || double_array_length(tokens) != 6)
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
	if (isnan(cylinder.center.x) || isnan(cylinder.axis.x) || cylinder.color.r == -1 ||
	    !is_normalized(cylinder.axis) ||
	    cylinder.diameter <= 0 || cylinder.height <= 0)
		return (0);
	return (add_cylinder(scene, cylinder));
}

t_scene	*parse_scene(char *filename)
{
	t_scene	*scene;
	int		fd;
	char	*line;
	char	**tokens;
	int		success;
	int		line_num = 0;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	init_scene(scene);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening scene file");
		free_scene(scene);
		return (NULL);
	}
	success = 1;
	line = NULL;
	while (success)
	{
		free(line);
		line = get_next_line(fd);
		line_num++;

		if (line == NULL)
			break;

		// Basic trim (remove trailing newline if present)
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		// --- Strip comments ---
		char *comment_ptr = strchr(line, '#');
		if (comment_ptr != NULL)
			*comment_ptr = '\0'; // Truncate string at comment start
		// --- End Strip comments ---

		// Skip empty lines or lines that are now empty after comment removal
		if (line[0] == '\0')
			continue;

		tokens = ft_split(line, ' ');
		if (!tokens || !tokens[0]) // Check if split failed or line was just whitespace
		{
			fprintf(stderr, "Error: Invalid format on line %d.\n", line_num);
			success = 0;
		}
		else if (strcmp(tokens[0], "A") == 0)
			success = parse_ambient(line, scene);
		else if (strcmp(tokens[0], "C") == 0)
			success = parse_camera(line, scene);
		else if (strcmp(tokens[0], "L") == 0)
			success = parse_light(line, scene);
		else if (strcmp(tokens[0], "pl") == 0)
			success = parse_plane(line, scene);
		else if (strcmp(tokens[0], "cy") == 0)
			success = parse_cylinder(line, scene);
		else
		{
			fprintf(stderr, "Error on line %d: Invalid identifier \"%s\".\n", line_num, tokens[0]);
			success = 0;
		}

		if (!success)
			fprintf(stderr, "Error parsing element on line %d: %s\n", line_num, line);

		if (tokens)
			ft_free_split(tokens);
	}
	free(line);
	close(fd);

	if (!success)
	{
		fprintf(stderr, "Error occurred during scene parsing.\n");
		free_scene(scene);
		scene = NULL;
	}

	if (scene && (isnan(scene->camera.fov) || scene->ambient.intensity < 0.0))
	{
		fprintf(stderr, "Error: Scene missing mandatory Camera (C) or Ambient light (A) definition.\n");
		free_scene(scene);
		scene = NULL;
	}

	return (scene);
}
