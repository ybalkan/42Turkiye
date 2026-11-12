/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 22:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:09:02 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_sched_type
{
	CODEX_FIFO,
	CODEX_EDF,
	CODEX_LIFO
}	t_sched_type;

typedef struct s_request
{
	int			coder_id;
	long long	seq;
	long long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*data;
	int			size;
	int			capacity;
}	t_heap;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	int				is_in_use;
	long long		cooldown_until;
	t_heap			queue;
}	t_dongle;

typedef struct s_rules
{
	int				num_coders;
	long long		time_to_burnout;
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				compiles_required;
	long long		dongle_cooldown;
	t_sched_type	scheduler;
}	t_rules;

typedef struct s_sim	t_sim;

typedef struct s_coder
{
	int			id;
	int			compile_count;
	int			waiting;
	int			granted;
	long long	last_compile_start;
	t_request	request;
	t_dongle	*first;
	t_dongle	*second;
	pthread_t	thread;
	t_sim		*sim;
}	t_coder;

struct s_sim
{
	t_rules			rules;
	long long		start_time;
	long long		seq_counter;
	int				simulation_ended;
	int				monitor_started;
	int				started_coders;
	pthread_mutex_t	sched_mutex;
	pthread_cond_t	sched_cond;
	pthread_mutex_t	log_mutex;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_t		monitor;
};

/* Parsing */
int			print_error(const char *msg);
int			parse_args(int argc, char **argv, t_rules *rules);
int			parse_values(char **argv, t_rules *rules);
int			parse_number(const char *str, long long *out);

/* Simulation setup */
int			init_simulation(t_sim *sim, t_rules *rules);
void		cleanup_simulation(t_sim *sim);
void		destroy_sync(t_sim *sim);
int			init_dongles(t_sim *sim);
void		init_coders(t_sim *sim);
int			start_threads(t_sim *sim);
void		join_threads(t_sim *sim);

/* Time and state */
long long	get_time_ms(void);
void		ms_to_timespec(long long ms, struct timespec *ts);
void		precise_sleep(long long duration, t_sim *sim);
int			is_simulation_ended(t_sim *sim);

/* Priority queue */
int			heap_init(t_heap *heap, int capacity);
void		heap_destroy(t_heap *heap);
int			heap_push(t_heap *heap, t_request req, t_sched_type type);
t_request	heap_pop(t_heap *heap, t_sched_type type);
t_request	*heap_peek(t_heap *heap);
int			compare_requests(t_request *a, t_request *b, t_sched_type type);
void		heap_swap(t_request *a, t_request *b);
void		heap_sift_up(t_heap *heap, int index, t_sched_type type);
void		heap_sift_down(t_heap *heap, int index, t_sched_type type);
int			heap_remove(t_heap *heap, int coder_id, t_sched_type type);

/* Dongles */
int			dongle_init(t_dongle *dongle, int id, int capacity);
void		dongle_destroy(t_dongle *dongle);
void		dongle_enqueue(t_dongle *dongle, t_request req, t_sched_type type);
void		dongle_remove(t_dongle *dongle, int coder_id, t_sched_type type);
int			dongle_available(t_dongle *dongle, long long now);
void		dongle_take(t_dongle *dongle, int coder_id, t_sched_type type);
void		dongle_release(t_dongle *dongle, long long now, long long cooldown);

/* Coders */
void		*coder_routine(void *arg);
int			acquire_pair(t_coder *coder);
void		release_pair(t_coder *coder);
void		mark_refactoring(t_coder *coder);
void		wait_single(t_coder *coder);
int			reached_required(t_coder *coder);

/* Scheduler and monitor */
void		arbitrate(t_sim *sim);
int			all_compiled(t_sim *sim);
void		*monitor_routine(void *arg);

/* Logging */
void		log_line(t_sim *sim, int id, const char *msg, long long ts);
void		log_compile_start(t_sim *sim, t_coder *coder, long long ts);

#endif
