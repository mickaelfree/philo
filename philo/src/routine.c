/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:06:59 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/08 20:18:19 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_single_philo(t_philo *philo, t_simu *simu)
{
	pthread_mutex_lock(&simu->forks[philo->left_fork]);
	print_action(simu, philo->id, TAKING_FORK);
	ft_sleep(simu, simu->time_to_die + 1);
	pthread_mutex_unlock(&simu->forks[philo->left_fork]);
}

static void	take_forks(t_philo *philo, t_simu *simu)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&simu->forks[first_fork]);
	simu->fork_status[first_fork] = 1;
	print_action(simu, philo->id, TAKING_FORK);
	pthread_mutex_lock(&simu->forks[second_fork]);
	simu->fork_status[second_fork] = 1;
	print_action(simu, philo->id, TAKING_FORK);
}

void	philo_eat(t_philo *philo, t_simu *simu)
{
	if (simu->nb_philo == 1)
	{
		handle_single_philo(philo, simu);
		return ;
	}
	take_forks(philo, simu);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(simu, philo->id, EAT);
	ft_sleep(simu, simu->time_to_eat);
	simu->fork_status[philo->left_fork] = 0;
	pthread_mutex_unlock(&simu->forks[philo->left_fork]);
	simu->fork_status[philo->right_fork] = 0;
	pthread_mutex_unlock(&simu->forks[philo->right_fork]);
}

int	check_simu_end(t_simu *simu)
{
	int	tmp;

	pthread_mutex_lock(&simu->print_mutex);
	tmp = simu->simulation_end;
	pthread_mutex_unlock(&simu->print_mutex);
	return (tmp);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_simu	*simu;

	philo = (t_philo *)arg;
	simu = philo->simu;
	if (philo->id % 2 == 0)
		ft_sleep(simu, 10);
	while (!check_simu_end(simu))
	{
		philo_eat(philo, simu);
		print_action(simu, philo->id, SLEEP);
		ft_sleep(simu, simu->time_to_sleep);
		print_action(simu, philo->id, THINK);
	}
	return (NULL);
}
