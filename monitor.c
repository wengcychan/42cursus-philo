/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:48:03 by wchan             #+#    #+#             */
/*   Updated: 2023/08/04 18:12:49 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_die(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			if (data->nbr_meal != -1)
			{
				if (check_meal(data))
					return ;
			}
			if (check_philo_die(&data->philo[i]))
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("[%ld] %d %s\n", get_time() - data->start_time,
					data->philo[i].nbr + 1, DIE);
				pthread_mutex_unlock(&data->print_mutex);
				return ;
			}
			i++;
			usleep(100);
		}
	}
}

bool	check_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->eat_mutex));
	if (get_time() - philo->begin_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->data->eat_mutex));
		pthread_mutex_lock(&(philo->data->die_mutex));
		philo->data->die = true;
		pthread_mutex_unlock(&(philo->data->die_mutex));
		return (true);
	}
	pthread_mutex_unlock(&(philo->data->eat_mutex));
	return (false);
}

bool	check_meal(t_data *data)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (data->nbr_finish_meal == data->nbr_philo)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = true;
		pthread_mutex_unlock(&data->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->stop_mutex));
	pthread_mutex_lock(&(philo->data->die_mutex));
	if (philo->data->die || philo->data->stop)
	{
		pthread_mutex_unlock(&(philo->data->die_mutex));
		pthread_mutex_unlock(&(philo->data->stop_mutex));
		return (true);
	}
	pthread_mutex_unlock(&(philo->data->die_mutex));
	pthread_mutex_unlock(&(philo->data->stop_mutex));
	return (false);
}
