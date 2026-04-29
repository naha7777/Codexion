/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:43:01 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 12:47:21 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	check_first(t_coder *coder, t_data *data, int id)
{
	if (data->dongles[id].available == 0)
		if (data->dongles[data->nb_coder].available == 0)
			take_dongle(coder, &data->dongles[id], &data->dongles[data->nb_coder], &data);
}

static void	check_last(t_coder *coder, t_data *data, int id)
{
	if (data->dongles[id-1].available == 0)
		if (data->dongles[id].available == 0)
			take_dongle(coder, &data->dongles[id-1], &data->dongles[id], &data);
}

static void	check_else(t_coder *coder, t_data *data, int id)
{
	if (data->dongles[id].available == 0)
			if (data->dongles[id-1].available == 0)
				take_dongle(coder, &data->dongles[id], &data->dongles[id-1], &data);
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
