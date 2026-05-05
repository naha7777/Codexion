/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:08:46 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 09:48:39 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	thread_creation(int i, t_data *data)
{
	if (pthread_create(&data->coders[i].thread_id, NULL,
			routine, &data->coders[i]) != 0)
	{
		data->stop_simu = 1;
		while (--i >= 0)
			pthread_join(data->coders[i].thread_id, NULL);
		return (1);
	}
	return (0);
}

// static void	test(t_data *data)
// {
// 	int	i;
// 	i = 0;
// 	while (data->heap.array[i].coder_id != 0)
// 	{
// 		printf("[%i]", data->heap.array[i].coder_id);
// 		i++;
// 	}
// }

static void	fill_heap(t_data *data)
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
			data->heap.size ++;
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
	// test(data);
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
		if (thread_creation(i, data) != 0)
			return (thread_fail(i, data), 1);
		i++;
	}
	if (strcmp(data->schedul, "edf") == 0)
		fill_heap(data);
	return (data->init_step++, 0);
}

static int	fill_dongle(t_data *data)
{
	int	i;

	i = 0;
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
	return (0);
}
