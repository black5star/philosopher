/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feeding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:52 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/26 12:24:54 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    write_message(t_philo *philo, t_status stat)
{
    long    time;
    
    pthread_mutex_lock(&philo->data->message);
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
        printf("%ld %d died\n", time, philo->id);
    pthread_mutex_unlock(&philo->data->message);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork);
    write_message(philo, FORK);
    pthread_mutex_lock(&philo->left_fork->fork);
    write_message(philo, FORK);
    incrementer(&philo->p_mutex, &philo->meals_count);
    write_message(philo, EATING);
    ft_usleep(philo->data->time_eat);
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

void    *get_dinner(void *p)
{
    t_philo *philo;
    
    philo = (t_philo *)p;

    while(!get_value(&philo->data->mutex, &philo->data->death_flag))
    {
        if(philo->meals_count == philo->data->max_meals)
            incrementer(&philo->p_mutex, &philo->data->full);
        eating(philo);
        write_message(philo, SLEEPING);
        ft_usleep(philo->data->time_slp);
        write_message(philo, THINKING);
    }
    return (NULL);
}

void    start_feeding(t_main *data)
{
    int i;

    i = -1;
    data->start_time = time_now();
    while(++i < data->philo_nb)
        pthread_create(&data->philo[i].thread, NULL, get_dinner, &data->philo[i]);
    i = -1;
    pthread_create(&data->observer, NULL, monitor, data);
    while(++i < data->philo_nb)
        pthread_join(data->philo[i].thread, NULL);
    pthread_join(data->observer, NULL);
}
