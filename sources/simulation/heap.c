/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:02:56 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/04 11:04:53 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_push(t_heap *h, int id, long long deadline)
{
	int i = h->size++;
	h->array[i] = (t_node){id, deadline};
	while (i > 0 && h->array[(i-1)/2].deadline > h->array[i].deadline)
	{
		t_node tmp = h->array[(i-1)/2];
		h->array[(i-1)/2] = h->array[i];
		h->array[i] = tmp;
		i = (i-1)/2;
	}
}

int	heap_peek(t_heap *h)
{
	if (h->size == 0)
		return (-1);
	return h->array[0].coder_id;
}

void	heap_pop(t_heap *h)
{
	h->array[0] = h->array[--h->size];
	int i = 0;
	while (1)
	{
		int left = 2*i+1, right = 2*i+2, smallest = i;
		if (left < h->size && h->array[left].deadline < h->array[smallest].deadline)
			smallest = left;
		if (right < h->size && h->array[right].deadline < h->array[smallest].deadline)
			smallest = right;
		if (smallest == i) break;
		t_node tmp = h->array[smallest];
		h->array[smallest] = h->array[i];
		h->array[i] = tmp;
		i = smallest;
	}
}
