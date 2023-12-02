/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:43:45 by yozainan          #+#    #+#             */
/*   Updated: 2023/12/01 21:24:46 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_new_line(char *tmp)
{
	int		i;
	char	*str;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_handle(char *backup)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!str)
		return (NULL);
	i++;
	k = 0;
	while (backup[i])
	{
		str[k++] = backup[i++];
	}
	str[k] = '\0';
	free(backup);
	return (str);
}

char	*ft_get_line(int fd, char *handle)
{
	char	*buffer;
	int		rbyts;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rbyts = 1;
	while (!ft_strchr(handle, '\n') && rbyts != 0)
	{
		rbyts = read(fd, buffer, BUFFER_SIZE);
		if (rbyts == -1)
		{
			free(buffer);
			free(handle);
			return (NULL);
		}
		buffer[rbyts] = '\0';
		handle = ft_strjoin(handle, buffer);
	}
	free(buffer);
	return (handle);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*handle[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	handle[fd] = ft_get_line(fd, handle[fd]);
	if (!handle[fd])
		return (NULL);
	buff = get_new_line(handle[fd]);
	handle[fd] = ft_handle(handle[fd]);
	return (buff);
}
