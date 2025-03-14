/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:48:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:18:51 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft.h"

#define BUFFER_SIZE 1024

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	j = -1;
	while (++j < len2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}

static char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = 0;
	while (s1[len])
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*read_line(int fd, char *buffer, char *backup)
{
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(backup);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

static char	*get_line_from_backup(char **backup)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*backup)
		return (NULL);
	if (!**backup)
	{
		free(*backup);
		*backup = NULL;
		return (NULL);
	}
	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if ((*backup)[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
	{
		line[i] = (*backup)[i];
		i++;
	}
	line[i] = '\0';
	temp = *backup;
	*backup = ft_strdup(&(*backup)[i + ((*backup)[i] == '\n')]);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	backup = read_line(fd, buffer, backup);
	free(buffer);
	if (!backup)
		return (NULL);
	line = get_line_from_backup(&backup);
	return (line);
} 