/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:34:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/22 23:07:25 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

size_t	ft_strlen(char *str)
{
	int		i;

	if (!str)
	{
		return (0);
	}
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	l_s1;
	size_t	l_s2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	l_s1 = ft_strlen((char *)s1);
	l_s2 = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < l_s1)
		str[i] = (char)s1[i];
	while (++j < l_s2)
		str[i++] = (char)s2[j];
	str[i] = '\0';
	return (str);
}
