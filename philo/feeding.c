/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feeding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:02:52 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/24 18:31:44 by blackstar        ###   ########.fr       */
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
    ft_usleep(philo->data->time_eat, philo);
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
        {
            incrementer(&philo->p_mutex, &philo->data->full);
            printf("***philo %d is full and the value is %d********\n", philo->id, philo->data->full);
            break ;
        }
        eating(philo);
        write_message(philo, SLEEPING);
        ft_usleep(philo->data->time_slp, philo);
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
