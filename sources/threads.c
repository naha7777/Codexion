/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:44:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/22 11:13:55 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int count = 0;
pthread_mutex_t door;

static void *ft_p(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&door);
	count++;
	pthread_mutex_unlock(&door);
	return NULL;
}

void threads(int ac, char **av)
{
	(void)ac;
	pthread_t tid, tid2;
	pthread_mutex_init(&door, NULL);

	pthread_create(&tid, NULL, ft_p, av[8]);
	pthread_create(&tid2, NULL, ft_p, av[7]);

	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);
	printf("Valeur finale : %d\n", count);
	pthread_mutex_destroy(&door);
	printf("tlm a fini");
}
