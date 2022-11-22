/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:34:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/22 23:22:52 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_create_len(char *str, unsigned int start, size_t len)
{
	size_t	count;

	if (start >= ft_strlen(str))
		return (0);
	count = 0;
	while (str[start] && count < len)
	{
		count++;
		start++;
	}
	return (count);
}

char	*ft_strnstr(char *full_path, const char *s2, size_t n)
{
	char	*path;
	size_t	i;
	size_t	j;

	i = 0;
	while (full_path[i] && i < n)
	{
		j = 0;
		while (full_path[i + j] == s2[j] && (i + j < n))
		{
			if (s2[j + 1] == '\0')
			{
				path = path_str(&full_path[n]);
				return (path);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*join_slash_and_comd_to_path(char *s1, char *s2)
{
	char		*str;
	size_t		l_s1;
	size_t		l_s2;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	l_s1 = ft_strlen((char *)s1);
	l_s2 = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (l_s1 + l_s2 + 2));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < l_s1)
		str[i] = (char)s1[i];
	str[i] = '/';
	i++;
	while (++j < l_s2)
		str[i++] = (char)s2[j];
	str[i] = '\0';
	return (str);
}
