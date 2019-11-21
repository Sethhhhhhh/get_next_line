/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:02:45 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/21 10:08:53 by yviavant         ###   ########.fr       */
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

int             get_next_line(int fd, char **line)
{
    static char *str;
    char        *buf;
    int         bytes;

    if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 )
        return (-1);
    if (!str)
        if (!(str = ft_calloc(1, sizeof(char))))
            return (-1);
    if (!(buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
        return (ft_free(&str, &buf, -1));
    if ((ft_check(&str, line)))
        return (ft_free(&str, &buf, 1));
    while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[bytes] = '\0';
        str = ft_strjoin(str, buf);
        if (ft_check(&str, line))
            return (ft_free(&str, &buf, 1)); 
    }
    if (bytes == -1 || !((*line) = ft_substr(str, 0, ft_strlen(str))))
        return (ft_free(&str, &buf, -1));
    return (ft_free(&str, &buf, 0));
}
