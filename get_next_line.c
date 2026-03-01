/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoumman <mhoumman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:04:03 by mhoumman          #+#    #+#             */
/*   Updated: 2025/12/14 21:44:43 by mhoumman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*read_line(int fd, char *res)
{
	char	*buff;
	int		x;

	buff = malloc (BUFFER_SIZE + 1);
	if (!buff)
		return (free (res), res = NULL, NULL);
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
	static char	*res;
	char		*line;
	int			i;

	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
		return (free(res), res = NULL, NULL);
	res = read_line(fd, res);
	if (!res || res[0] == '\0')
		return (free(res), res = NULL, NULL);
	i = found_new_line(res);
	if (i == -1)
		i = ft_strlen(res);
	line = ft_substr(res, 0, i);
	if (!line)
		return (free(res), res = NULL, NULL);
	res = update_res(res, i);
	if (!res)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
