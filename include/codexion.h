/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:51:11 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/22 18:43:47 by anacharp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder
{
	int				id;
	int				nb_compiled;
	long			last_compile;
	pthread_t		thread_id;
	struct s_data	*data;
}					t_coder;

typedef struct s_dongle
{
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	long			cooldown_begin;
}					t_dongle;

typedef struct s_data
{
	int					init_step;
	int					nb_coder;
	float				burn_t;
	float				compil_t;
	float				debug_t;
	float				refact_t;
	int					tt_compil;
	float				dongles_cld;
	char				*schedul;
	int					stop_simu;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		log_lock;
	t_coder				*coders;
	t_dongle			*dongles;
}						t_data;

// PARSING
int		parser(int argc, char **argv);

// UTILS
long	ft_atol(const char *nptr);

// FILL STRUCTURES
int		fill_data(char **av, t_data *data);

// ALGOS
void	*fifo(void *arg);
void	*edf(void *arg);

// CLEAN
void	end_clean(t_data *data);
void	problem_clean(t_data *data);

// MONITOR
void	monitor(void *arg);

#endif
