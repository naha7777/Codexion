/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacharp <anacharp@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:51:11 by anacharp          #+#    #+#             */
/*   Updated: 2026/05/05 15:26:28 by anacharp         ###   ########.fr       */
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
# define MIN_CODERS 2
# define TAKE_DONGLE "has taken a dongle"
# define COMPIL "is compiling"
# define DEBUG "is debugging"
# define REFACT "is refactoring"
# define BURN "burned out"

typedef struct s_node
{
	int			coder_id;
	long long	deadline;
}				t_node;

typedef struct s_heap
{
	t_node	array[MAX_CODERS];
	int		size;
}			t_heap;

typedef struct s_coder
{
	int				id;
	int				nb_compiled;
	long long		last_compile;
	pthread_t		thread_id;
	pthread_mutex_t	last_lock;
	pthread_mutex_t	nb_lock;
	struct s_data	*data;
	struct s_dongle	*first;
	struct s_dongle	*sec;
}					t_coder;

typedef struct s_dongle
{
	int				available;
	int				nb_took;
	long long		cld_b;
}					t_dongle;

typedef struct s_data
{
	t_heap				heap;
	long long			start_time;
	int					init_step;
	int					nb_coder;
	long long			burn_t;
	long long			compil_t;
	long long			debug_t;
	long long			refact_t;
	int					tt_compil;
	long long			d_cld;
	char				*schedul;
	int					stop_simu;
	long long			end_time;
	pthread_cond_t		global_cond;
	pthread_mutex_t		global_lock;
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

// FILL
int			fill_data(char **av, t_data *data);
void		fill_heap(t_data *data);

// ROUTINE
void		*routine(void *arg);

// SCHEDULERS
int			algo(t_coder *coder);

// DONGLES
int			i_want_dongle(t_coder *coder);
int			take_dongle(t_coder *coder, t_dongle *first, t_dongle *sec);
int			drop_dongles(t_coder *coder);

// ROUTINE UTILS
void		print_status(t_coder *coder, char *status);
int			check_flag(t_coder *coder);
int			check_compil(t_coder *coder, t_data *data);
void		broadcast(t_data *data);

// CLEAN
void		join_coders(t_data *data);
void		end_clean(t_data *data);
void		problem_clean(t_data *data);

// DESTROY
void		double_destroy(int i, t_data *data);
void		simple_destroy(int i, t_data *data);
void		thread_fail(int i, t_data *data);
void		destroy(t_data *data);

// MONITOR
void		*go_monitor(void *arg);

// TIME
long long	get_time(void);
long long	get_sim_time(t_data *data);

// HEAP
int			heap_peek(t_heap *h);
void		heap_last(t_heap *h);

#endif
