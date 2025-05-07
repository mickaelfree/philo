/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:14:54 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/07 17:15:17 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../include/philo.h"


enum  Action{
        EAT,
        SLEEP,
        TAKINK_FORK,
        THINK,
        DIE,
}action;
void	print_action(t_simu *p,int i,enum Action hello)
{
        if (hello == TAKINK_FORK)
        {
                //faire action
                printf("%s  %d\n","le philo prend une fourchette",i);
                printf("%s  %d\n","",i);
        }
        if (hello == EAT)
        {
                printf("%s  %d\n","philo est entrain de manger",i);
                sleep(p->time_to_eat);
                //faire action
        }
        if (hello == SLEEP)
        {
                //faire action
                printf("%s  %d\n","le philo dormir",i);
                sleep(p->time_to_sleep);
        }
        if (hello == TAKINK_FORK)
        {
                //faire action
                printf("%s  %d\n","",i);
        }
        if (hello == THINK)
        {
                //faire action
                printf("%s  %d\n","",i);
        }
        if (hello == DIE)
        {
                //faire action
                printf("%s  %d\n","fin de la simulation il un mort",i);
        }
}
void	timetodie(int i)
{
        printf("time to die in %d\n",i);
}
void	parse(t_simu *philo, char **argv)
{
        philo->nb_philo = atoi(argv[1]);
        philo->time_to_die = atoi(argv[2]);
        philo->time_to_eat = atoi(argv[3]);
        philo->time_to_sleep = atoi(argv[4]);
        philo->nb_eat = atoi(argv[5]);

}

int	main(int argc, char **argv)
{
        t_simu	philo;
        int i;
	(void)argc;
	if (argc != 5 && argc != 6)
		return (1);
        parse(&philo, argv);
        debug_philo_state(&philo);
        i = 1;

        //faire une boucle pour cree tous les philo
        while (1)
        {
                timetodie(philo.time_to_die);
                sleep(i);
                print_action(&philo,i,EAT);
                if(!philo.time_to_die--)
                        break;
        }
        if (philo.time_to_die <= 0)
                printf("fin de la simulation il un mort");
        
	return (0);
}
