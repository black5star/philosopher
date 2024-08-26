/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:59 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/26 12:19:03 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void    ft_free(t_main *data, int flag)
{
    pthread_mutex_destroy(&data->message);
    pthread_mutex_destroy(&data->monitor_mtx);
    pthread_mutex_destroy(&data->monitor_time);
    pthread_mutex_destroy(&data->mutex);
    free(data->philo);
    free(data->forks);
    exit(flag);
}

void    ft_exit(char *s)
{
    if(s)
        printf("%s\n", s);
    exit(EXIT_FAILURE);
}
