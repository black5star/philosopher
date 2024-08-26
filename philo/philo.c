/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/24 18:49:07 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int time_out(t_philo *philo)
{
    long last_meal_time;
    long temp;
    int time;
    
    pthread_mutex_lock(&philo->p_mutex);
    last_meal_time = philo->last_meal_time;
    temp = time_now() - philo->data->start_time;
    time = temp - last_meal_time;
    pthread_mutex_unlock(&philo->p_mutex);
    return (time);
}

void    turn_and_check(t_philo *philo, int time)
{
    pthread_mutex_lock(&philo->p_mutex);
    if(time > philo->data->time_die)
        philo->data->death_flag = 1;
    pthread_mutex_unlock(&philo->p_mutex);
    if(get_value(&philo->data->mutex, &philo->data->death_flag))
        write_message(philo, DIED);
    return ;
}

void    *monitor(void *p)
{
    t_main *data;
    t_philo philo;
    int i;

    data = (t_main *)p;
    i = -1;
    while(++i <= data->philo_nb)
    {
        philo = data->philo[i];
        if(data->full == data->philo_nb)
        {
            ft_exit(NULL);
        }
        turn_and_check(&philo, time_out(&philo));
        if(i == data->philo_nb - 1)
            i = -1;
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_main data;

    check_args(ac, av, &data);
    ft_init(&data);
    
    start_feeding(&data);
}
