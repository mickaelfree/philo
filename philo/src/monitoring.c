/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:11:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/13 23:50:42 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_philosopher_death(t_simu *simu, int i)
{
	int	is_dead;

	pthread_mutex_lock(&simu->philos[i].meal_mutex);
	is_dead = (get_time_ms() - simu->philos[i].last_meal > simu->time_to_die);
	pthread_mutex_unlock(&simu->philos[i].meal_mutex);
	if (is_dead)
	{
		pthread_mutex_lock(&simu->print_mutex);
		if (!simu->simulation_end)
		{
			simu->simulation_end = 1;
			printf("%ld %d died\n", get_time_ms() - simu->start_time, simu->philos[i].id);
		}
		pthread_mutex_unlock(&simu->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_philosopher_eaten_enough(t_simu *simu, int i)
{
	int	eaten_enough;

	if (simu->nb_eat <= 0)
		return (1);
	pthread_mutex_lock(&simu->philos[i].meal_mutex);
	eaten_enough = (simu->philos[i].meals_eaten >= simu->nb_eat);
	pthread_mutex_unlock(&simu->philos[i].meal_mutex);
	return (eaten_enough);
}

static int	check_all_philosophers_eaten_enough(t_simu *simu)
{
	int	i;

	if (simu->nb_eat <= 0)
		return (0);
	i = 0;
	while (i < simu->nb_philo)
	{
		if (!check_philosopher_eaten_enough(simu, i))
			return (0);
		i++;
	}
	return (1);
}

static void	*end_simulation(t_simu *simu)
{
	pthread_mutex_lock(&simu->print_mutex);
	simu->simulation_end = 1;
	pthread_mutex_unlock(&simu->print_mutex);
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_simu	*simu;
	int		i;

	simu = (t_simu *)arg;
	while (1)
	{
		i = 0;
		while (i < simu->nb_philo)
		{
			if (check_philosopher_death(simu, i))
				return (end_simulation(simu));
			i++;
		}
		if (check_all_philosophers_eaten_enough(simu))
			return (end_simulation(simu));
		pthread_mutex_lock(&simu->print_mutex);
		if (simu->simulation_end)
		{
			pthread_mutex_unlock(&simu->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&simu->print_mutex);
		usleep(100);
	}
	return (NULL);
}
