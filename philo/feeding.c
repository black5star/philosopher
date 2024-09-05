/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feeding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:52 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/28 21:31:14 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, t_status stat)
{
	long	time;

	pthread_mutex_lock(&philo->data->monitor_time);
	time = time_now() - philo->data->start_time;
	if (stat == FORK
		&& !get_value(&philo->data->mutex, &philo->data->death_flag))
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (stat == EATING
		&& !get_value(&philo->data->mutex, &philo->data->death_flag))
	{
		printf("%ld %d is eating\n", time, philo->id);
		philo->last_meal_time = time;
	}
	else if (stat == SLEEPING
		&& !get_value(&philo->data->mutex, &philo->data->death_flag))
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (stat == THINKING
		&& !get_value(&philo->data->mutex, &philo->data->death_flag))
		printf("%ld %d is thinking\n", time, philo->id);
	else if (stat == DIED)
		printf("%ld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->monitor_time);
}

void	eating(t_philo *philo)
{
	if (philo->data->philo_nb == 3 && (philo->id % 2))
		ft_usleep(50);
	pthread_mutex_lock(&philo->right_fork->fork);
	write_message(philo, FORK);
	pthread_mutex_lock(&philo->left_fork->fork);
	write_message(philo, FORK);
	write_message(philo, EATING);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	for_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	write_message(philo, FORK);
	ft_usleep(philo->data->time_eat);
}

void	*get_dinner(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	incrementer(&philo->data->monitor_mtx, &philo->data->threads_counter);
	while (!get_value(&philo->data->mutex, &philo->data->death_flag)
		&& !get_value(&philo->data->monitor_mtx, &philo->data->all_are_full))
	{
		if (philo->data->philo_nb == 1)
		{
			for_one(philo);
			break ;
		}
		else
		{
			eating(philo);
			philo->meals_count++;
			if (philo->meals_count == philo->data->max_meals)
				incrementer(&philo->data->mutex, &philo->data->full);
			write_message(philo, SLEEPING);
			ft_usleep(philo->data->time_slp);
			write_message(philo, THINKING);
		}
	}
	return (NULL);
}

void	start_feeding(t_main *data)
{
	int	i;

	i = -1;
	data->start_time = time_now();
	while (++i < data->philo_nb)
		pthread_create(&data->philo[i].thread,
			NULL, get_dinner, &data->philo[i]);
	i = -1;
	pthread_create(&data->observer, NULL, monitor, data);
	while (++i < data->philo_nb)
		pthread_join(data->philo[i].thread, NULL);
	pthread_join(data->observer, NULL);
}
