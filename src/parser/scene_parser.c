/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:57:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/05 21:16:36 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

static int	parse_ambient(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || double_array_length(tokens) != 3)
	{
		if (tokens)
			ft_free_split(tokens);
		printf("parse amb return 0 becuse wrong number of tokens\n");
		return (0);
	}
	scene->ambient.intensity = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
	ft_free_split(tokens);
	if (scene->ambient.color.r == -1 || scene->ambient.intensity < 0.0
		|| scene->ambient.intensity > 1.0)
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
		printf("parse camera returning 0 because of wrong number of tokens\n");
		return (0);
	}
	scene->camera.position = parse_vector(tokens[1]);
	scene->camera.orientation = parse_vector(tokens[2]);
	scene->camera.fov = ft_atof(tokens[3]);
	ft_free_split(tokens);
	if (isnan(scene->camera.position.x) || isnan(scene->camera.orientation.x)
		|| !is_normalized(scene->camera.orientation)
		|| scene->camera.fov <= 0 || scene->camera.fov >= 180)
		return (0);
	return (1);
}

void	parse_call_obj_parser(t_ps *ps)
{
	if (ps->line[0] == '#' || ps->line[0] == '\0' || ps->line[0] == '\n')
	{
		free(ps->line);
		ps->line = get_next_line(ps->fd);
		return ;
	}
	else if (ps->line[0] == 'A')
		ps->success = parse_ambient(ps->line, ps->scene);
	else if (ps->line[0] == 'C')
		ps->success = parse_camera(ps->line, ps->scene);
	else if (ps->line[0] == 'L')
		ps->success = parse_light(ps->line, ps->scene);
	else if (ps->line[0] == 'p' && ps->line[1] == 'l')
		ps->success = parse_plane(ps->line, ps->scene);
	else if (ps->line[0] == 'c' && ps->line[1] == 'y')
		ps->success = parse_cylinder(ps->line, ps->scene);
	else if (ps->line[0] == 's' && ps->line[1] == 'p')
		ps->success = parse_sphere(ps->line, ps->scene);
	else
	{
		printf("line invalidated\n");
		ps->success = 0;
	}
	free(ps->line);
	ps->line = get_next_line(ps->fd);
}

void	parse_loop(t_ps *ps)
{
	ps->success = 1;
	ps->line = get_next_line(ps->fd);
	while (ps->success && ps->line)
	{
		parse_call_obj_parser(ps);
		printf("success at the end of the loop: %i\n", ps->success);
	}
	if (ps->success == 0 && ps->line)
		free(ps->line);
}

t_scene	*parse_scene(char *filename)
{
	t_ps	ps;

	if (!filename || !check_filename(filename))
		return (NULL);
	ps.scene = ft_calloc(1, sizeof(t_scene));
	if (!ps.scene)
		return (NULL);
	ps.fd = open(filename, O_RDONLY);
	if (ps.fd < 0)
	{
		free_scene(ps.scene);
		free(ps.scene);
		return (NULL);
	}
	parse_loop(&ps);
	close(ps.fd);
	if (!ps.success)
	{
		free_scene(ps.scene);
		free(ps.scene);
		ps.scene = NULL;
	}
	return (ps.scene);
}
