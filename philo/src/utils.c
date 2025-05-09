/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:02:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/09 14:13:30 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long wait_time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < wait_time)
		usleep(100);
}

void	cleanup(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_mutex_destroy(&simu->forks[i]);
		pthread_mutex_destroy(&simu->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&simu->print_mutex);
}

void	parse(t_simu *simu, char **argv)
{
	simu->nb_philo = atoi(argv[1]);
	simu->time_to_die = atoi(argv[2]);
	simu->time_to_eat = atoi(argv[3]);
	simu->time_to_sleep = atoi(argv[4]);
	simu->nb_eat = -1;
	if (argv[5])
		simu->nb_eat = atoi(argv[5]);
	simu->simulation_end = 0;
}
