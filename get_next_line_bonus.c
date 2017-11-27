/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:21:29 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/25 18:12:45 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*self_join(char *s1, const char *s2)
{
	char	*new;

	if (s1 == NULL)
		s1 = ft_memalloc(1);
	if (!(new = ft_strjoin(s1, s2)))
		return (NULL);
	free(s1);
	return (new);
}

static t_list	*elem_exist(t_list *lst, int fd)
{
	while(lst)
	{
		if (((t_str *)lst->content)->fd == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static int		next_line(t_list *elem, char **line)
{
	char	*tmp;
	size_t	len;
	t_str	*content;

	content = (t_str *)elem->content;
	if ((len = get_len(content->str) == 0))
		return (0);
	tmp = content->str;
	if (!(content->str))
		return (0);
	if (!(*line = ft_strndup(content->str, len)))
		return (-1);
	if (len == ft_strlen(content->str))
		len--;
	if (!(content->str = ft_strdup(&(content->str)[len + 1])))
		return (-1);
	free(tmp);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*lst = NULL;
	t_list			*elem;
	t_str			*str;
	int				ret;
	char			buf[BUFF_SIZE + 1];

	ret = 0;
	elem = NULL;
	str = NULL;
	if ((elem = elem_exist(lst, fd)) != NULL)
		return (next_line(elem, line));
	if (lst)
	{
		if (!(elem = ft_lstnewlast(lst, str, sizeof(t_str *))))
			return (-1);
	}
	else
	{
		if (!(elem = ft_lstnew(str, sizeof(t_str *))))
			return (-1);
		lst = elem;
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		str->str = self_join(str->str, buf);
		printf("test\n");
	}
	str->fd = fd;
	printf("test!!!\n");
	return (next_line(elem, line));
}
