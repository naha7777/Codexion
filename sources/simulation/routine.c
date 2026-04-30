/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:08:53 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/30 11:25:17 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void compil(t_coder *coder)
{
	if (check_flag(coder) == 1)
		return ;
	print_status(coder, COMPIL);
	usleep(coder->data->compil_t*1000);
	pthread_mutex_lock(&coder->nb_lock);
	coder->nb_compiled++;
	pthread_mutex_unlock(&coder->nb_lock);
	pthread_mutex_lock(&coder->last_lock);
	coder->last_compile = (get_sim_time(coder->data));
	pthread_mutex_unlock(&coder->last_lock);
	drop_dongles(coder);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	while (check_flag(coder) == 0)
	{
		if (i_want_dongle(coder) == 0)
		{
			compil(coder);
			// debug
			// refactoring
		}
	}
	return (NULL);
}
