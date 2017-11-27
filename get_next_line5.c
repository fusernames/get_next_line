/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:23:03 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/24 13:50:57 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*self_join(char *s1, const char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

static int	get_size(const char *s)
{
	int		i;

	i = 0;
	while(s[i] && s[i] != '\n')
		i++;
	return (i);
}

static char	*create_line(char *buf)
{
	int		i;
	char	*new;
	int		size;

	i = get_size(buf);
	if (buf[i])
		i++;
	size = ft_strlen(buf);
	new = ft_strndup(&buf[i], get_size(&buf[i]));
	ft_memmove(buf, &buf[i], ft_strlen(&buf[i]));
	buf[size - i] = '\0';
	return (new);
}

static int	has_cr(const char *buf)
{
	while (*buf && *buf != '\n')
		buf++;
	if (*buf == '\n')
		return (1);
	else
		return (0);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	int				i;
	static char		buf[BUFF_SIZE + 1];
	char			*str;

	if (fd < 0 || line == NULL)
		return (-1);
	str = ft_memalloc(1);
	ret = 0;
	if (buf[0])
	{
		str = create_line(buf);
		if (has_cr(buf))
		{
			*line = str;
			return (1);
		}
	}
	if (!has_cr(buf))
	{
		while((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			i = 0;
			str = self_join(str, buf);
			while(buf[i] && buf[i] != '\n')
				i++;
			if (buf[i] == '\n')
				break ;
		}
	}
	*line = ft_strndup(str, get_size(str));
	free(str);
	if ((ret <= 0 && !buf[0]) || (ret < 0))
		return (0);
	return (1);
}
