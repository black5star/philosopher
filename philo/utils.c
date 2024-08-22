/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:58 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/22 11:08:27 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_value(pthread_mutex_t *mutex, int *var, int val)
{
    pthread_mutex_lock(mutex);
    *var = val;
    pthread_mutex_unlock(mutex);
}

void incrementer(pthread_mutex_t *mutex, int *var)
{
    pthread_mutex_lock(mutex);
    *var += 1;
    pthread_mutex_unlock(mutex);
}

int get_value(pthread_mutex_t *mutex, int *var)
{
    int returned;
    pthread_mutex_lock(mutex);
    returned = *var;
    pthread_mutex_unlock(mutex);
    return(returned);
}

void    ft_usleep(long u_time, t_main *data)
{
    long start;
    long rest;

    start = time_now() * 1e3;
    while((time_now() * 1e3) - start < u_time &&
        !(get_value(&data->mutex, &data->death_flag)))
    {
        rest = u_time - ((time_now() * 1e3) - start);
        if(rest > 5)
            usleep(rest / 2);
        else
            usleep(rest);
    }
}

long    time_now()
{
    struct timeval t;
    
    if(gettimeofday(&t, NULL))
        ft_exit("gettimeofday failed");
    return((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}