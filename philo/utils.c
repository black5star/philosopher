/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:45:08 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/19 14:37:28 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_value(pthread_mutex_t *mutex, int *var, int val)
{
    pthread_mutex_lock(mutex);
    *var = val;
    pthread_mutex_unlock(mutex);
}

void value_modifier(pthread_mutex_t *mutex, int *var)
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

bool threadsflag_control(pthread_mutex_t *mutex, int philo_nb, int *threads)
{
    bool returned;

    returned = 0;
    pthread_mutex_lock(mutex);
    if(*threads == philo_nb)
        returned = 1;
    pthread_mutex_unlock(mutex);
    return(returned);
}

void    ft_usleep(long u_time, t_info *data)
{
    long start;
    long rest;

    start = time_now() * 1e3;
    while((time_now() * 1e3) - start < u_time)
    {
        if(get_value(&data->mutex, &data->end_time))
            break ;
        rest = u_time - ((time_now() * 1e3) - start);
        if(rest > 1e3)
            usleep(u_time / 2);
        else
        {
            while((time_now() * 1e3) - start < u_time)
                ;
        }
    }
}

long    time_now()
{
    struct timeval t;
    
    if(gettimeofday(&t, NULL))
        ft_exit("gettimeofday failed");
    return((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}