/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:44:14 by caboudar          #+#    #+#             */
/*   Updated: 2022/06/12 23:21:43 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	still_on_line(char *stash)
{
	int	i;

	i = -1;
	if (!stash)
		return (0);
	while (stash[++i])
		if (stash[i] == '\n')
			return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(buffer) + 1));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = -1;
	while (buffer[++j])
		str[i++] = buffer[j];
	str[i] = '\0';
	return (free(s1), str);
}
