/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:08:53 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 12:40:52 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_flag(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->stop_lock);
	if (coder->data->stop_simu == 1)
		return (1);
	pthread_mutex_unlock(&coder->data->stop_lock);
	return (0);
}

void	*simul(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	while (check_flag(coder) == 0)
	{
		i_want_dongle(coder);
		usleep(10);
	}
	return (NULL);
}
