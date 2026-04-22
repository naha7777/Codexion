/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:48:56 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/22 13:16:07 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	parse_nb(char *arg)
{
	int		i;
	long	nb;

	i = 0;
	if (arg[i] == '-' || !arg[i])
	{
		printf("Invalid value '%s', put a positive integer", arg);
		return (INT_MIN);
	}
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			printf("Invalid value '%s', put an integer", arg);
			return (INT_MIN);
		}
		i++;
	}
	nb = ft_atol(arg);
	if (nb > INT_MAX || nb < INT_MIN)
	{
		printf("Invalid value '%s'", arg);
		return (INT_MIN);
	}
	return (nb);
}

static char	*parse_schedule(char *arg)
{
	char	*fifo;
	char	*edf;

	fifo = "fifo";
	edf = "edf";
	if (strcmp(arg, fifo) == 0 || strcmp(arg, edf) == 0)
		return (arg);
	printf("Invalid schedule '%s': choose between 'fifo' and 'edf'", arg);
	return (NULL);
}

int	parser(int ac, char **av)
{
	int		i;
	int		nb;
	char	*s;
	if (ac < 9 || ac > 9)
	{
		printf("Invalid number of arguments: %i", ac);
		return (1);
	}

	i = 1;
	while (i < ac - 1)
	{
		nb = parse_nb(av[i]);
		if (nb == INT_MIN)
			return (1);
		i++;
	}
	s = parse_schedule(av[ac - 1]);
	if (s == NULL)
		return (1);
	return (0);
}
