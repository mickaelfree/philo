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

#include "../include/philo.h"
#include <stdio.h>

void	debug_philo_state(t_simu *info_simulation)
{
	printf("Philo State:\n"
			"  - Nombre de philosophes 👨: %d\n"
			"  - Temps avant de mourir💀: %d\n"
			"  - Temps pour manger: ⏲️%d\n"
			"  - Temps pour dormir: 😴%d\n"
			"  - Nombre de repas: 🐔%d\n",
			info_simulation->nb_philo,
			info_simulation->time_to_die,
			info_simulation->time_to_eat,
			info_simulation->time_to_sleep,
			info_simulation->nb_eat);
}
