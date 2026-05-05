/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:02:56 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 10:22:10 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	heap_pop(t_heap *h)
{
	int	save_nb;
	int	i;

	save_nb = h->array[0].coder_id;
	h->array[0] = h->array[--h->size];
	i = 0;
	while (i < h->size)
	{
		h->array[i].coder_id = h->array[i + 1].coder_id;
		i++;
	}
	return (save_nb);
}

void	heap_last(t_heap *h)
{
	int	i;
	int	nb;

	i = 0;
	nb = heap_pop(h);
	while (i < h->size && h->array[i].coder_id != 0)
		i++;
	h->array[i].coder_id = nb;
	h->size++;
}

int	heap_peek(t_heap *h)
{
	if (h->size == 0)
		return (-1);
	return (h->array[0].coder_id);
}
