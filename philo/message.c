/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:18 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/22 16:13:29 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    write_message(t_philo *philo, t_status stat)
{
    long    time;
    int     end_time;
    
    end_time = philo->data->death_flag;
    time = time_now() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->message);
    if(stat == FORK && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d has taken a fork\n", time, philo->id);
    else if(stat == EATING && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is eating\n", time, philo->id);
    else if(stat == SLEEPING && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is sleeping\n", time, philo->id);
    else if(stat == THINKING && !get_value(&philo->data->mutex, &end_time))
        printf("%ld %d is thinking\n", time, philo->id);
    else if(stat == DIED)
        printf("%ld %d died\n", time, philo->id);
    pthread_mutex_unlock(&philo->data->message);
}
