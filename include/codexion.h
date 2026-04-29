/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:51:11 by anacharp          #+#    #+#             */
/*   Updated: 2026/04/29 12:49:29 by anacharp         ###   ########.fr       */
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
# include <stdint.h>

# define MAX_CODERS 200
# define TAKE_DONGLE "has taken a dongle"
# define COMPIL "is compiling"
# define DEBUG "is debugging"
# define REFACT "is refactoring"
# define BURN "burned out"

typedef struct s_coder
{
	int				id;
	int				nb_compiled;
	long long		last_compile;
	pthread_t		thread_id;
	pthread_mutex_t	last_lock;
	pthread_mutex_t	nb_lock;
	struct s_data	*data;
}					t_coder;

typedef struct s_dongle
{
	int				available;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	long long		cooldown_begin;
}					t_dongle;

typedef struct s_data
{
	long long			start_time;
	int					init_step;
	int					nb_coder;
	long long			burn_t;
	long long			compil_t;
	long long			debug_t;
	long long			refact_t;
	int					tt_compil;
	long long			dongles_cld;
	char				*schedul;
	int					stop_simu;
	pthread_t			monitor_id;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		log_lock;
	t_coder				*coders;
	t_dongle			*dongles;
}						t_data;

// PARSING
int			parser(int argc, char **argv);

// UTILS
long		ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);

// FILL STRUCTURES
int			fill_data(char **av, t_data *data);

// SIMULATION
void		*simul(void *arg);
void		fifo(t_coder *coder);
void		edf(t_coder *coder);

// DONGLES
void		i_want_dongle(t_coder *coder);
void		take_dongle(t_coder *coder, t_dongle *first, t_dongle *sec, t_data *data);

// SIMU UTILS
void		print_status(t_coder *coder, char *status);

// CLEAN
void		end_clean(t_data *data);
void		problem_clean(t_data *data);

// DESTROY
void		double_destroy(int i, t_data *data);
void		simple_destroy(int i, t_data *data);
void		thread_fail(int i, t_data *data);
void		destroy(int i, t_data *data);

// MONITOR
void		*go_monitor(void *arg);

// TIME
long long	get_time(void);

#endif
