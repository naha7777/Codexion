/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:20:31 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 11:29:23 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_finish(t_data *data)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i <= data->nb_coder)
	{
		pthread_mutex_lock(&data->coders[i].nb_lock);
		if (data->coders[i].nb_compiled >= data->tt_compil)
			count ++;
		pthread_mutex_unlock(&data->coders[i].nb_lock);
		if (count == data->nb_coder)
		{
			pthread_mutex_lock(&data->log_lock);
			data->stop_simu = 1;
			pthread_mutex_unlock(&data->log_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_burn_out(t_data *data)
{
	int	i;
	int	last;
	long long time;

	last = 0;
	i = 0;
	while (i < data->nb_coder)
	{
		pthread_mutex_lock(&data->coders[i].last_lock);
		last = data->coders[i].last_compile;
		pthread_mutex_unlock(&data->coders[i].last_lock);
		if ((get_time() - last) >= data->burn_t)
		{
			pthread_mutex_lock(&data->log_lock);
			data->stop_simu = 1;
			pthread_mutex_unlock(&data->log_lock);
			pthread_mutex_lock(&data->log_lock);
			time = (get_time() - data->start_time);
			printf("%lli %i %s\n", time, data->coders[i].id, BURN);
			pthread_mutex_unlock(&data->log_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	simulation(t_data *data)
{
	if (check_burn_out(data) == 1)
		return (1);
	else if (check_finish(data) == 1)
		return (1);
	else
		return (0);
}

void	*go_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (simulation(data) == 0)
	{
		usleep(1000);
	}
	return (NULL);
}
