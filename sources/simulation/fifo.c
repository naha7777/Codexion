/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/01 10:41:20 by anacharp         ###   ########.fr       */
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

static int	check_available(t_coder *coder, t_data *data, t_dongle *first,
	t_dongle *sec)
{
	if (check_flag(coder) == 1)
		return (1);
	pthread_mutex_lock(&first->lock);
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		return (1);
	}
	pthread_mutex_lock(&sec->lock);
	while (wait(coder, first, sec, data) == 1)
	{
		pthread_mutex_unlock(&sec->lock);
		pthread_cond_wait(&first->cond, &first->lock);
		if (check_flag(coder) == 1)
			return(pthread_mutex_unlock(&first->lock), 1);
		pthread_mutex_lock(&sec->lock);
	}
	if (check_flag(coder) == 1)
	{
		pthread_mutex_unlock(&first->lock);
		return (pthread_mutex_unlock(&sec->lock), 1);
	}
	take_dongle(coder, first, sec);
	pthread_mutex_unlock(&first->lock);
	return (pthread_mutex_unlock(&sec->lock), 0);
}

// static int	check_available(t_coder *c, t_data *d, t_dongle *f, t_dongle *s)
// {
// 	printf("%i, %lld, %i, %i\n", c->id, d->burn_t, f->available, s->available);
// 	printf("no problem bro\n");
// 	return (0);
// }

static int	check_id(int id, t_coder *coder, t_data *data)
{
	t_dongle	*first;
	t_dongle	*sec;

	if (id == 1)
	{
		first = &data->dongles[id-1];
		sec = &data->dongles[data->nb_coder-1];
	}
	if (id == data->nb_coder)
	{
		first = &data->dongles[id-2];
		sec = &data->dongles[data->nb_coder-1];
	}
	if (id != 1 && id != data->nb_coder)
	{
		first = &data->dongles[id-1];
		sec = &data->dongles[id-2];
	}
	if (check_available(coder, data, first, sec) == 1)
			return (1);
		else
			return (0);
	return (printf("ERROR: invalid id : %i", id), 1);
}

int	fifo(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (check_id(id, coder, data) == 1)
		return (1);
	return (0);
}
