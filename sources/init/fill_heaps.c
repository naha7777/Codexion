/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heaps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:55:46 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 13:56:04 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	fill_fifo_heap(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coder)
	{
		data->heap.array[i].coder_id = data->coders[i].id;
		data->heap.size++;
		i++;
	}
}

static void	fill_edf_heap(t_data *data)
{
	int	i;
	int	y;

	i = -1;
	y = 0;
	while (i++ < data->nb_coder - 1)
	{
		if (data->coders[i].id % 2 != 0)
		{
			data->heap.array[y].coder_id = data->coders[i].id;
			data->heap.size++;
			y++;
		}
	}
	i = -1;
	while (i++ < data->nb_coder - 1)
	{
		if (data->coders[i].id % 2 == 0)
		{
			data->heap.array[y].coder_id = data->coders[i].id;
			data->heap.size ++;
			y++;
		}
	}
}

void	fill_heap(t_data *data)
{
	if (strcmp(data->schedul, "edf") == 0)
		fill_edf_heap(data);
	else
		fill_fifo_heap(data);
}
