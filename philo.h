/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:54:07 by wchan             #+#    #+#             */
/*   Updated: 2023/08/24 14:38:07 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # define FORK "\e[33mhas taken a fork\e[0m"
// # define EAT "\e[31mis eating\e[0m"
// # define SLEEP "\e[32mis sleeping\e[0m"
// # define THINK "\e[34mis thinking\e[0m"
// # define DIE "\e[35mdied\e[0m"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meal;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	eat_mutex;
	bool			die;
	bool			stop;
	long			start_time;
	int				nbr_finish_meal;
	struct s_philo	*philo;
}				t_data;

typedef struct s_philo
{
	pthread_t		tid;
	int				nbr;
	long			begin_meal_time;
	int				meal_count;
	pthread_mutex_t	mutex_fork_left;
	pthread_mutex_t	*mutex_fork_right;
	t_data			*data;
}				t_philo;

//philo.c
void	*philo_routine(void *arg);
int		philo_eat(t_philo *philo);
void	one_philo(t_data data);
void	destroy_mutex(t_data data);

//init.c
int		get_input(int argc, char **argv, t_data *data);
void	init_mutex(t_data *data);
void	init_data(t_data *data, t_philo	philo[]);
void	init_philo(t_data *data);

//utils.c
int		isdigit_str(char *str);
int		ft_atoi(const char *str);
void	print_message(char *message, t_philo *philo);
int		ft_usleep(long time, t_philo *philo);
long	get_time(void);

//monitor.c
void	monitor_die(t_data	*data);
bool	check_philo_die(t_philo *philo);
bool	check_meal(t_data *data);
bool	is_dead(t_philo *philo);

#endif