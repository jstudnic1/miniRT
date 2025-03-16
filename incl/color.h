/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:30:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:02:53 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Color utility functions
t_rgb	create_rgb(int r, int g, int b);
int		validate_rgb(t_rgb color);

#endif
