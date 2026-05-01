/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:33:23 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/01 10:15:57 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_status(t_coder *coder, char *status)
{
	pthread_mutex_lock(&coder->data->log_lock);
	pthread_mutex_lock(&coder->data->stop_lock);
	printf("%lli %i %s\n", get_sim_time(coder->data), coder->id, status);
	pthread_mutex_unlock(&coder->data->stop_lock);
	pthread_mutex_unlock(&coder->data->log_lock);
}

int	check_compil(t_coder *coder, t_data *data)
{
	pthread_mutex_lock(&coder->nb_lock);
	if (coder->nb_compiled < data->tt_compil)
		return (pthread_mutex_unlock(&coder->nb_lock), 0);
	pthread_mutex_unlock(&coder->nb_lock);
	return (1);
}

int	check_flag(t_coder *coder)
{
	int	i;

	i = 0;
	if (check_compil(coder, coder->data) == 1)
		return (0);
	pthread_mutex_lock(&coder->data->stop_lock);
	if (coder->data->stop_simu == 1)
		return (pthread_mutex_unlock(&coder->data->stop_lock), 1);
	pthread_mutex_unlock(&coder->data->stop_lock);
	return (0);
}

