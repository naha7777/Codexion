/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:31:02 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 12:49:21 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	take_dongle(t_coder *coder, t_dongle *first, t_dongle *sec, t_data *data)
{
	pthread_mutex_lock(&first);
	first->available = 1;
	print_status(coder, TAKE_DONGLE);
	pthread_mutex_unlock(&first);
	pthread_mutex_lock(&sec);
	sec->available = 1;
	print_status(coder, TAKE_DONGLE);
	pthread_mutex_unlock(&sec);
}

void	i_want_dongle(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	if (strcmp(data->schedul, "fifo") == 0)
	{
		fifo(coder);
	}
	else
		edf(coder);
}
