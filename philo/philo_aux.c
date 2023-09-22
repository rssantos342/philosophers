/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:47:17 by ride-sou          #+#    #+#             */
/*   Updated: 2023/09/21 17:46:41 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;
	int	i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - 48;
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (sign * nbr);
}

long long	time_ms(void)
{
	struct timeval	time;
	long long		time_total;

	gettimeofday(&time, NULL);
	time_total = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_total);
}

void	print_str(t_philos *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data_s->check_m);
	if (philo->data_s->philo_died == 1
		|| philo->data_s->all_philos_ate == philo->data_s->nbr_philos)
	{
		pthread_mutex_unlock(&philo->data_s->check_m);
		return ;
	}
	pthread_mutex_unlock(&philo->data_s->check_m);
	time = time_ms() - philo->data_s->start_time;
	pthread_mutex_lock(&philo->data_s->print_m);
	printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data_s->print_m);
}

void	destroy_philos_forks(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->check_m);
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->philo_s[i].alive);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philo_s);
	free(data->forks);
}
