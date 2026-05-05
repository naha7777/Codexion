/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:08:46 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 15:18:02 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	thread_creation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coder)
	{
		if (pthread_create(&data->coders[i].thread_id, NULL,
				routine, &data->coders[i]) != 0)
		{
			pthread_mutex_lock(&data->stop_lock);
			data->stop_simu = 1;
			pthread_mutex_unlock(&data->stop_lock);
			while (--i >= 0)
				pthread_join(data->coders[i].thread_id, NULL);
			return (thread_fail(i, data), 1);
		}
		i++;
	}
	return (0);
}

static int	fill_coder(t_data *data)
{
	int	i;

	i = 0;
	data->coders = ft_calloc(data->nb_coder, sizeof(t_coder));
	if (!data->coders)
		return (1);
	data->init_step++;
	while (i < data->nb_coder)
	{
		data->coders[i].id = i + 1;
		data->coders[i].data = data;
		if (pthread_mutex_init(&data->coders[i].last_lock, NULL) != 0)
			return (simple_destroy(i, data), 1);
		if (pthread_mutex_init(&data->coders[i].nb_lock, NULL) != 0)
			return (double_destroy(i, data), 1);
		i++;
	}
	fill_heap(data);
	return (data->init_step++, 0);
}

static int	fill_dongle(t_data *data)
{
	data->dongles = ft_calloc(data->nb_coder, sizeof(t_dongle));
	if (!data->dongles)
	{
		printf("Error during memory allocation.");
		return (1);
	}
	data->init_step++;
	if (pthread_mutex_init(&data->global_lock, NULL) != 0)
		return (destroy(data), 1);
	if (pthread_cond_init(&data->global_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&data->global_lock);
		return (destroy(data), 1);
	}
	return (data->init_step++, 0);
}

int	fill_data(char **av, t_data *data)
{
	data->nb_coder = ft_atol(av[1]);
	data->burn_t = ft_atol(av[2]);
	data->compil_t = ft_atol(av[3]);
	data->debug_t = ft_atol(av[4]);
	data->refact_t = ft_atol(av[5]);
	data->tt_compil = ft_atol(av[6]);
	data->d_cld = ft_atol(av[7]);
	data->schedul = av[8];
	data->stop_simu = 0;
	data->init_step = 0;
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
	if (pthread_create(&data->monitor_id, NULL, go_monitor, data) != 0)
		return (1);
	if (thread_creation(data) != 0)
		return (1);
	return (0);
}
