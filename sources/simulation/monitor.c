/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:20:31 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/30 10:13:57 by anacharp         ###   ########.fr       */
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

	last = 0;
	i = 0;
	while (i < data->nb_coder)
	{
		pthread_mutex_lock(&data->coders[i].last_lock);
		last = data->coders[i].last_compile;
		pthread_mutex_unlock(&data->coders[i].last_lock);
		if (last != 0)
		{
			if ((get_sim_time(data) - last) >= data->burn_t)
			{
				pthread_mutex_lock(&data->log_lock);
				data->stop_simu = 1;
				pthread_mutex_unlock(&data->log_lock);
				print_status(&data->coders[i], BURN);
				return (1);
			}
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
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (simulation(data) == 0)
	{
		usleep(1000);
	}
	while (i < data->nb_coder)
	{
		pthread_mutex_lock(&data->dongles[i].lock);
		pthread_cond_broadcast(&data->dongles[i].cond);
		pthread_mutex_unlock(&data->dongles[i].lock);
		i++;
	}
	return (NULL);
}
