/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:40:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:07:12 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

// String manipulation
char	**ft_split(char const *s, char c);
void	ft_free_split(char **split);

// Number conversion
int		ft_atoi(const char *str);
double	ft_atof(const char *str);

// Memory management
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*get_next_line(int fd);

#endif 