/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:08:58 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/29 17:28:10 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
int		gnl_init_temp(char **temp, int fd);
char	*get_next_line(int fd);
char	*gnl_pop_line(char **temp);
int		gnl_append_read(char **temp, int fd);
int		gnl_find_char(char *s, char c);
void	gnl_strlcpy(char *dest, char *src, int n);
int		gnl_malloc_check(char *ptr1, char *ptr2);
int		gnl_read_cleanup(char *read_buf);
#endif
