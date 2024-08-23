/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feeding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:52 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/23 16:16:21 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork);
    write_message(philo, FORK);
    pthread_mutex_lock(&philo->left_fork->fork);
    write_message(philo, FORK);
    incrementer(&philo->p_mutex, &philo->meals_count);
    write_message(philo, EATING);
    ft_usleep((philo->data->time_eat * 1e3), philo->data);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

void    *get_dinner(void *p)
{
    t_philo *philo;
    
    philo = (t_philo *)p;

    while(!get_value(&philo->data->mutex, &philo->data->death_flag))
    {
        if(philo->meals_count == philo->data->max_meals)
            break ;
        philo->last_meal_time = time_now() - philo->data->start_time;
        eating(philo);
        write_message(philo, SLEEPING);
        ft_usleep((philo->data->time_slp * 1e3), philo->data);
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
    while(++i < data->philo_nb)
        pthread_join(data->philo[i].thread, NULL);
    pthread_create(&data->observer, NULL, monitor, &data);
    pthread_join(data->observer, NULL);
}
