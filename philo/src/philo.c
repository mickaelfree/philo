/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:14:54 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 01:51:45 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate_args(t_simu *simu, int argc)
{
	if (simu->nb_philo <= 0 || simu->time_to_die <= 0 || simu->time_to_eat <= 0
		|| simu->time_to_sleep <= 0)
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	if (argc == 6 && simu->nb_eat <= 0)
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	return (1);
}

static int	allocate_memory(t_simu *simu)
{
	simu->philos = malloc(sizeof(t_philo) * simu->nb_philo);
	if (!simu->philos)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	simu->forks = malloc(sizeof(pthread_mutex_t) * simu->nb_philo);
	if (!simu->forks)
	{
		printf("Error: Memory allocation failed\n");
		free(simu->philos);
		return (0);
	}
	simu->fork_status = NULL;
	return (1);
}

static int	initialize_simulation(t_simu *simu)
{
	if (!init_mutexes(simu))
	{
		printf("Error: Failed to initialize mutexes\n");
		return (0);
	}
	if (!init_philos(simu))
	{
		printf("Error: Failed to initialize philosophers\n");
                free(simu->fork_status);
		return (0);
	}
	if (start_simulation(simu))
	{
		printf("Error: Failed start simulation\n");
		cleanup(simu);
		return (0);
	}
	return (1);
}

void	print_action(t_simu *p, int philo_id, enum e_action action)
{
	long	current_time;

	pthread_mutex_lock(&p->print_mutex);
	if (!p->simulation_end)
	{
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
	}
	pthread_mutex_unlock(&p->print_mutex);
}

int	main(int argc, char **argv)
{
	t_simu	simu;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s \n", argv[0]);
		printf("(int) number_of_philosophers\n");
		printf("(int) time_to_die\n(int) time_to_eat\n(int) time_to_sleep\n");
		printf("(int) [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	parse(&simu, argv);
	if (!validate_args(&simu, argc) || !allocate_memory(&simu))
		return (1);
	if (!initialize_simulation(&simu))
	{
		free(simu.philos);
		free(simu.forks);
		return (1);
	}
	cleanup(&simu);
	free(simu.philos);
	free(simu.forks);
	return (0);
}
