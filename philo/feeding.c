/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feeding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:10:30 by blackstar         #+#    #+#             */
/*   Updated: 2024/08/19 15:19:37 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    check_threads(t_info *data)
{
    while(!get_value(&data->mutex, &data->threads_var))
        ;
}

void *is_philo_dead(void *p)
{
    t_info *data;
    int i;

    data = (t_info *)p;
    while(!threadsflag_control(&data->mutex, data->philo_nb, &data->threads_count))
        ;
    while(!get_value(&data->mutex, &data->end_time))
    {
        i = -1;
        while(++i < data->philo_nb && !get_value(&data->mutex, &data->end_time))
        {
            if(time_out(data->philo + i))
            {
                set_value(&data->mutex, &data->end_time, 1);
                write_message(data->philo + i, 'd');
                // printf("here\n");
            }
        }
    }
    return(NULL);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork);
    write_message(philo, 'f');
    pthread_mutex_lock(&philo->left_fork->fork);
    write_message(philo, 'f');
    value_modifier(&philo->p_mutex, &philo->meals_count);
    write_message(philo, 'e');
    ft_usleep((philo->data->time_eat * 1e3), philo->data);
    if(philo->data->max_meals != -1 && (philo->meals_count == philo->data->max_meals))
    {
        pthread_mutex_lock(&philo->p_mutex);
        philo->full = true;
        pthread_mutex_unlock(&philo->p_mutex);
    }
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

void    *get_dinner(void *p)
{
    t_philo *philo;
    
    philo = (t_philo *)p;
    check_threads(philo->data);
    pthread_mutex_lock(&philo->p_mutex);
    philo->last_meal_time = time_now();
    pthread_mutex_unlock(&philo->p_mutex);
    value_modifier(&philo->data->mutex, &philo->data->threads_count);
    while(!get_value(&philo->data->mutex, &philo->data->end_time))
    {
        if(philo->meals_count == philo->data->max_meals)
            break ;
        eating(philo);
        write_message(philo, 's');
        ft_usleep((philo->data->time_slp * 1e3), philo->data);
        write_message(philo, 't');
    }
    return (NULL);
}

void    start_feeding(t_info *data)
{
    int i;

    i = -1;
    if(data->philo_nb == 1)
        pthread_create(&data->philo[0].thread, NULL, one_philo, &data->philo[0]);
    else
    {
        while(++i < data->philo_nb)
            pthread_create(&data->philo[i].thread, NULL, get_dinner, &data->philo[i]);
    }
    pthread_create(&data->is_dead, NULL, is_philo_dead, data);
    data->start_time = time_now();
    set_value(&data->mutex, &data->threads_var, 1);
    i = -1;
    while(++i < data->philo_nb)
        pthread_join(data->philo[i].thread, NULL);
}
