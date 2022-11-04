/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:34:04 by caboudar          #+#    #+#             */
/*   Updated: 2022/10/20 16:11:15 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

size_t	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_cmp(char *s1, char *s2)
{
	int				i;

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_create_len((char *)s, start, len);
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (l--)
		str[i++] = (char)s[start++];
	str[i] = '\0';
	return (str);
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
