/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:31:02 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/02 16:43:48 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	drop_dongles(t_coder *coder)
{
	// if (check_flag(coder) == 1)
	// 	return (1);
	if (!coder->first || !coder->sec)
        return (0);
	pthread_mutex_lock(&coder->data->global_lock);
	coder->first->available = 0;
	coder->first->cld_b = get_sim_time(coder->data);
	coder->sec->available = 0;
	coder->sec->cld_b = get_sim_time(coder->data);
	pthread_cond_broadcast(&coder->data->global_cond);
	pthread_mutex_unlock(&coder->data->global_lock);
	coder->first = NULL;
	coder->sec = NULL;
	// usleep(50000);
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
	first->nb_took ++;
	print_status(coder, TAKE_DONGLE);
	sec->available = 1;
	sec->nb_took ++;
	return (0);
}

int	i_want_dongle(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	if (check_flag(coder) == 1)
		return (1);
	if (check_compil(coder, data) == 1)
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
