/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 07:36:33 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/22 12:20:30 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_size(t_list *lst)
{
	int 	i;
	int		total = 0;
	char	*content;

	while (lst)
	{
		content = (char *)lst->content;
		i = 0;
		while(content[i] != '\n' && content[i])
		{
			i++;
			total++;
		}
		if (content[i] == '\n')
			content[i] = '\0';
		lst = lst->next;
	}
	return (total);
}

static void		create_line(t_list *lst, char **line)
{
	char	*content;
	char	*tmp;
	
	tmp = *line;
	*line = malloc(sizeof(char) * get_size(lst));
	while (lst)
	{
		content = (char *)lst->content;
		ft_strcat(*line, content);
		lst = lst->next;
	}
	free(tmp);
	ft_lstrm(lst);
}

static t_list	*add_at_lst(t_list **start, t_list **new, char *buf, int content_size)
{
	if (*start == NULL)
	{
		*start = ft_lstnew(buf, content_size);
		if (*start == NULL)
			return (NULL);
	}
	else
	{
		*new = ft_lstnewlast(*start, buf, content_size);
		if (*new == NULL)
			return (NULL);
	}
	return (*start);
}

/*static int	next_cr(const char *str)
{
	int		i;
	i = 1;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}*/

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE];
	static char		*saved = NULL;
	int				i;
	int				ret;
	t_list			*start;
	t_list			*new;

	start = NULL;
	new = NULL;
	// part 1
	if (saved)
	{
		i = 0;
		while (saved[i] != '\n' && saved[i])
			i++;
		add_at_lst(&start, &new, saved, sizeof(char) * i + 1);
		saved = &saved[i];
		if (*saved == '\n')
		{
			saved++;
			create_line(start, line);
			return (1);
		}
	}
	// part 2
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		i = 0;
		while(buf[i] && buf[i] != '\n')
			i++;
		add_at_lst(&start, &new, buf, sizeof(char) * i + 1);
		if (buf[i] == '\n')
		{
			saved = ft_strdup(&buf[i + 1]);
			break;
		}
	}
	if (ret == 0)
		return (0);
	create_line(start, line);
	return (1);
}

int			main(void)
{
	char	*tab;
	int		fd;

	tab = NULL;
	fd = open("test", O_RDONLY);
	while(get_next_line(fd, &tab))
		printf("%s\n", tab);
	//printf("%s", tab);
}
