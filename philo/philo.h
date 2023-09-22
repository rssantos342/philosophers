/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:37:41 by ride-sou          #+#    #+#             */
/*   Updated: 2023/09/21 16:39:04 by ride-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define YELLOW "\033[1;33m"

typedef struct s_philos
{
	int				id;
	int				times_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	alive;
	pthread_t		philo;
	struct s_data	*data_s;
}	t_philos;

typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_times_to_eat;
	int				all_philos_ate;
	int				philo_died;
	long long		start_time;
	pthread_mutex_t	print_m;
	pthread_mutex_t	check_m;
	pthread_mutex_t	*forks;
	pthread_t		main_thread;
	t_philos		*philo_s;
}	t_data;

// philo.c
int			get_values(char **av, t_data *args);

// philo_aux.c
int			ft_atoi(const char *str);
long long	time_ms(void);
void		print_str(t_philos *philo, char *str);
void		destroy_philos_forks(t_data *data);

// philo_init.c
int			init_philos(t_data *data);
int			init_forks(t_data *data);
int			init_philos_forks(t_data *data);
void		routine(t_data *data);

// philo_actions.c
void		*start_dinner(void *philo);
int			philo_grab_forks(t_philos *philo);
int			philo_is_eating(t_philos *philo);
int			philo_is_sleeping(t_philos *philo);

// philo_rules.c
int			philo_death(t_data *rules);
int			num_philos_eaten(t_data *rules);
void		*philo_rules(void *index);

#endif