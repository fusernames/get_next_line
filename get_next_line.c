/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:19:18 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/22 18:20:19 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*self_join(char *s1, const char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

int			replace_next_cr(char *line)
{
	int			i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	line[i] = '\0';
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	int			i;
	static int	index = 0;
	char		*tmp;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	ret = 0;
	if (index < 0)
		return (0);
	if (!index)
		*line = ft_memalloc(1);
	if (index)
	{
		tmp = *line;
		*line = ft_strdup(&(*line)[index + 1]);
		free(tmp);
		if ((index = replace_next_cr(*line)))
			return (1);
	}
	if (!index)
	{
		while ((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			i = 0;
			while (buf[i] && buf[i] != '\n')
				i++;
			*line = self_join(*line, buf);
			if (buf[i] == '\n')
				break ;
		}
	}
	index = replace_next_cr(*line);
	if (ret <= 0)
		index = -1;
	return (1);
}
