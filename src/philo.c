/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:14:54 by mickmart          #+#    #+#             */
/*   Updated: 2025/04/25 01:32:50 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../include/philo.h"


void	timetodie(int i)
{
        printf("time to die in %d\n",i);
}

int	main(int argc, char **argv)
{
        t_philo	philo;
        int i;
	(void)argv;
	if (argc != 5 && argc != 6)
		return (1);
        philo.nb_philo = atoi(argv[1]);
        philo.time_to_die = atoi(argv[2]);
        philo.time_to_eat = atoi(argv[3]);
        philo.time_to_sleep = atoi(argv[4]);
        philo.nb_eat = atoi(argv[5]);
	printf("%d\n",philo.nb_philo);
	printf("%d\n",philo.time_to_die);
	printf("%d\n",philo.time_to_eat);
	printf("%d\n",philo.time_to_sleep);
	printf("%d\n",philo.nb_eat);
        i = 1;
        while (1)
        {
                timetodie(philo.time_to_die);
                sleep(i);
                if(!philo.time_to_die--)
                        break;
                
                
                
        }
	return (0);
}
