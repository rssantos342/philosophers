/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:24:06 by ride-sou          #+#    #+#             */
/*   Updated: 2023/09/22 12:33:02 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo_s = malloc(sizeof (t_philos) * data->nbr_philos);
	if (!data->philo_s)
		return (-1);
	while (i < data->nbr_philos)
	{
		data->philo_s[i].id = i + 1;
		data->philo_s[i].right_fork = &data->forks[i];
		if ((i + 1) != data->nbr_philos)
			data->philo_s[i].left_fork = &data->forks[i + 1];
		else
			data->philo_s[i].left_fork = &data->forks[0];
		data->philo_s[i].times_eaten = 0;
		data->philo_s[i].data_s = data;
		data->philo_s[i].last_meal = time_ms();
		if (pthread_mutex_init(&data->philo_s[i].alive, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof (pthread_mutex_t) * data->nbr_philos);
	if (!data->forks)
		return (-1);
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	init_philos_forks(t_data *data)
{
	data->all_philos_ate = 0;
	data->philo_died = 0;
	if (pthread_mutex_init(&data->print_m, NULL))
	{
		printf("Error in the print mutex");
		return (-1);
	}
	if (pthread_mutex_init(&data->check_m, NULL))
	{
		printf("Error in the check mutex");
		return (-1);
	}
	if (init_forks(data) == -1)
	{
		printf("Error in the forks init");
		return (-1);
	}
	if (init_philos(data) == -1)
	{
		printf("Error in the philos init");
		return (-1);
	}
	return (0);
}

void	routine(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = time_ms();
	while (i < data->nbr_philos)
	{
		pthread_create(&data->philo_s[i].philo, NULL,
			&start_dinner, &data->philo_s[i]);
		usleep(1000);
		i++;
	}
	pthread_create(&data->main_thread, NULL, &philo_rules, data);
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philo_s[i].philo, NULL);
		i++;
	}
	pthread_join(data->main_thread, NULL);
}
