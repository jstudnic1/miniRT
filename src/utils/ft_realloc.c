/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:02:39 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 22:05:27 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

void	ft_calloc_mmcp(char *src, char *dst, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		dst[i] = src[i];
		i++;
	}
}

void	*ft_realloc(void *old_ptr, size_t new_size, size_t old_size)
{
	char	*new_ptr;
	char	*tmp;

	new_ptr = NULL;
	tmp = old_ptr;
	if (old_ptr == NULL && old_size == 0)
	{
		new_ptr = malloc(new_size);
		return ((void *)new_ptr);
	}
	else if ((old_ptr == NULL && old_size != 0))
		return (NULL);
	else if (old_ptr && new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	ft_calloc_mmcp(tmp, new_ptr, old_size);
	free(old_ptr);
	return ((void *)new_ptr);
}
