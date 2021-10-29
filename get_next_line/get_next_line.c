/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:06:38 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/20 12:19:53 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*temp;
	int			eof_flag;
	char		*ret_ptr;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	eof_flag = 1;
	if (temp == NULL)
		eof_flag = gnl_init_temp(&temp, fd);
	if (eof_flag == -1)
		return (NULL);
	while (eof_flag == 1 && temp[gnl_find_char(temp, '\n')] == '\0')
		eof_flag = gnl_append_read(&temp, fd);
	if (eof_flag == -1)
		return (NULL);
	ret_ptr = gnl_pop_line(&temp);
	if (temp[0] == 0)
	{
		free(temp);
		temp = NULL;
	}	
	return (ret_ptr);
}

/*
//like append read, but for the first read of the file, 
//returns -1 when trying to read from an empty file.
*/
int	gnl_init_temp(char **temp, int fd)
{
	char	*read_buf;
	char	*neo_temp;
	int		len_read;

	read_buf = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!read_buf)
		return (-1);
	len_read = read(fd, read_buf, BUFFER_SIZE);
	if (len_read <= 0)
	{
		free(read_buf);
		return (-1);
	}
	neo_temp = (char *)malloc((len_read + 1) * sizeof(char));
	if (!neo_temp)
	{
		free(read_buf);
		return (-1);
	}
	gnl_strlcpy(neo_temp, read_buf, len_read);
	*temp = neo_temp;
	free(read_buf);
	return (len_read == BUFFER_SIZE);
}

/*
//splits the input string after the first '\n', returns the first string
//and resize temp accordingly;
*/
char	*gnl_pop_line(char **temp)
{
	char	*ret_ptr;
	char	*neo_temp;
	int		i;
	int		j;

	i = gnl_find_char((*temp), '\n');
	j = gnl_find_char((*temp), '\0');
	ret_ptr = (char *)malloc((i + 2) * sizeof(char));
	neo_temp = (char *)malloc((j - i) * sizeof(char));
	if (gnl_malloc_check(ret_ptr, neo_temp) == 0)
		return (NULL);
	gnl_strlcpy(neo_temp, (*temp + i + 1), j - i);
	gnl_strlcpy(ret_ptr, *temp, i + 1);
	free(*temp);
	*temp = neo_temp;
	return (ret_ptr);
}

/*
//Reads BUFFER_SIZE bytes from file fd and appends to temp and resizes temp, 
//1 on sucess, 0 on EoF, -1 on Error
*/
int	gnl_append_read(char **temp, int fd)
{
	char	*read_buf;
	char	*neo_temp;
	int		len_read;
	int		len_temp;

	read_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (-1);
	len_read = read(fd, read_buf, BUFFER_SIZE);
	if (len_read < 0)
		return (gnl_read_cleanup(read_buf));
	len_temp = gnl_find_char((*temp), '\0');
	neo_temp = (char *)malloc((len_read + len_temp + 1) * sizeof(char));
	if (!neo_temp)
		return (gnl_read_cleanup(read_buf));
	gnl_strlcpy(neo_temp, *temp, len_temp + 1);
	gnl_strlcpy((neo_temp + len_temp), read_buf, len_read);
	free(*temp);
	*temp = neo_temp;
	free(read_buf);
	return (len_read == BUFFER_SIZE);
}
