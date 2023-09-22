/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:53:19 by ride-sou          #+#    #+#             */
/*   Updated: 2023/09/21 16:39:03 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_dinner(void *philo)
{
	t_philos	*philo_copy;

	philo_copy = (t_philos *)philo;
	while (1)
	{
		if (philo_copy->data_s->nbr_philos == 1)
		{
			pthread_mutex_lock(philo_copy->right_fork);
			print_str(philo, YELLOW"has taken a fork"RESET);
			pthread_mutex_unlock(philo_copy->right_fork);
			return (NULL);
		}
		if (philo_copy->id % 2 == 0)
			usleep(4000);
		if (philo_grab_forks(philo_copy) == -1)
			break ;
		if (philo_is_eating(philo_copy) == -1)
			break ;
		if (philo_is_sleeping(philo_copy) == -1)
			break ;
		print_str(philo_copy, "is thinking");
	}
	return (NULL);
}

int	philo_grab_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->data_s->check_m);
	if (philo->data_s->philo_died == 1
		|| philo->data_s->all_philos_ate == philo->data_s->nbr_philos)
	{
		pthread_mutex_unlock(&philo->data_s->check_m);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data_s->check_m);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_str(philo, YELLOW"has taken a fork"RESET);
		pthread_mutex_lock(philo->right_fork);
		print_str(philo, YELLOW"has taken a fork"RESET);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_str(philo, YELLOW"has taken a fork"RESET);
		pthread_mutex_lock(philo->left_fork);
		print_str(philo, YELLOW"has taken a fork"RESET);
	}
	return (0);
}

int	philo_is_eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->data_s->check_m);
	if (philo->data_s->philo_died == 1
		|| (philo->data_s->all_philos_ate == philo->data_s->nbr_philos))
	{
		pthread_mutex_unlock(&philo->data_s->check_m);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data_s->check_m);
	pthread_mutex_lock(&philo->alive);
	print_str(philo, BLUE"is eating"RESET);
	philo->last_meal = time_ms();
	pthread_mutex_lock(&philo->data_s->check_m);
	philo->times_eaten++;
	if (philo->data_s->nbr_times_to_eat != -1)
		if (philo->times_eaten == philo->data_s->nbr_times_to_eat)
			philo->data_s->all_philos_ate++;
	pthread_mutex_unlock(&philo->data_s->check_m);
	pthread_mutex_unlock(&philo->alive);
	usleep(philo->data_s->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_is_sleeping(t_philos *philo)
{
	pthread_mutex_lock(&philo->data_s->check_m);
	if (philo->data_s->philo_died == 1
		|| philo->data_s->all_philos_ate == philo->data_s->nbr_philos)
	{
		pthread_mutex_unlock(&philo->data_s->check_m);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data_s->check_m);
	print_str(philo, PURPLE"is sleeping"RESET);
	usleep(philo->data_s->time_to_sleep * 1000);
	return (0);
}
