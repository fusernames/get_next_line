/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 07:36:33 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/22 09:41:07 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char	**create_tab(size_t size)
{
	char	**tab;
	tab = ft_memalloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	tab[size] = NULL;
	return (tab);
}*/

static int		getsize(t_list *lst)
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
		lst = lst->next;
	}
	return (total);
}

static void		createline(t_list *lst, char **line)
{
	char	*content;
	char	*tmp;
	
	tmp = *line;
	*line = malloc(sizeof(char) * getsize(lst));
	while (lst)
	{
		content = (char *)lst->content;
		ft_strcat(*line, content);
		lst = lst->next;
	}
	free(tmp);
	ft_lstrm(lst);
}

static int		next_line(const char *buf)
{
	int		i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	return (i);
}

int				get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE];
	int				ret;
	int				i;
	t_list			*new;
	t_list 			*start;

	i = 0;
	start = NULL;
	new = NULL;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n' && start == NULL)
		start = ft_lstnew(&buf[i + 1], sizeof(char) * (i + 1 + next_line(&buf [i + 1]) - i));
	else if (buf[i] == '\n' && start)
		new = ft_lstnewlast(start, &buf[i + 1], sizeof(char) * (i + 1 + next_line(&buf [i + 1]) - i));
	createline(start, line);
	ft_lstdebugchar(start);
	return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		i = 0;
		buf[ret] = '\0';
		while (buf[i] && buf[i] != '\n')
			i++;
		if (start == NULL)
			start = ft_lstnew(buf, sizeof(char) * i);
		else
			new = ft_lstnewlast(start, buf, sizeof(char) * i);
		if (buf[i] == '\n')
			break;
	}
	if (ret == 0)
		return (0);
	ft_lstdebugchar(start);
	createline(start, line);
	return (1);
}

int		main(void)
{
	char	*tab;
	int		fd;

	tab = NULL;
	fd = open("test", O_RDONLY);
	while(get_next_line(fd, &tab))
		printf("%s\n", tab);
	//printf("%s", tab);
}
