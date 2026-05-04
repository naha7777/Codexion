/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:08:53 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/04 11:08:21 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	compil(t_coder *coder)
{
	if (check_flag(coder) == 1)
		return (1);
	print_status(coder, COMPIL);
	pthread_mutex_lock(&coder->nb_lock);
	coder->nb_compiled++;
	pthread_mutex_unlock(&coder->nb_lock);
	pthread_mutex_lock(&coder->last_lock);
	coder->last_compile = (get_sim_time(coder->data));
	pthread_mutex_unlock(&coder->last_lock);
	if (check_flag(coder) == 1)
		return (1);
	usleep(coder->data->compil_t * 1000);
	if (drop_dongles(coder) == 1)
		return (1);
	return (0);
}

static int	debug(t_coder *coder)
{
	if (check_flag(coder) == 1)
		return (1);
	print_status(coder, DEBUG);
	usleep(coder->data->debug_t * 1000);
	return (0);
}

static int	refactor(t_coder *coder)
{
	if (check_flag(coder) == 1)
		return (1);
	print_status(coder, REFACT);
	usleep(coder->data->refact_t * 1000);
	return (0);
}

static void	set_last_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->last_lock);
	coder->last_compile = get_sim_time(coder->data);
	pthread_mutex_unlock(&coder->last_lock);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	set_last_compile(coder);
	usleep(coder->id * 10000);
	if (check_flag(coder) == 0)
	{
		if (check_compil(coder, data) == 1)
			return (broadcast(data), NULL);
		while (i_want_dongle(coder) == 0 && check_compil(coder, data) == 0)
		{
			if (compil(coder) == 1)
				return (broadcast(data), NULL);
			if (debug(coder) == 1)
				return (broadcast(data), NULL);
			if (refactor(coder) == 1)
				return (broadcast(data), NULL);
			if (check_flag(coder) == 1)
				return (broadcast(data), NULL);
			if (strcmp(data->schedul, "fifo") == 0)
				usleep(coder->id * 500);
		}
	}
	return (broadcast(data), NULL);
}
