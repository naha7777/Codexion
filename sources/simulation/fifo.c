/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/30 10:06:33 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	wait(t_coder *c, t_dongle *f, t_dongle *n, t_data *d)
{
	long	now;

	if (check_flag(c) == 1)
		return (0);
	if (f->available == 1 || n->available == 1)
		return (1);
	now = get_time();
	if ((now - f->cld_b < d->d_cld) || (now - n->cld_b < d->d_cld))
		return (1);
	return (0);
}

static int	check_first(t_coder *coder, t_data *data, int id)
{
	t_dongle	*first;
	t_dongle	*neighbor;

	neighbor = &data->dongles[data->nb_coder-1];
	first = &data->dongles[id-1];
	pthread_mutex_lock(&first->lock);
	pthread_mutex_lock(&neighbor->lock);
	while (wait(coder, first, neighbor, data) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&neighbor->lock);
		pthread_cond_wait(&first->cond, &first->lock);
		pthread_mutex_lock(&first->lock);
		pthread_mutex_lock(&neighbor->lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&neighbor->lock);
		return (1);
	}
	take_dongle(coder, first, neighbor);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&neighbor->lock);
	return (0);
}

static int	check_last(t_coder *coder, t_data *data, int id)
{
	t_dongle	*first;
	t_dongle	*neighbor;

	neighbor = &data->dongles[id-1];
	first = &data->dongles[id-2];
	pthread_mutex_lock(&first->lock);
	pthread_mutex_lock(&neighbor->lock);
	while (wait(coder, first, neighbor, data) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&neighbor->lock);
		pthread_cond_wait(&first->cond, &first->lock);
		pthread_mutex_lock(&first->lock);
		pthread_mutex_lock(&neighbor->lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&neighbor->lock);
		return (1);
	}
	take_dongle(coder, first, neighbor);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&neighbor->lock);
	return (0);
}

static int	check_else(t_coder *coder, t_data *data, int id)
{
	t_dongle	*first;
	t_dongle	*neighbor;

	first = &data->dongles[id-1];
	neighbor = &data->dongles[id-2];
	pthread_mutex_lock(&first->lock);
	pthread_mutex_lock(&neighbor->lock);
	while (wait(coder, first, neighbor, data) == 1)
	{
		// pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&neighbor->lock);
		pthread_cond_wait(&first->cond, &first->lock);
		// pthread_mutex_lock(&first->lock);
		pthread_mutex_lock(&neighbor->lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&neighbor->lock);
		return (1);
	}
	take_dongle(coder, first, neighbor);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&neighbor->lock);
	return (0);
}

int	fifo(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (id == 1)
		if (check_first(coder, data, id) == 1)
			return (1);
	if (id == data->nb_coder)
		if (check_last(coder, data, id) == 1)
			return (1);
	if (id != 1 || id != data->nb_coder)
		if (check_else(coder, data, id) == 1)
			return (1);
	return (0);
}
