/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:30:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/14 14:42:23 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

#include <stdint.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Color utility functions
t_rgb	create_rgb(int r, int g, int b);
int		validate_rgb(t_rgb color);

/* Conversions */
uint32_t	rgb_to_uint32(t_rgb color);

// Color utilities
int min(int a, int b);
int max(int a, int b);

#endif
