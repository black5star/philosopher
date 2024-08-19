/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:24:01 by blackstar         #+#    #+#             */
/*   Updated: 2024/08/19 15:18:34 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *one_philo(void *p)
{
    t_philo *philo;

    philo = (t_philo *)p;
    check_threads(philo->data);
        pthread_mutex_lock(&philo->p_mutex);
    philo->last_meal_time = time_now();
    pthread_mutex_unlock(&philo->p_mutex);
    value_modifier(&philo->data->mutex, &philo->data->threads_count);
    write_message(philo, 'f');
    while(!get_value(&philo->data->mutex, &philo->data->end_time))
        usleep(philo->data->time_die + 2);
    return (NULL);
}

void    init_forks(t_forks *fork, t_philo *philo, int i)
{
    int philo_nb;

    philo_nb = philo->data->philo_nb;
    philo->right_fork = &fork[(i + 1) % philo_nb];
    philo->left_fork = &fork[i];
    if(!(philo->id % 2))
    {
        philo->right_fork = &fork[i];
        philo->left_fork = &fork[(i + 1) % philo_nb];
    }
}

void    init_philos(t_info *data)
{
    int i;
    t_philo *philo;
    
    i = -1;
    while(++i < data->philo_nb)
    {
        philo = data->philo + i;
        philo->id = i + 1;
        philo->data = data;
        philo->meals_count = 0;
        philo->full = false;
        pthread_mutex_init(&philo->p_mutex, NULL);
        init_forks(data->forks, philo, i);
    }
}

void ft_init(t_info *data)
{
    int i;
    
    data->philo = malloc(sizeof(t_philo) * data->philo_nb);
    data->forks = malloc(sizeof(t_forks) * data->philo_nb);
    pthread_mutex_init(&data->mutex, NULL);
    pthread_mutex_init(&data->message, NULL);
    data->end_time = 0;
    data->threads_var = 0;
    data->threads_count = 0;
    i = -1;
    while(++i < data->philo_nb)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
    }
    init_philos(data);
}
