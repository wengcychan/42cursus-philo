/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:48:03 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 12:42:53 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo[250];

	if (argc < 5 || argc > 6 || get_input(argc, argv, &data))
		return (1);
	if (!data.nbr_meal)
		return (0);
	if (data.nbr_philo == 1)
	{
		one_philo(data);
		return (0);
	}
	init_data(&data, philo);
	init_mutex(&data);
	init_philo(&data);
	destroy_mutex(data);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->begin_meal_time = get_time();
	if (philo->nbr % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo);
	while (1)
	{
		if (philo_eat(philo))
			break ;
		if (philo->meal_count == philo->data->nbr_meal)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			philo->data->nbr_finish_meal++;
			pthread_mutex_unlock(&philo->data->meal_mutex);
		}
		print_message(SLEEP, philo);
		if (ft_usleep(philo->data->time_to_sleep, philo))
			break ;
		print_message(THINK, philo);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex_fork_left));
	print_message(FORK, philo);
	pthread_mutex_lock(philo->mutex_fork_right);
	print_message(FORK, philo);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->begin_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	print_message(EAT, philo);
	if (ft_usleep(philo->data->time_to_eat, philo))
	{
		pthread_mutex_unlock(&(philo->mutex_fork_left));
		pthread_mutex_unlock(philo->mutex_fork_right);
		return (-1);
	}
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->mutex_fork_left));
	pthread_mutex_unlock(philo->mutex_fork_right);
	return (0);
}

void	one_philo(t_data data)
{
	long	start_time;

	start_time = get_time();
	printf("[%ld] 1 has taken a fork\n",
		get_time() - start_time);
	while (get_time() - start_time < data.time_to_die)
		usleep(500);
	printf("[%ld] 1 died\n",
		get_time() - start_time);
}

void	destroy_mutex(t_data data)
{
	int	i;

	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.die_mutex);
	pthread_mutex_destroy(&data.stop_mutex);
	pthread_mutex_destroy(&data.meal_mutex);
	pthread_mutex_destroy(&data.eat_mutex);
	i = 0;
	while (i < data.nbr_philo)
	{
		pthread_mutex_destroy(&data.philo[i].mutex_fork_left);
		i++;
	}
}
