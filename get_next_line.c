/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 07:36:33 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/21 16:41:53 by alcaroff         ###   ########.fr       */
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

int		getsize(t_list *lst)
{
	int 	i;
	int		total = 0;
	char	*content;

	while (lst)
	{
		content = (char *)lst->content;
		i = 0;
		while(content[i] != '\n')
		{
			printf("%c", content[i]);
			i++;
			total++;
			if (content[i] == '\0')
				break;
		}
		lst = lst->next;
	}
	return (total);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE];
	int				ret;
	int				i;
	t_list			*new;
	static t_list 	*start = NULL;

	new = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE - 1)))
	{
		i = 0;
		buf[ret] = '\0';
		while (buf[i] && buf[i] != '\n')
			i++;
		if (start == NULL)
			start = ft_lstnew(buf, sizeof(char) * i);
		else
			new = ft_lstnewlast(start, buf, sizeof(char) * i);
		if (ret > i)
			new = ft_lstnewlast(start, &buf[i + 1], sizeof(char) * (ret - i + 1));
		if (buf[i] == '\n')
			break;
	}
	line = malloc(sizeof(char) * getsize(start));
	return (ret);
}

int		main(void)
{
	char	*tab;
	int		fd;

	tab = NULL;
	fd = open("test", O_RDONLY);
	get_next_line(fd, &tab);
	//printf("%s", tab);
}
