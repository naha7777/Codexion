/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:43 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/04 11:30:49 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

	// if (strcmp(d->schedul, "edf") == 0)
	// {
	// 	if (heap_peek(&f->heap) == -1 || heap_peek(&n->heap) == -1)
	// 		return (1);
	// 	if (c->id != heap_peek(&f->heap) || c->id != heap_peek(&n->heap))
	// 		return (1);
	// }

static void	check_heaps(int id, t_heap *heap, t_coder *c)
{
	int	i;
	long long	deadline;

	i = 0;
	pthread_mutex_lock(&c->last_lock);
	deadline = c->last_compile + c->data->burn_t;
	pthread_mutex_unlock(&c->last_lock);
	while (i < heap->size)
	{
		if (heap->array[i].coder_id == id)
			return ;
		i++;
	}
	if (heap->size < 2)
		heap_push(heap, id, deadline);
}

static void	put_in_heaps(int id, t_dongle *f, t_dongle *s, t_coder *c)
{
	t_heap	*first;
	t_heap	*sec;
	int i;

	i = 0;
	pthread_mutex_lock(&c->data->global_lock);
	first = &f->heap;
	sec = &s->heap;
	check_heaps(id, first, c);
	check_heaps(id, sec, c);
	pthread_mutex_unlock(&c->data->global_lock);
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
	put_in_heaps(id, first, sec, coder);
	return (0);
}

int	edf(t_coder *coder)
{
	t_data	*data;
	int		id;

	id = coder->id;
	data = coder->data;
	if (check_flag(coder) == 1)
		return (1);
	if (check_id(id, coder, data))
		return (1);
	return (0);
}
