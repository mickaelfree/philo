/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:17:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 02:36:55 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

enum				e_action
{
	EAT,
	SLEEP,
	TAKING_FORK,
	THINK,
	DIE
};

typedef struct s_timer
{
	struct timeval	timer;
}					t_timer;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	meal_mutex;
	struct s_simu	*simu;
}					t_philo;

typedef struct s_simu
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				simulation_end;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	int				*fork_status;
	t_philo			*philos;
}					t_simu;

long				get_time_ms(void);
void				ft_sleep(t_simu *simu, long wait_time);
void				cleanup(t_simu *simu);
void				parse(t_simu *simu, char **argv);
void				*philo_routine(void *arg);

int					init_mutexes(t_simu *simu);
int					init_philos(t_simu *simu);
int					check_simu_end(t_simu *simu);

void				*monitor_routine(void *arg);

int					start_simulation(t_simu *simu);
void				print_action(t_simu *p, int philo_id, enum e_action action);

#endif
