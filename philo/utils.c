/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:58 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/27 16:53:08 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	incrementer(pthread_mutex_t *mutex, int *var)
{
	pthread_mutex_lock(mutex);
	*var += 1;
	pthread_mutex_unlock(mutex);
}

int	get_value(pthread_mutex_t *mutex, int *var)
{
	int	returned;

	pthread_mutex_lock(mutex);
	returned = *var;
	pthread_mutex_unlock(mutex);
	return (returned);
}

void	ft_usleep(long u_time)
{
	long	start;
	long	rest;

	start = time_now() * 1e3;
	u_time *= 1e3;
	while ((time_now() * 1e3) - start < u_time)
	{
		rest = u_time - ((time_now() * 1e3) - start);
		if (rest > 5)
			usleep(rest / 2);
		else
			usleep(rest);
	}
}

long	time_now(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		ft_exit("gettimeofday failed");
	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}

long	time_out(t_philo *philo)
{
	long	temp;
	long	time;

	pthread_mutex_lock(&philo->data->monitor_time);
	temp = time_now() - philo->data->start_time;
	time = temp - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->monitor_time);
	return (time);
}
