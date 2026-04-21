/* *********************************************************************** */
/*                                                                         */
/*                                                     :::      ::::::::   */
/* parser.c                                          :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+     */
/* By: anacharp <anacharp@student.42lehavre.fr   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+           */
/* Created: 2026/04/21 10:36:06 by anacharp        #+#    #+#              */
/* Updated: 2026/04/21 11:20:46 by anacharp        ###   ########.fr       */
/*                                                                         */
/* *********************************************************************** */

#include "codexion.h"

static int parse_nb(char *arg)
{
	int		i;
	int	nb;

	i = 0;
	if (arg[i] == '-' || !arg[i])
		return NULL;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return NULL;
		i++;
	}
	nb = atoi(arg);
	if (nb > INT_MAX || nb < INT_MIN)
		return NULL;
	return (nb);
}


void parser(int ac, char **av)
{
	int i;
	(void)av;
	(void)ac;
	i = 0;
	while(++i < ac - 1)
	{
		parse_nb(av[i]);
	}
}
