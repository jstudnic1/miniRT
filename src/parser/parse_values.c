/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:21:11 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 22:21:45 by smelicha         ###   ########.fr       */
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
		printf("parse colors returning invalid because of number of tokens\n");
		return ((t_rgb){-1, -1, -1});
	}
	color = create_rgb(ft_atoi(values[0]), \
		ft_atoi(values[1]), \
		ft_atoi(values[2]));
	ft_free_split(values);
	if (!validate_rgb(color))
	{
		printf("parse colors returning invalid because of invalid colors\n");
		return ((t_rgb){-1, -1, -1});
	}
	return (color);
}

t_vector	parse_vector(char *str)
{
	t_vector	vec;
	char		**values;

	printf("parse vector: string to parse: %s\n", str);
	values = ft_split(str, ',');
	if (!values || double_array_length(values) != 3)
	{
		if (values)
			ft_free_split(values);
		printf("parse vector returning because of wrong number of tokens\n");
		return ((t_vector){NAN, NAN, NAN});
	}
	vec.x = ft_atof(values[0]);
	vec.y = ft_atof(values[1]);
	vec.z = ft_atof(values[2]);
	ft_free_split(values);
	return (vec);
}
