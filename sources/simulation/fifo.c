/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/30 11:43:16 by anacharp         ###   ########.fr       */
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
	if (check_flag(coder) == 1)
		return (1);
	pthread_mutex_lock(&data->dongles[id-1].lock);
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-1].lock);
		return (1);
	}
	pthread_mutex_lock(&data->dongles[data->nb_coder-1].lock);
	while (wait(coder, &data->dongles[id-1], &data->dongles[data->nb_coder-1],
				data) == 1)
	{
		pthread_mutex_unlock(&data->dongles[data->nb_coder-1].lock);
		pthread_cond_wait(&data->dongles[id-1].cond, &data->dongles[id-1].lock);
		if (check_flag(coder) == 1)
			return(pthread_mutex_unlock(&data->dongles[id-1].lock), 1);
		pthread_mutex_lock(&data->dongles[data->nb_coder-1].lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-1].lock);
		return (pthread_mutex_unlock(&data->dongles[data->nb_coder-1].lock), 1);
	}
	take_dongle(coder, &data->dongles[id-1], &data->dongles[data->nb_coder-1]);
	pthread_mutex_unlock(&data->dongles[id-1].lock);
	return (pthread_mutex_unlock(&data->dongles[data->nb_coder-1].lock), 0);
}

static int	check_last(t_coder *coder, t_data *data, int id)
{
	if (check_flag(coder) == 1)
		return (1);
	pthread_mutex_lock(&data->dongles[id-2].lock);
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-2].lock);
		return (1);
	}
	pthread_mutex_lock(&data->dongles[id-1].lock);
	while (wait(coder, &data->dongles[id-2], &data->dongles[id-1], data) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-1].lock);
		pthread_cond_wait(&data->dongles[id-2].cond, &data->dongles[id-2].lock);
		if (check_flag(coder) == 1)
			return(pthread_mutex_unlock(&data->dongles[id-2].lock), 1);
		pthread_mutex_lock(&data->dongles[id-1].lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-2].lock);
		return (pthread_mutex_unlock(&data->dongles[id-1].lock), 1);
	}
	take_dongle(coder, &data->dongles[id-2], &data->dongles[id-1]);
	pthread_mutex_unlock(&data->dongles[id-2].lock);
	return (pthread_mutex_unlock(&data->dongles[id-1].lock), 0);
}

static int	check_else(t_coder *coder, t_data *data, int id)
{
	if (check_flag(coder) == 1)
		return (1);
	pthread_mutex_lock(&data->dongles[id-1].lock);
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-1].lock);
		return (1);
	}
	pthread_mutex_lock(&data->dongles[id-2].lock);
	while (wait(coder, &data->dongles[id-1], &data->dongles[id-2], data) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-2].lock);
		pthread_cond_wait(&data->dongles[id-1].cond, &data->dongles[id-1].lock);
		if (check_flag(coder) == 1)
			return(pthread_mutex_unlock(&data->dongles[id-1].lock), 1);
		pthread_mutex_lock(&data->dongles[id-2].lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&data->dongles[id-1].lock);
		return (pthread_mutex_unlock(&data->dongles[id-2].lock), 1);
	}
	take_dongle(coder, &data->dongles[id-1], &data->dongles[id-2]);
	pthread_mutex_unlock(&data->dongles[id-1].lock);
	return (pthread_mutex_unlock(&data->dongles[id-2].lock), 0);
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
	if (id != 1 && id != data->nb_coder)
		if (check_else(coder, data, id) == 1)
			return (1);
	return (0);
}
