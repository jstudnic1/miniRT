/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:40:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:12:14 by smelicha         ###   ########.fr       */
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
void	*ft_realloc(void *old_ptr, size_t new_size, size_t old_size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif 