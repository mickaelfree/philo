/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:19:07 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/07 16:09:34 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"
#include <stdio.h>

void debug_philo_state(t_simu *info_simulation) {
    printf("Philo State:\n"
           "  - Nombre de philosophes 👨: %d\n"
           "  - Temps avant de mourir💀: %d\n"
           "  - Temps pour manger: ⏲️%d\n"
           "  - Temps pour dormir: 😴%d\n"
           "  - Nombre de repas: 🐔%d\n", 
           info_simulation->nb_philo, info_simulation->time_to_die, info_simulation->time_to_eat, info_simulation->time_to_sleep, info_simulation->nb_eat);
}
static char *get_philo_state_str(int state)
{
	if (state == THINKING) return "🤔";
	else if (state == EATING) return "🍝";
	else if (state == SLEEPING) return "😴";
	else if (state == FORK_TAKEN) return "🍴";
	else if (state == DEAD) return "💀";
	return "❓";
}

void debug_simulation_details(t_simu *s)
{
	int i;
	printf("\n🔍 SIMU: %dp %dms🍽️ %dms😴 %dms💀 %d🍗\n", 
		s->nb_philo, s->time_to_eat, s->time_to_sleep, s->time_to_die, s->nb_eat);
	for (i = 0; i < s->nb_philo; i++)
		printf("P%d:%s %d🍗 %ldms⏱️ | ", i+1, get_philo_state_str(s->philos[i].state), 
			s->philos[i].meals_eaten, s->philos[i].last_meal);
	printf("\n");
}

