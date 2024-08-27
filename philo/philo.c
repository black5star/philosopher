/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:47:42 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/27 17:29:30 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value(pthread_mutex_t *mutex, int *var, int val)
{
	pthread_mutex_lock(mutex);
	*var = val;
	pthread_mutex_unlock(mutex);
}

bool	turn_and_check(t_philo *philo, long time)
{
	if (time > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->mutex);
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->mutex);
	}
	if (philo->data->death_flag)
	{
		write_message(philo, DIED);
		return (1);
	}
	return (0);
}

void	*monitor(void *p)
{
	t_main	*data;
	t_philo	*philo;
	int		i;

	data = (t_main *)p;
	while (get_value(&data->monitor_mtx, &data->threads_counter)
		< data->philo_nb)
		;
	i = -1;
	while (++i <= data->philo_nb)
	{
		philo = data->philo + i;
		if (get_value(&philo->data->mutex, &philo->data->full)
			== data->philo_nb)
		{
			set_value(&data->monitor_mtx, &data->all_are_full, 1);
			break ;
		}
		if (turn_and_check(philo, time_out(philo)))
			break ;
		if (i == data->philo_nb - 1)
			i = -1;
		usleep(200);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main	data;

	check_args(ac, av, &data);
	ft_init(&data);
	start_feeding(&data);
	ft_free(&data);
}
