/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:40:52 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/06 11:07:45 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h> // For uint32_t

// Defines the RGB color structure.
typedef struct s_rgb
{
	int		r; // Red component [0-255]
	int		g; // Green component [0-255]
	int		b; // Blue component [0-255]
}	t_rgb;

// Helper function (implementation likely in color.c or utils)
uint32_t	rgb_to_uint32(t_rgb	color);

// Color utility functions (implementations likely in color.c or utils)
t_rgb		create_rgb(int r, int g, int b);
int			validate_rgb(t_rgb color);

// Math helpers (used in color manipulation)
int			min(int a, int b);
int			max(int a, int b);

// Optional: Define common colors
// # define COLOR_RED     (t_rgb){255, 0, 0}
// # define COLOR_GREEN   (t_rgb){0, 255, 0}
// # define COLOR_BLUE    (t_rgb){0, 0, 255}
// # define COLOR_WHITE   (t_rgb){255, 255, 255}
// # define COLOR_BLACK   (t_rgb){0, 0, 0}

#endif
