/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 17:13:39 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	check_first(t_coder *coder, t_data *data, int id)
{
	t_dongle *f;
	t_dongle *n;

	n = &data->dongles[data->nb_coder-1];
	f = &data->dongles[id-1];
	pthread_mutex_lock(&f->lock);
	pthread_mutex_lock(&n->lock);
	while (f->available == 1 || n->available == 1 || (get_time() - f->cld_b < data->d_cld) || (get_time() - n->cld_b < data->d_cld))
	{
		pthread_mutex_unlock(&f->lock);
		pthread_mutex_unlock(&n->lock);
		pthread_cond_wait(&f->cond, &f->lock);
		pthread_mutex_lock(&f->lock);
		pthread_mutex_lock(&n->lock);
	}
	take_dongle(coder, f, n);
	pthread_mutex_unlock(&f->lock);
	pthread_mutex_unlock(&n->lock);
}

static void	check_last(t_coder *coder, t_data *data, int id)
{
	t_dongle *f;
	t_dongle *n;

	n = &data->dongles[id-1];
	f = &data->dongles[id-2];
	pthread_mutex_lock(&f->lock);
	pthread_mutex_lock(&n->lock);
	while (f->available == 1 || n->available == 1 || (get_time() - f->cld_b < data->d_cld) || (get_time() - n->cld_b < data->d_cld))
	{
		pthread_mutex_unlock(&f->lock);
		pthread_mutex_unlock(&n->lock);
		pthread_cond_wait(&f->cond, &f->lock);
		pthread_mutex_lock(&f->lock);
		pthread_mutex_lock(&n->lock);
	}
	take_dongle(coder, f, n);
	pthread_mutex_unlock(&f->lock);
	pthread_mutex_unlock(&n->lock);
}

static void	check_else(t_coder *coder, t_data *data, int id)
{
	t_dongle *f;
	t_dongle *n;

	n = &data->dongles[id-2];
	f = &data->dongles[id-1];
	pthread_mutex_lock(&f->lock);
	pthread_mutex_lock(&n->lock);
	while (f->available == 1 || n->available == 1 || (get_time() - f->cld_b < data->d_cld) || (get_time() - n->cld_b < data->d_cld))
	{
		pthread_mutex_unlock(&f->lock);
		pthread_mutex_unlock(&n->lock);
		pthread_cond_wait(&f->cond, &f->lock);
		pthread_mutex_lock(&f->lock);
		pthread_mutex_lock(&n->lock);
	}
	take_dongle(coder, f, n);
	pthread_mutex_unlock(&f->lock);
	pthread_mutex_unlock(&n->lock);
}

void	fifo(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (id == 1)
		check_first(coder, data, id);
	else if (id == data->nb_coder)
		check_last(coder, data, id);
	else
		check_else(coder, data, id);
}
