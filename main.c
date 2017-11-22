/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaroff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:40:53 by alcaroff          #+#    #+#             */
/*   Updated: 2017/11/22 15:41:52 by alcaroff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			main(void)
{
	char	*tab;
	int		fd;
	int		i = 0;

	tab = NULL;
	fd = open("test", O_RDONLY);
	while(get_next_line(fd, &tab))
	{
		printf("%d -> ", i);
		printf("%s\n", tab);
		i++;
	}
	//printf("%s", tab);
}
