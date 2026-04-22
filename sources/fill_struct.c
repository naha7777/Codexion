/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:08:46 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/22 18:34:51 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int thread_creation(int i, t_data *data)
{
	if (strcmp(data->schedul, "fifo") == 0)
	{
		if (pthread_create(&data->coders[i].thread_id, NULL, fifo, &data->coders[i]) != 0)
		{
			pthread_mutex_lock(&data->stop_lock);
			data->stop_simu = 1;
			pthread_mutex_unlock(&data->stop_lock);
			while (--i >= 0)
				pthread_join(data->coders[i].thread_id, NULL);
			return (1);
		}
		return (0);
	}
	if (pthread_create(&data->coders[i].thread_id, NULL, edf, &data->coders[i]) != 0)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->stop_simu = 1;
		pthread_mutex_unlock(&data->stop_lock);
		while (--i >= 0)
			pthread_join(data->coders[i].thread_id, NULL);
		return (1);
	}
	return(0);
}

static int fill_coder(t_data *data)
{
	int i;

	i = 0;
	data->coders = malloc(sizeof(t_coder)*data->nb_coder);
	if (!data->coders)
		return (1);
	data->init_step++;
	while (i < data->nb_coder)
	{
		data->coders[i].id = i + 1;
		data->coders[i].nb_compiled = 0;
		data->coders[i].last_compile = 0;
		data->coders[i].data = data;
		if (thread_creation(i, data) != 0)
			return (1);
		i++;
	}
	return (data->init_step++, 0);
}

static void destroy(int i, t_data *data)
{
	while(--i >=0)
	{
		pthread_mutex_destroy(&data->dongles[i].lock);
		pthread_cond_destroy(&data->dongles[i].cond);
	}
}

static int fill_dongle(t_data *data)
{
	int i;

	i = 0;
	data->dongles = malloc(sizeof(t_dongle)*data->nb_coder);
	if (!data->dongles)
		return (1);
	data->init_step++;
	while(i < data->nb_coder)
	{
		if (pthread_mutex_init(&data->dongles[i].lock, NULL) != 0)
			return (destroy(i, data), 1);
		if (pthread_cond_init(&data->dongles[i].cond, NULL) != 0)
		{
			pthread_mutex_destroy(&data->dongles[i].lock);
			return (destroy(i, data), 1);
		}
		data->dongles[i].cooldown_begin = 0;
		i++;
	}
	return (data->init_step++, 0);
}

int fill_data(char **av, t_data *data)
{
	data->nb_coder = atoi(av[1]);
	data->burn_t = atoi(av[2]);
	data->compil_t = atoi(av[3]);
	data->debug_t = atoi(av[4]);
	data->refact_t = atoi(av[5]);
	data->tt_compil = atoi(av[6]);
	data->dongles_cld = atoi(av[7]);
	data->schedul = av[8];
	data->stop_simu = 0;
	if (pthread_mutex_init(&data->stop_lock, NULL) != 0)
		return (1);
	data->init_step++;
	if (pthread_mutex_init(&data->log_lock, NULL) != 0)
		return (1);
	data->init_step++;
	if (fill_dongle(data) != 0)
		return (1);
	if (fill_coder(data) != 0)
		return (1);
	return (0);
}
