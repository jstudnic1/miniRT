/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:47:15 by jstudnic          #+#    #+#             */
/*   Updated: 2024/06/07 10:09:32 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx/mlx.h"
# include "vector.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

/* VECTOR UTILS*/
double		vec_len(t_vector vector);
double		dot_product(t_vector u, t_vector v);
t_vector	cross_product(t_vector u, t_vector v);
double		vec_len2(t_vector vector);

/* VECTORS */

#endif
