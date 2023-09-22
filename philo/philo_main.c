/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:37:09 by ride-sou          #+#    #+#             */
/*   Updated: 2023/09/21 16:14:04 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_values(char **av, t_data *args)
{
	if (ft_atoi(av[1]) > 0 && ft_atoi(av[1]) <= INT_MAX && 
		ft_atoi(av[2]) > 0 && ft_atoi(av[2]) <= INT_MAX && 
		ft_atoi(av[3]) > 0 && ft_atoi(av[3]) <= INT_MAX && 
		ft_atoi(av[4]) > 0 && ft_atoi(av[4]) <= INT_MAX)
	{
		args->nbr_philos = ft_atoi(av[1]);
		args->time_to_die = ft_atoi(av[2]);
		args->time_to_eat = ft_atoi(av[3]);
		args->time_to_sleep = ft_atoi(av[4]);
		if (av[5])
		{
			if (ft_atoi(av[5]) > 0 && ft_atoi(av[5]) <= INT_MAX)
				args->nbr_times_to_eat = ft_atoi(av[5]);
			else
				return (-1);
		}
		if (!av[5])
			args->nbr_times_to_eat = -1;
	}
	else
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	ph_data;

	if (ac == 5 || ac == 6)
	{
		if (get_values(av, &ph_data) == -1)
		{
			printf(RED"Wrong type of arguments."RESET);
			return (-1);
		}
		if (init_philos_forks(&ph_data) == -1)
			return (-1);
		routine(&ph_data);
		destroy_philos_forks(&ph_data);
	}
	else
		printf(RED"Wrong number of arguments. Must be 5 or 6."RESET);
}
