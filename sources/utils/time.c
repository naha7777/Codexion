/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:31:52 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/01 12:10:05 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_sim_time(t_data *data)
{
	return (get_time() - data->start_time);
}

void	sleep_timeout(struct timespec *ts)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	ts->tv_sec = tv.tv_sec;
	ts->tv_nsec = (tv.tv_usec * 1000) + (10 * 1000000);
	if (ts->tv_nsec >= 1000000000)
	{
		ts->tv_sec++;
		ts->tv_nsec -= 1000000000;
	}
}
