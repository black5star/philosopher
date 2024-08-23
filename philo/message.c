/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:18 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/23 16:05:19 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    write_message(t_philo *philo, t_status stat)
{
    long    time;
    int     end_time;
    
    pthread_mutex_lock(&philo->data->message);
    turn_the_flag(philo, time_out(philo));
    end_time = philo->data->death_flag;
    time = time_now() - philo->data->start_time;
    if(stat == FORK && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d has taken a fork\n", time, philo->id);
    else if(stat == EATING && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is eating\n", time, philo->id);
    else if(stat == SLEEPING && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is sleeping\n", time, philo->id);
    else if(stat == THINKING && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is thinking\n", time, philo->id);
    else if(stat == DIED || get_value(&philo->data->mutex, &end_time))
    {
        printf("%ld %d died\n", time, philo->id);
        ft_exit(NULL);
    }
    pthread_mutex_unlock(&philo->data->message);
}
