/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:43:57 by yozainan          #+#    #+#             */
/*   Updated: 2023/11/30 19:26:42 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(char *tmp)
{
	int	i;
	char	*str;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	str = malloc(sizeof(char) * i + 2);
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

char	*ft_handle(char	*backup)
{
	int	i;
	int	j;
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
		return(NULL);
	i++;
	j = 0;
	while (backup[i])
		str[j++] = backup[i++];
	str[j] = '\0';
	free(backup);
	return (str);
}

char	*read_file(int fd, char *tmp)
{
	char	*buffer;
	int	rbyts;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rbyts = 1;
	while (!ft_strchr(tmp, '\n') && rbyts != 0)
	{
		rbyts = read(fd, buffer, BUFFER_SIZE);
		if (rbyts == -1)
		{
			free(buffer);
			return (tmp);
		}
		buffer[rbyts] = '\0';
		tmp = ft_strjoin(tmp, buffer);
	}
	free(buffer);
	return (tmp);
}

char *get_next_line(int fd)
{
	char	*buff;
	static char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = read_file(fd, tmp);
	if (!tmp)
		return (NULL);
	buff = get_new_line(tmp);
	tmp = ft_handle(tmp);
	return (buff);
}

int main ()
{
    int fd;
    char *line;
    int i = 0;
    
    fd = open("file.txt", O_RDONLY);

	line = get_next_line(fd);
	// printf("++++++++ %s", line);
    while ((line = get_next_line(fd)) && i < 4)
    {
        printf("%s", line);
        i++;
    }  
}