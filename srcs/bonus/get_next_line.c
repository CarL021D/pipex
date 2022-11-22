/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caboudar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:10:11 by caboudar          #+#    #+#             */
/*   Updated: 2022/11/22 21:04:43 by caboudar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

// char	*ft_get_line(char *stash)
// {
// 	char	*line;
// 	int		i;

// 	if (!stash[0])
// 		return (NULL);
// 	i = 0;
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	if (!stash[i])
// 		i--;
// 	line = malloc(sizeof(char) * i + 2);
// 	if (!line)
// 		return (NULL);
// 	line[i + 1] = '\0';
// 	while (i >= 0)
// 	{
// 		line[i] = stash[i];
// 		i--;
// 	}
// 	return (line);
// }

// char	*ft_set_stash(char *stash)
// {
// 	char	*remaining_chars;
// 	int		i;
// 	int		j;
// 	int		len;

// 	i = 0;
// 	j = -1;
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	len = ft_strlen(stash) - i;
// 	if (stash[i] == '\n')
// 	{
// 		remaining_chars = malloc(sizeof(char) * len);
// 		if (!remaining_chars)
// 			return (free(stash), NULL);
// 		remaining_chars[len - 1] = '\0';
// 		while (--len)
// 			remaining_chars[++j] = stash[++i];
// 		return (free(stash), remaining_chars);
// 	}
// 	else
// 		return (free(stash), NULL);
// }

// char	*get_next_line(int fd)
// {
// 	static char		*stash;
// 	char			*buffer;
// 	int				read_char;
// 	char			*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	if (!buffer)
// 		return (NULL);
// 	read_char = 1;
// 	while (read_char && !still_on_line(stash))
// 	{
// 		read_char = read(fd, buffer, BUFFER_SIZE);
// 		if (read_char == -1)
// 			return (free(stash), free(buffer), NULL);
// 		buffer[read_char] = '\0';
// 		stash = ft_strjoin(stash, buffer);
// 		if (!stash)
// 			return (free(buffer), NULL);
// 	}
// 	line = ft_get_line(stash);
// 	stash = ft_set_stash(stash);
// 	return (free(buffer), line);
// }

char    *join_stash_to_buffer(char *s1, char *s2)
{
        char    *str;
        size_t  i;
        size_t  j;

        str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
        if (!str)
                return (free(s1), NULL);
        i = 0;
        while (s1 && s1[i])
        {
                str[i] = s1[i];
                i++;
        }
        j = -1;
        while (s2[++j])
                str[i++] = s2[j];
        str[i] = '\0';
        return (free(s1), str);
}

int     still_on_line(char *stash)
{
        int     i;

        i = -1;
        if (!stash)
                return (0);
        while (stash[++i])
                if (stash[i] == '\n')
                        return (1);
        return (0);
}

char    *ft_get_line(char *stash)
{       
        char    *line;  
        int             i;
        
        if (!stash[0]) 
                return (NULL);
        i = 0;
        while (stash[i] && stash[i] != '\n')
                i++;
        if (!stash[i])
                i--;
        line = malloc(sizeof(char) * i + 2);
        if (!line)
                return (NULL);
        line[i + 1] = '\0';
        while (i >= 0)
        {       
                line[i] = stash[i];
                i--;
        }
        return (line);
}

char    *ft_set_stash(char *stash)
{       
        char    *remaining_chars;
        int             i;
        int             j;
        int             len;
        
        i = 0;
        j = -1;
        while (stash[i] && stash[i] != '\n')
                i++;
        len = ft_strlen(stash) - i;
        if (stash[i] == '\n')
        {       
                remaining_chars = malloc(sizeof(char) * len);
                if (!remaining_chars)
                        return (free(stash), NULL);
                remaining_chars[len - 1] = '\0';
                while (--len)
                        remaining_chars[++j] = stash[++i];
                return (free(stash), remaining_chars);
        }
        else    
                return (free(stash), NULL);
}

static void    gnl_cleaner(char *stash, char *line)
{
        free(stash);
        free(line);
}

char    *get_next_line(int fd, int id)
{
        static char             *stash;
        static char             *line;
        char                    buffer[BUFFER_SIZE];
        int                     read_char;

        if (CLEAN == id)
                return (gnl_cleaner(stash, line), NULL);

        if (fd < 0)
                return (NULL);
        read_char = 1;
        while (read_char && !still_on_line(stash))
        {
                read_char = read(fd, buffer, BUFFER_SIZE);
                if (read_char == -1)
                        return (free(stash), NULL);
                buffer[read_char] = '\0';
                stash = join_stash_to_buffer(stash, buffer);
                if (!stash)
                        return (NULL);
        }
        line = ft_get_line(stash);
        stash = ft_set_stash(stash);
        return (line);
}


// char    *get_next_line(int fd)
// {
//         static char             *stash;
//         char                    *buffer;
//         int                             read_char;
//         char                    *line;

//         if (fd < 0 || BUFFER_SIZE <= 0)
//                 return (NULL);
//         buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
//         if (!buffer)
//                 return (NULL);
//         read_char = 1;
//         while (read_char && !still_on_line(stash))
//         {
//                 read_char = read(fd, buffer, BUFFER_SIZE);
//                 if (read_char == -1)
//                         return (free(stash), free(buffer), NULL);
//                 buffer[read_char] = '\0';
//                 stash = join_stash_to_buffer(stash, buffer);
//                 if (!stash)
//                         return (free(buffer), NULL);
//         }
//         line = ft_get_line(stash);
//         stash = ft_set_stash(stash);
//         return (free(buffer), line);
// }