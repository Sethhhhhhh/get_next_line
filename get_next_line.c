/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohannviavant <yohannviavant@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:02:45 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/22 08:27:35 by yohannviava      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int      ft_free(char **str, char **buf, int ret)
{
    if (*str && (ret == -1 || ret == 0))
    {
        free(*str);
        *str = NULL;
    }
    if (*buf)
        free(*buf);
    return (ret);
}

static int      ft_check(char **str, char **line)
{
    int     i;

    i = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '\n')
        {
            if (i == 0)
            {
                if (!(*line = ft_strdup("")))
                    return (-1);
            }
            else
            {
                if (!(*line = ft_substr(*str, 0, i)))
                    return (-1);
            }
            if (!(*str = ft_substr(*str, (i + 1), ft_strlen(*str))))
                return (-1);
            return (1);
        }
        i++;
    }
    return (0);
}

static int      ft_read(int fd, char **buf, char **str, char **line)
{
    int     bytes;
    
    if ((bytes = (ft_check(str, line))) == -1)
        return (ft_free(str, buf, -1));
    if (bytes)
        return (ft_free(str, buf, 1));
    while ((bytes = read(fd, *buf, BUFFER_SIZE)) > 0)
    {
        (*buf)[bytes] = '\0';
        *str = ft_strjoin(*str, *buf);
        if ((bytes = ft_check(str, line)) == -1)
            return (ft_free(str, buf, -1)); 
        if (bytes)
            return (ft_free(str, buf, 1));
    }
    if (bytes == -1 || ((*line) = ft_substr(*str, 0, ft_strlen(*str))) == NULL)
        return (ft_free(str, buf, -1));
    return (ft_free(str, buf, 0));
}

int             get_next_line(int fd, char **line)
{
    static char *str;
    char        *buf;
    int         ret;

    if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 )
        return (ft_free(&str, &buf, -1));
    if (!str)
        if (!(str = ft_calloc(1, sizeof(char))))
            return (ft_free(&str, &buf, -1));
    if (!(buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
        return (ft_free(&str, &buf, -1));
    return (ft_read(fd, &buf, &str, line));
}

// int     main(int ac, char **av)
// {
//     int     fd;
//     char    *line;

//     fd = open(av[1], O_RDONLY);
//     while (get_next_line(fd, &line))
//     {
//         printf("%s\n", line);
//         free(line);
//     }
//     printf("%s\n", line);
//     free(line);
//     while (1);
//     return (0);
// }