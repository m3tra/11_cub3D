/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:27:40 by fporto            #+#    #+#             */
/*   Updated: 2023/03/08 15:30:29 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	*init(void)
{
	char	*arr;

	arr = malloc(1);
	if (!arr)
		return (NULL);
	arr[0] = 0;
	return ((void *)arr);
}

static int	save_line(char **linerd, char *buffr, char **line, ssize_t nrdbytes)
{
	if (nrdbytes == -1)
	{
		free(buffr);
		free(*linerd);
		*linerd = NULL;
		return (-1);
	}
	if (!ft_strchr(*linerd, '\n'))
	{
		free(buffr);
		*line = *linerd;
		*linerd = NULL;
	}
	return (0);
}

static	int	gnl(int fd, char **lineread, char *buffer, char **line)
{
	ssize_t	nreadbytes;
	char	*temp;

	if (!(*lineread))
		*lineread = init();
	nreadbytes = 0;
	while (!ft_strchr(*lineread, '\n'))
	{
		nreadbytes = read(fd, buffer, BUFFER_SIZE);
		if (nreadbytes == -1)
			return (save_line(lineread, buffer, line, nreadbytes));
		if (!nreadbytes)
			break ;
		buffer[nreadbytes] = '\0';
		temp = *lineread;
		*lineread = ft_strjoin(temp, buffer);
		free(temp);
	}
	if (!ft_strchr(*lineread, '\n'))
		return (save_line(lineread, buffer, line, nreadbytes));
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*lineread[FD_MAX];
	char		*temp;
	int			ret;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || fd == 1 || fd == 2 || fd >= 4096 || !line || BUFFER_SIZE <= 0
		|| !buffer)
	{
		if (buffer)
			free(buffer);
		return (-1);
	}
	ret = gnl(fd, &lineread[fd], buffer, line);
	if (!ret)
		return (0);
	if (ret == -1)
		return (-1);
	free(buffer);
	*line = ft_substr(lineread[fd], 0, \
		(ft_strchr(lineread[fd], '\n') - lineread[fd]));
	temp = lineread[fd];
	lineread[fd] = ft_strdup(temp + ft_strlen(*line) + 1);
	free(temp);
	return (1);
}
