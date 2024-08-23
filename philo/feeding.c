/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feeding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:52 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/22 16:14:46 by hboustaj         ###   ########.fr       */
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
        turn_the_flag(philo, time_out(philo));
        if(get_value(&philo->data->mutex, &philo->data->death_flag))
        {
            write_message(philo, DIED);
            ft_exit(NULL);
        }
        eating(philo);
        philo->last_meal_time = time_now();
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
    // pthread_create(&data->observer, NULL, monitor, &data);
    i = -1;
    while(++i < data->philo_nb)
        pthread_join(data->philo[i].thread, NULL);
}
