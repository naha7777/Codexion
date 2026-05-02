/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/02 17:21:32 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	wait(t_coder *c, t_dongle *f, t_dongle *n, t_data *d)
{
	long	now;

	if (check_flag(c) == 1)
		return (0);
	if (f->nb_took == 0 && n->nb_took == 0)
		return (0);
	if (f->available == 1 || n->available == 1)
		return (1);
	now = get_sim_time(d);
	if (f->nb_took != 0)
		if (now - f->cld_b < d->d_cld)
			return (1);
	if (n->nb_took != 0)
		if (now - n->cld_b < d->d_cld)
			return (1);
	return (0);
}

static int	check_available(t_coder *coder, t_data *data, t_dongle *first,
	t_dongle *sec)
{
	if (check_flag(coder) == 1)
		return (1);
	pthread_mutex_lock(&data->global_lock);
	while (wait(coder, first, sec, data) == 1)
	{
		pthread_cond_wait(&data->global_cond, &data->global_lock);
		if (check_flag(coder) == 1)
			return (pthread_mutex_unlock(&data->global_lock), 1);
	}
	if (check_flag(coder) == 1)
		return (pthread_mutex_unlock(&data->global_lock), 1);
	if (take_dongle(coder, first, sec) == 1)
		return (pthread_mutex_unlock(&data->global_lock), 1);
	return (pthread_mutex_unlock(&data->global_lock), 0);
}

static int	find_low(t_dongle *first, t_dongle *sec, t_coder *coder)
{
	t_dongle	*low;
	t_dongle	*high;

	if (first <= sec)
	{
		low = first;
		high = sec;
	}
	else
	{
		low = sec;
		high = first;
	}
	if (check_available(coder, coder->data, low, high) == 1)
		return (1);
	return (0);
}

static int	check_id(int id, t_coder *coder, t_data *data)
{
	t_dongle	*first;
	t_dongle	*sec;

	if (id == 1)
	{
		first = &data->dongles[id - 1];
		sec = &data->dongles[data->nb_coder - 1];
	}
	if (id == data->nb_coder)
	{
		first = &data->dongles[id - 2];
		sec = &data->dongles[data->nb_coder - 1];
	}
	if (id != 1 && id != data->nb_coder)
	{
		first = &data->dongles[id - 1];
		sec = &data->dongles[id - 2];
	}
	if (find_low(first, sec, coder) == 1)
		return (1);
	return (0);
}

int	fifo(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (check_flag(coder) == 1)
		return (1);
	if (check_id(id, coder, data) == 1)
		return (1);
	return (0);
}
