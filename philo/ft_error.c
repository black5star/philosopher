/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:59 by hboustaj          #+#    #+#             */
/*   Updated: 2024/09/05 10:51:36 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_main *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->forks->fork);
	pthread_mutex_destroy(&data->monitor_mtx);
	pthread_mutex_destroy(&data->monitor_time);
	pthread_mutex_destroy(&data->mutex);
	free(data->forks);
	free(data->philo);
}

void	ft_exit(char *s)
{
	if (s)
		printf("%s\n", s);
	exit(EXIT_FAILURE);
}
