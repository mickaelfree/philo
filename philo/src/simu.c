/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:56:47 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/09 14:00:45 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_simu	*simu;
	int		i;
	int		all_ate_enough;

	simu = (t_simu *)arg;
	while (!simu->simulation_end)
	{
		i = 0;
		all_ate_enough = 1;
		while (i < simu->nb_philo)
		{
			pthread_mutex_lock(&simu->philos[i].meal_mutex);
			if (get_time_ms() - simu->philos[i].last_meal > simu->time_to_die)
			{
				pthread_mutex_unlock(&simu->philos[i].meal_mutex);
				print_action(simu, simu->philos[i].id, DIE);
				pthread_mutex_lock(&simu->print_mutex);
				simu->simulation_end = 1;
				pthread_mutex_unlock(&simu->print_mutex);
				return (NULL);
			}
			if (simu->nb_eat > 0 && simu->philos[i].meals_eaten < simu->nb_eat)
				all_ate_enough = 0;
			pthread_mutex_unlock(&simu->philos[i].meal_mutex);
			i++;
		}
		if (simu->nb_eat > 0 && all_ate_enough)
		{
			pthread_mutex_lock(&simu->print_mutex);
			simu->simulation_end = 1;
			pthread_mutex_unlock(&simu->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo, t_simu *simu)
{
	pthread_mutex_lock(&simu->forks[philo->left_fork]);
	print_action(simu, philo->id, TAKINK_FORK);
	pthread_mutex_lock(&simu->forks[philo->right_fork]);
	print_action(simu, philo->id, TAKINK_FORK);
	
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	
	print_action(simu, philo->id, EAT);
	ft_sleep(simu->time_to_eat);
	
	pthread_mutex_unlock(&simu->forks[philo->left_fork]);
	pthread_mutex_unlock(&simu->forks[philo->right_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_simu	*simu;

	philo = (t_philo *)arg;
	simu = philo->simu;
	if (philo->id % 2 == 0)
		ft_sleep(10);
	
	while (!simu->simulation_end)
	{
		philo_eat(philo, simu);
		print_action(simu, philo->id, SLEEP);
		ft_sleep(simu->time_to_sleep);
		print_action(simu, philo->id, THINK);
	}
	return (NULL);
}

int	start_simulation(t_simu *simu)
{
	int			i;
	pthread_t	monitor;

	simu->start_time = get_time_ms();
	i = 0;
	while (i < simu->nb_philo)
	{
		if (pthread_create(&simu->philos[i].thread, NULL, philo_routine,
				&simu->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, simu) != 0)
		return (1);
	i = 0;
	while (i < simu->nb_philo)
	{
		if (pthread_join(simu->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}
