/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:18 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/23 18:04:57 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    write_message(t_philo *philo, t_status stat)
{
    long    time;
    
    pthread_mutex_lock(&philo->data->message);
    turn_and_check(philo, time_out(philo));
    time = time_now() - philo->data->start_time;
    if(stat == FORK)
        printf("%ld %d has taken a fork\n", time, philo->id);
    else if(stat == EATING)
    {
        philo->last_meal_time = time;
        printf("%ld %d is eating\n", time, philo->id);
    }
    else if(stat == SLEEPING)
        printf("%ld %d is sleeping\n", time, philo->id);
    else if(stat == THINKING)
        printf("%ld %d is thinking\n", time, philo->id);
    else if(stat == DIED)
    {
        printf("%ld %d died\n", time, philo->id);
        ft_exit(NULL);
    }
    pthread_mutex_unlock(&philo->data->message);
}
