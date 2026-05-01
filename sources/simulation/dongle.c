/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:31:02 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/01 11:06:44 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	drop_dongles(t_coder *coder)
{
	if (check_flag(coder) == 1)
		return (1);
	pthread_mutex_lock(&coder->first->lock);
	coder->first->available = 0;
	coder->first->cld_b = get_sim_time(coder->data);
	pthread_cond_broadcast(&coder->first->cond);
	pthread_mutex_unlock(&coder->first->lock);
	pthread_mutex_lock(&coder->sec->lock);
	coder->sec->available = 0;
	coder->sec->cld_b = get_sim_time(coder->data);
	pthread_cond_broadcast(&coder->sec->cond);
	pthread_mutex_unlock(&coder->sec->lock);
	coder->first = NULL;
	coder->sec = NULL;
	return (0);
}

int	take_dongle(t_coder *coder, t_dongle *first, t_dongle *sec)
{
	if (check_flag(coder) == 1)
		return (1);
	coder->first = first;
	coder->sec = sec;
	print_status(coder, TAKE_DONGLE);
	first->available = 1;
	print_status(coder, TAKE_DONGLE);
	sec->available = 1;
	return (0);
}

int	i_want_dongle(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	if (check_flag(coder) == 1)
		return (1);
	if (strcmp(data->schedul, "fifo") == 0)
	{
		if (fifo(coder) == 1)
			return (1);
		else
			return (0);
	}
	// else
	// {
	// 	if (edf(coder) != 0)
	// 		return (1);
	// }
	return (0);
}
