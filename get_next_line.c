/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:29:56 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/27 14:34:28 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*self_join(char *s1, const char *s2)
{
	char	*new;

	if (s1 == NULL)
		s1 = ft_memalloc(1);
	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

static size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static int		next_line(ssize_t ret, char **saved, char **line)
{
	size_t	len;
	char	*tmp;

	tmp = *saved;
	if (ret < 0)
		return (-1);
	if (((len = get_len(*saved)) == 0 || *saved == NULL) && ret == 0)
		return (0);
	if (!(*line = ft_strndup(*saved, len)))
		return (-1);
	if ((*saved)[len] == '\n')
		len++;
	if (!(*saved = ft_strdup(&(*saved)[len])))
		return (-1);
	free(tmp);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*saved = NULL;
	char			buf[BUFF_SIZE + 1];
	ssize_t			ret;

	ret = 1;
	if (fd < 0 || line == NULL)
		return (-1);
	if (saved)
	{
		if (saved[get_len(saved)])
			return (next_line(ret, &saved, line));
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(saved = self_join(saved, buf)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (next_line(ret, &saved, line));
}
