/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:26:56 by wchan             #+#    #+#             */
/*   Updated: 2023/08/04 18:14:07 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isdigit_str(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long		res;
	int			sign;
	const char	*ptr;

	res = 0;
	sign = 1;
	ptr = str;
	if (!str)
		return (0);
	while (*ptr == 32 || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (*ptr == '-')
		sign *= -1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		res = res * 10 + *ptr - '0';
		if (sign * res > 2147483647 || sign * res < -2147483648)
			return (-1);
		ptr++;
	}
	return ((int) res * sign);
}

void	print_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("[%ld] %d %s\n", get_time() - philo->data->start_time,
		philo->nbr + 1, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_usleep(long time, t_philo *philo)
{
	long	start_usleep_time;

	start_usleep_time = get_time();
	while (get_time() - start_usleep_time < time)
	{
		if (is_dead(philo))
			return (-1);
		usleep(500);
	}
	return (0);
}

long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
