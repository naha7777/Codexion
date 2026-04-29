/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:20:31 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 09:26:19 by anacharp         ###   ########.fr       */
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
	while (i <= data->nb_coder)
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
			printf("%lli %i burned out\n", get_time(), data->coders[i].id);
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

// en gros le monitor :
// - check tous les codeurs
// - micro sieste avec usleep de 1/2 ms
// - recommence

// Pour eviter que le monitor ne lise une heure pendant que le codeur est en
// train de l'ecrire (=data race), ils utilisent un mutex
// - le codeur verouille, ecrit l'heure, deverouille
// - le monitor verouille, lit l'heure, deverouille

// si le temps de la last_compile d'un codeur depasse le time de burn-out
// change le flag
// ou si tous les codeurs ont atteint le nb tt de compil
// pour ce second, vu que c'est TOUS les codeurs, quand un l'atteint le thread
// codeur doit surement s'arreter et si tous les threads codeurs sont arretes
// et que le flag de stop est pas enclenche alors ils ont tous reussi

// reflechir au niveau du temps avec gettimeofday
// on recup les donnees en millisecondes de base
// donc faut faire le temps en millisecondes
// gettimeofday donne des secondes et des microsecondes
// usleep demande des microsecondes

// donc pour utiliser usleep on doit creer un convertisseur en millisecondes
// pareil pour gettime

// peut creer des fonctions genre use_usleep et gettime qui convertissent tout
// seul et renvoient le resultat
// et on met dans datas les donnees en millisecondes comme ca le monitor n'a
// rien a faire d'autre que comparer avec les donnees de base
