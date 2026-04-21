/* *********************************************************************** */
/*                                                                         */
/*                                                     :::      ::::::::   */
/* main.c                                            :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+     */
/* By: anacharp <anacharp@student.42lehavre.fr   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+           */
/* Created: 2026/04/21 10:35:59 by anacharp        #+#    #+#              */
/* Updated: 2026/04/21 10:59:54 by anacharp        ###   ########.fr       */
/*                                                                         */
/* *********************************************************************** */

#include "codexion.h"

int main(int ac, char **av)
{
	if (ac != 9)
	printf("Invalid number of arguments: %i", ac);
		return (0);
	parser(ac, av);
	return(0);
}
