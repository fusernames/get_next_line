/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:40:53 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/27 17:53:35 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			main(int ac, char **av)
{
	char	*tab;
	int		fd;
	int		i = 0;

	if (ac != 2)
		return (0);
	tab = NULL;
	fd = open(av[1], O_RDONLY);
	while(get_next_line(fd, &tab) > 0 && i < 10)
	{
		printf("%d -> ", i);
		printf("%s\n", tab);
		i++;
	}
	//printf("%s", tab);
}
