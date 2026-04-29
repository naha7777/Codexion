/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:20:29 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 11:03:55 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_flag(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->stop_lock);
	if (coder->data->stop_simu == 1)
		return (1),
	pthread_mutex_unlock(&coder->data->stop_lock);
	return (0);
}

static int dongle()
{
	
}


void	*fifo(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	while (check_flag(coder) == 0)
	{
		usleep(10);
	}
	// pthread_mutex_lock(&data->log_lock);
	// printf("codeur %i: je me reveille\n", coder->id);
	// pthread_mutex_unlock(&data->log_lock);
	return (NULL);
}

// check flag
// prend dongles si dispo
