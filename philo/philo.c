/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/22 16:28:40 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long time_out(t_philo *philo)
{
    long last_meal_time;
    long time;
    
    pthread_mutex_lock(&philo->p_mutex);
    last_meal_time = philo->last_meal_time;
    pthread_mutex_unlock(&philo->p_mutex);
    time = time_now() - philo->data->start_time;
    return (time - last_meal_time);
}
void    turn_the_flag(t_philo *philo, long time)
{
    pthread_mutex_lock(&philo->p_mutex);
    if(time > philo->data->time_die)
        philo->data->death_flag = 1;
    pthread_mutex_unlock(&philo->p_mutex);
}

void    *monitor(void *p)
{
    t_main *data;

    data = (t_main *)p;
    while(!get_value(&data->mutex, &data->death_flag))
        ;
    return (NULL);
}

int main(int ac, char **av)
{
    t_main data;

    check_args(ac, av, &data);
    ft_init(&data);
    start_feeding(&data);
}
