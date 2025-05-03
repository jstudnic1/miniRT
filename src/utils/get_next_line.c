/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:48:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:08:37 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/libft.h"

#define BUFFER_SIZE 1024

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

static char	*copy_backup_to_line(char **backup, int *i)
{
	char	*line;

	line = NULL;
	*i = 0;
	while ((*backup)[*i] && (*backup)[*i] != '\n')
		*i = *i + 1;
	if ((*backup)[*i] == '\n')
		*i = *i + 1;
	line = malloc(sizeof(char) * (*i + 1));
	if (!line)
		return (NULL);
	*i = 0;
	while ((*backup)[*i] && (*backup)[*i] != '\n')
	{
		line[*i] = (*backup)[*i];
		*i = *i + 1;
	}
	line[*i] = '\0';
	return (line);
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
	line = copy_backup_to_line(backup, &i);
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
