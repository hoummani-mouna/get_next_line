/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoumman <mhoumman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:52:50 by mhoumman          #+#    #+#             */
/*   Updated: 2025/12/14 21:36:56 by mhoumman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_new_line(char *res)
{
	int	i;

	i = 0;
	if (!res)
		return (-1);
	while (res[i])
	{
		if (res[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*update_res(char *res, int i)
{
	char	*tmp;

	if (!res)
		return (NULL);
	if (res[i - 1] == '\n')
		tmp = ft_substr(res, i, ft_strlen(res + i));
	else
		tmp = ft_strdup("");
	free (res);
	if (!tmp)
		return (NULL);
	res = tmp;
	return (res);
}

char	*help(int fd, char *res)
{
	char	*buff;
	int		x;

	buff = malloc (BUFFER_SIZE + 1);
	if (!buff)
		return (free(res), res = NULL, NULL);
	x = 1;
	while (found_new_line(res) == -1 && x > 0)
	{
		x = read(fd, buff, BUFFER_SIZE);
		if (x < 0)
			return (free(buff), buff = NULL, NULL); 
		else if (x == 0)
			break ;
		buff[x] = '\0';
		res = ft_strjoin(res, buff);
		if (!res)
		{
			free(buff);
			return (NULL);
		}
	}
	free (buff);
	buff = NULL;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res[OPEN_MAX];
	char		*line;
	int			i;

	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
		return (free(res[fd]), res[fd] = NULL, NULL);
	res[fd] = help(fd, res[fd]);
	if (!res[fd] || res[fd][0] == '\0')
		return (free(res[fd]), res[fd] = NULL, NULL);
	i = found_new_line(res[fd]);
	if (i == -1)
		i = ft_strlen(res[fd]);
	line = ft_substr(res[fd], 0, i);
	if (!line)
		return (free(res[fd]), res[fd] = NULL, NULL);
	res[fd] = update_res(res[fd], i);
	if (!res[fd])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
