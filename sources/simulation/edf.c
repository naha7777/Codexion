/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:34:36 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/23 08:34:44 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*edf(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	pthread_mutex_lock(&data->log_lock);
	printf("codeur %i: je me reveille pas\n", coder->id);
	pthread_mutex_unlock(&data->log_lock);
	return (NULL);
}
