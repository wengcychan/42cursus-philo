/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:48:03 by wchan             #+#    #+#             */
/*   Updated: 2023/08/24 14:37:54 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_input(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!isdigit_str(argv[i + 1]))
			return (-1);
		i++;
	}
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_meal = ft_atoi(argv[5]);
	if (!data->nbr_philo || data->nbr_philo > 250)
		return (-1);
	if (data->nbr_philo == -1 || data->time_to_die == -1 || data->time_to_eat
		== -1 || data->time_to_sleep == -1 || (argc
			== 6 && data->nbr_meal == -1))
		return (-1);
	if (argc == 5)
		data->nbr_meal = -1;
	return (0);
}

void	init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->die_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&(data->philo[i].mutex_fork_left), NULL);
		i++;
	}
}

void	init_data(t_data *data, t_philo	philo[])
{
	int	i;

	data->philo = philo;
	data->die = false;
	data->stop = false;
	data->nbr_finish_meal = 0;
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].nbr = i;
		philo[i].meal_count = 0;
		philo[i].data = data;
		philo[i].mutex_fork_right = &data->philo[(i + 1)
			% data->nbr_philo].mutex_fork_left;
		i++;
	}
}

void	init_philo(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_create(&data->philo[i].tid, NULL,
			philo_routine, &data->philo[i]);
		i++;
	}
	while (get_time() - data->start_time < data->time_to_die)
		usleep(500);
	monitor_die(data);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
}
