/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:34 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/19 12:18:30 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    time_out(t_philo *philo)
{
    long time;
    
    if(get_value(&philo->p_mutex, &philo->full))
        return (0);
    time = time_now() - get_value(&philo->p_mutex, &philo->last_meal_time);
    if(time > philo->data->time_die)
        return (1);
    return (0);    
}

void    write_message(t_philo *philo, char c)
{
    long    time;
    int     end_time;
    
    if(philo->meals_count == philo->data->max_meals)
        return ;
    end_time = philo->data->end_time;
    time = time_now() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->message);
    if(c == 'f' && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d has taken a fork\n", time, philo->id);
    else if(c == 'e' && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is eating\n", time, philo->id);
    else if(c == 's' && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is sleeping\n", time, philo->id);
    else if(c == 't' && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is thinking\n", time, philo->id);
    else if(c == 'd' && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d died\n", time, philo->id);
    pthread_mutex_unlock(&philo->data->message);
}
