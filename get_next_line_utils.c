/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoumman <mhoumman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:47:18 by mhoumman          #+#    #+#             */
/*   Updated: 2025/12/14 17:50:00 by mhoumman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc (ft_strlen(str) + 1);
	if (!d)
		return (NULL);
	while (str[i])
	{
		d[i] = str[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*d;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	j = 0;
	d = malloc (len1 + len2 + 1);
	if (!d)
		return (NULL);
	i = -1;
	while (++i < len1)
		d[i] = s1[i];
	while (s2[j])
		d[i++] = s2[j++];
	return (d[i] = '\0', free(s1), d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*d;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	d = malloc (len + 1);
	if (!d)
		return (NULL);
	while (i < len)
	{
		d[i] = s[i + start];
		i++;
	}
	d[i] = '\0';
	return (d);
}
