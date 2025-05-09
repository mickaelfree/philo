/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:17:33 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/09 14:13:37 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

enum PhiloState {
	THINKING,
	EATING,
	SLEEPING,
	FORK_TAKEN,
	DEAD
};

enum Action {
	EAT,
	SLEEP,
	TAKINK_FORK,
	THINK,
	DIE
};

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			last_meal;
        int 			state;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	struct s_simu	*simu;
}	t_philo;

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
	t_philo			*philos;
}	t_simu;

/* Fonctions utilitaires */
long	get_time_ms(void);
void	ft_sleep(long wait_time);
void	cleanup(t_simu *simu);
void	parse(t_simu *simu, char **argv);

/*intitialisation */
void	init_mutexes(t_simu *simu);
void	init_philos(t_simu *simu);

/*maint simulation*/

int	start_simulation(t_simu *simu);

void	print_action(t_simu *p, int philo_id, enum Action action);

/* Fonctions de debug */
 void	debug_philo_state(t_simu *p);
void debug_simulation_details(t_simu *s);

#endif
