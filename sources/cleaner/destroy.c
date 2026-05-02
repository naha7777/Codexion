/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:28:07 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/02 15:33:31 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	double_destroy(int i, t_data *data)
{
	pthread_mutex_destroy(&data->coders[i].last_lock);
	while (--i >= 0)
	{
		pthread_mutex_destroy(&data->coders[i].last_lock);
		pthread_mutex_destroy(&data->coders[i].nb_lock);
	}
}

void	simple_destroy(int i, t_data *data)
{
	while (--i >= 0)
		pthread_mutex_destroy(&data->coders[i].last_lock);
}

void	thread_fail(int i, t_data *data)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->coders[i].last_lock);
		pthread_mutex_destroy(&data->coders[i].nb_lock);
		i --;
	}
}

void	destroy(t_data *data)
{
	pthread_mutex_destroy(&data->global_lock);
	pthread_cond_destroy(&data->global_cond);
}
