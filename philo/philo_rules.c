/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:48:40 by ride-sou          #+#    #+#             */
/*   Updated: 2023/09/21 17:21:21 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_death(t_data *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr_philos)
	{
		pthread_mutex_lock(&rules->philo_s[i].alive);
		if ((time_ms() - rules->philo_s[i].last_meal) >= rules->time_to_die)
		{
			print_str(&rules->philo_s[i], RED"died"RESET);
			pthread_mutex_lock(&rules->check_m);
			rules->philo_died = 1;
			pthread_mutex_unlock(&rules->check_m);
			pthread_mutex_unlock(&rules->philo_s[i].alive);
			return (1);
		}
		pthread_mutex_unlock(&rules->philo_s[i].alive);
		i++;
	}
	return (0);
}

int	num_philos_eaten(t_data *rules)
{
	if (rules->nbr_times_to_eat == -1)
		return (0);
	pthread_mutex_lock(&rules->check_m);
	if (rules->all_philos_ate == rules->nbr_philos)
	{
		pthread_mutex_lock(&rules->print_m);
		printf(GREEN"All philosophers ate %i time(s) each."RESET, \
			rules->nbr_times_to_eat);
		pthread_mutex_unlock(&rules->print_m);
		pthread_mutex_unlock(&rules->check_m);
		return (1);
	}
	pthread_mutex_unlock(&rules->check_m);
	return (0);
}

void	*philo_rules(void *index)
{
	t_data	*rules;

	rules = (t_data *)index;
	while (1)
	{
		if (philo_death(rules) == 1)
			return (NULL);
		if (num_philos_eaten(rules) == 1)
			return (NULL);
	}
}
