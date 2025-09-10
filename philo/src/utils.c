/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:02:20 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 01:51:36 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	t_timer	t;

	gettimeofday(&t.timer, NULL);
	return ((t.timer.tv_sec * 1000) + (t.timer.tv_usec / 1000));
}

void	ft_sleep(t_simu *simu, long wait_time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < wait_time && !check_simu_end(simu))
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
	if (simu->fork_status)
		free(simu->fork_status);
}

static int	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > 2147483647) || (sign == -1 && num > 2147483648))
			return (0);
		i++;
	}
	return ((int)(num * sign));
}

void	parse(t_simu *simu, char **argv)
{
	simu->nb_philo = ft_atoi(argv[1]);
	simu->time_to_die = ft_atoi(argv[2]);
	simu->time_to_eat = ft_atoi(argv[3]);
	simu->time_to_sleep = ft_atoi(argv[4]);
	simu->nb_eat = -1;
	if (argv[5])
		simu->nb_eat = ft_atoi(argv[5]);
	simu->simulation_end = 0;
}
