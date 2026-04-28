/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:20:29 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/28 17:54:55 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*fifo(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	pthread_mutex_lock(&data->log_lock);
	printf("codeur %i: je me reveille\n", coder->id);
	pthread_mutex_unlock(&data->log_lock);
	return (NULL);
}

//last_compile = temps du debut de la compile ou la fin ?
