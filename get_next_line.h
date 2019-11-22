/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohannviavant <yohannviavant@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:03:09 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/21 22:26:13 by yohannviava      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	*ft_calloc(size_t count, size_t size);
int     ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, size_t len);
int     get_next_line(int fd, char **line);

#endif