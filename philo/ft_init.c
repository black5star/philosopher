/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:07 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/24 16:36:22 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_forks(t_forks *fork, t_philo *philo, int i)
{
    int philo_nb;

    philo_nb = philo->data->philo_nb;
    if(!(philo->id % 2))
    {
        philo->right_fork = &fork[(i + 1) % philo_nb];
        philo->left_fork = &fork[i];
    }
    else
    {
        philo->right_fork = &fork[i];
        philo->left_fork = &fork[(i + 1) % philo_nb];
    }
}

void    init_philos(t_main *data)
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
        pthread_mutex_init(&data->philo->p_mutex, NULL);
        init_forks(data->forks, philo, i);
    }
}

void ft_init(t_main *data)
{
    int i;

    data->philo = malloc(sizeof(t_philo) * data->philo_nb);
    data->forks = malloc(sizeof(t_forks) * data->philo_nb);
    pthread_mutex_init(&data->message, NULL);
    pthread_mutex_init(&data->mutex, NULL);
    data->death_flag = 0;
    data->full = 0;
    i = -1;
    while(++i < data->philo_nb)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
    }
    init_philos(data);
}
