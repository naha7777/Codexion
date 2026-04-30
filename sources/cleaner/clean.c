/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:14:47 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/30 09:46:37 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_coders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_coder)
	{
		pthread_join(data->coders[i].thread_id, NULL);
		i++;
	}
	pthread_join(data->monitor_id, NULL);
	printf("finito");
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
	mutex_destroy(data);
	free(data->coders);
	destroy_c_m(data);
	free(data->dongles);
	pthread_mutex_destroy(&data->log_lock);
	pthread_mutex_destroy(&data->stop_lock);
}
