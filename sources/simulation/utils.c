/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:33:23 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 12:33:33 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_status(t_coder *coder, char *status)
{
	pthread_mutex_lock(&coder->data->log_lock);
	pthread_mutex_lock(&coder->data->stop_lock);
	if (coder->data->stop_simu == 0)
		printf("%lli %i %s\n", get_time(), coder->id, status);
	pthread_mutex_unlock(&coder->data->stop_lock);
	pthread_mutex_unlock(&coder->data->log_lock);
}
