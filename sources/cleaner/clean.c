/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:14:47 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/01 11:44:52 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	join_coders(t_data *data)
{
	int	i;

	i = 0;
	printf("[MAIN] Waiting for Monitor...\n");
	pthread_join(data->monitor_id, NULL);
	printf("[MAIN] Monitor joined! All stop flags should be set.\n");
	while (i < data->nb_coder)
	{
		printf("[MAIN] Waiting for Coder %d...\n", i + 1);
		if (data->coders[i].thread_id != 0)
		{
			pthread_join(data->coders[i].thread_id, NULL);
			printf("[MAIN] Coder %d joined!\n", i + 1);
		}
		i++;
	}
}

static void	destroy_c_m(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coder)
	{
		pthread_mutex_destroy(&data->dongles[i].lock);
		pthread_cond_destroy(&data->dongles[i].cond);
		i++;
	}
}

static void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coder)
	{
		pthread_mutex_destroy(&data->coders[i].last_lock);
		pthread_mutex_destroy(&data->coders[i].nb_lock);
		i++;
	}
}

void	problem_clean(t_data *data)
{
	while (data->init_step > 0)
	{
		if (data->init_step == 6)
		{
			join_coders(data);
			mutex_destroy(data);
		}
		else if (data->init_step == 5)
			free(data->coders);
		else if (data->init_step == 4)
			destroy_c_m(data);
		else if (data->init_step == 3)
			free(data->dongles);
		else if (data->init_step == 2)
			pthread_mutex_destroy(&data->log_lock);
		else if (data->init_step == 1)
			pthread_mutex_destroy(&data->stop_lock);
		data->init_step--;
	}
}

void	end_clean(t_data *data)
{
	join_coders(data);
	printf("go destroy");
	mutex_destroy(data);
	free(data->coders);
	destroy_c_m(data);
	free(data->dongles);
	pthread_mutex_destroy(&data->log_lock);
	pthread_mutex_destroy(&data->stop_lock);
}
