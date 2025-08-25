/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:14:54 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/14 02:42:25 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate_args(t_simu *simu, int argc)
{
	if (simu->nb_philo <= 0 || simu->time_to_die <= 0 || simu->time_to_eat <= 0
		|| simu->time_to_sleep <= 0 || (argc == 6 && simu->nb_eat <= 0))
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	return (1);
}

static int	allocate_memory(t_simu *simu)
{
	simu->philos = malloc(sizeof(t_philo) * simu->nb_philo);
	simu->forks = malloc(sizeof(pthread_mutex_t) * simu->nb_philo);
	if (!simu->philos || !simu->forks)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	return (1);
}

static int	initialize_simulation(t_simu *simu)
{
	init_mutexes(simu);
	init_philos(simu);
	if (start_simulation(simu) != 0)
	{
		printf("Error: Failed to start simulation\n");
		cleanup(simu);
		free(simu->philos);
		free(simu->forks);
		return (0);
	}
	return (1);
}

void	print_action(t_simu *p, int philo_id, enum e_action action)
{
	long	current_time;

	pthread_mutex_lock(&p->print_mutex);
	if (p->simulation_end)
	{
		pthread_mutex_unlock(&p->print_mutex);
		return ;
	}
	current_time = get_time_ms() - p->start_time;
	if (action == TAKING_FORK)
		printf("%ld %d has taken a fork\n", current_time, philo_id);
	else if (action == EAT)
		printf("%ld %d is eating\n", current_time, philo_id);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", current_time, philo_id);
	else if (action == THINK)
		printf("%ld %d is thinking\n", current_time, philo_id);
	else if (action == DIE)
		printf("%ld %d died\n", current_time, philo_id);
	pthread_mutex_unlock(&p->print_mutex);
}

int	main(int argc, char **argv)
{
	t_simu	simu;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s \n", argv[0]);
		return (1);
	}
	parse(&simu, argv);
	if (!validate_args(&simu, argc) || !allocate_memory(&simu))
		return (1);
	if (!initialize_simulation(&simu))
		return (1);
	cleanup(&simu);
	free(simu.philos);
	free(simu.forks);
	return (0);
}
